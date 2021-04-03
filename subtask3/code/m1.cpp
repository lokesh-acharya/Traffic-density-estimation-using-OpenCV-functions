#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <chrono>

using namespace cv;
using namespace std;
using namespace std::chrono;

/*------------Global variables-----------------*/
#define ul unsigned long
#define ARRAY_SIZE 10000

float* a;       //to store the queue density
unsigned long mag_g = 0;

/* Initializing the array */
void init(){ 
    a = (float *)malloc(sizeof(float)*ARRAY_SIZE);
}

vector<Point2f> src_points; //to store 4-coordinates

/*-----------------------------------------------*/


/*-------------------------------------------------
| method to calculate the magnitude of image after |
| applying threshold                               |
--------------------------------------------------*/

ul cal_magnitude(Mat diff){
    mag_g = 0;
    float threshold = 30.0f;
    float dist;

    ul mag = 0;

    for(int i=0; i<diff.rows; ++i)
        for(int j=0; j<diff.cols; ++j)
        {
            Vec3b pixelMatrix = diff.at<Vec3b>(i,j);
            dist = sqrt(pixelMatrix[0]*pixelMatrix[0]+pixelMatrix[1]*pixelMatrix[1]+pixelMatrix[2]*pixelMatrix[2]);
            if(dist>threshold) mag ++;
            mag_g++;
        }
    return mag;
}



/*-------------------------------------------------
| helper function to detect the mouse click events |
|                                                  |
--------------------------------------------------*/

void onMouseClick(int event, int x, int y, int flags, void* userdata){
    //capture points if left button pressed wiht control key pressed
    if( event == EVENT_LBUTTONDOWN ){
        src_points.push_back(Point2f(x,y));
        /*cout<< "coordinate- ("<< x <<","<< y << ")"<< endl;*/
    }
    if(src_points.size() == 4){
        destroyWindow("Win");
        return;
    }
}

/*-------------------------------------------------
| Function to take 4 points from the user in      |
| order to apply projection and cropping to that  |
| particular region                               |
--------------------------------------------------*/

void setPoints(Mat imgsrc){    
    //set the area of interest for the frame to be proojected and cropped
    
    // converting the colored image to grayscale 
    Mat gray_img;
    cvtColor(imgsrc,gray_img,COLOR_BGR2GRAY);
    //resize(gray_img,gray_img,Size(gray_img.cols/3,gray_img.rows/3));
    namedWindow("Win",0);
    resizeWindow("Win",1000,1000);
    imshow("Win", gray_img);
         
    //give the instructions to click the points    
    cout<<"click 4 points on Win "<<endl;
    cout<<"top-left"<<endl;
    cout<<"bottom-left"<<endl;
    cout<<"bottom-right"<<endl;
    cout<<"top-right"<<endl;
    setMouseCallback("Win",onMouseClick,0);
    waitKey(0);
    return;
}

/*-------------------------------------------------
| Function to correct the camera angle and crop   |
| the image.                                      |
--------------------------------------------------*/

Mat project_crop(Mat imsrc,vector<Point2f> &dst_points){
    Mat gray_img;
    cvtColor(imsrc,gray_img,COLOR_BGR2GRAY);
    
    //projecting the grayscaled image to the required image     
    
    
    Mat homography = findHomography(src_points, dst_points);
    Mat im_out;
    warpPerspective(gray_img, im_out, homography, gray_img.size());

    //croping the image
    int top_left_x = 472;
    int top_left_y = 52;
    int width = 800 - 472;
    int height = 830 - 52;
    Rect cropped_img(top_left_x, top_left_y, width, height);
    Mat im_crop = im_out(cropped_img);
    return im_crop;
}


/*-------------------------------------------------
|                   MAIN                          |
--------------------------------------------------*/

int main(int argc, char** argv){
    
    init();

    if(argv[1]==NULL){
        cout<<"enter the image to be processed"<<endl;
        return 0;
    }
    string vid_path = argv[1];
    string final_path = vid_path + ".mp4";
    VideoCapture cap(final_path);
    
    char *arg2 = argv[2];
    int gap = atoi(arg2); 

    /*check if camera opened successfully*/
    if(!cap.isOpened()){
        cout << "Could not open the video file" << endl;
        return -1;
    }
    
    /*set the projection points*/
    Mat frame, cropped, empty;//, prev;
    cap >> empty;
    if(empty.empty()) return -1;
    
    /*set the 4 coordinates*/
    setPoints(empty);
    /*
    src_points.push_back(Point2f(854,270));
    src_points.push_back(Point2f(579,1072));
    src_points.push_back(Point2f(1574,1068));
    src_points.push_back(Point2f(1328,274));
	*/
	
    vector<Point2f> dst_points;
    dst_points.push_back(Point2f(472,52));
    dst_points.push_back(Point2f(472,832));
    dst_points.push_back(Point2f(800,830));
    dst_points.push_back(Point2f(800,52));

    empty = project_crop(empty,dst_points);
    namedWindow("frame",0);
    resizeWindow("frame",300,500);
    
    //int time = 1;
    int k = 0;
    int cnt = 0;

    auto start = high_resolution_clock::now();

    while(k<1000000){
        // capture new frame
        cap >> frame;
        if(frame.empty()) break;
        
        //correction of camera anlge and cropping        
        cropped = project_crop(frame,dst_points);

        if(cnt==0 || cnt==gap){

            //Estimate Queue Density            
            Mat dst;
            absdiff(cropped,empty,dst);
            ul mag = cal_magnitude(dst);
            float mag1 = (mag*1.0f)/(mag_g*1.0f);
            a[k] = mag1;

            cnt = 1;
            /*dispaly out the time, Queue Density, Dynamic Density*/
            //cout<<time<<","<<a[k-1]<<","<<b[k-1]<< "\n";
        }
        else{
            a[k]=a[k-1];                     
            cnt += 1;
        }       
        k++;
        
        /*display new cropped frame*/
        /*
        imshow("frame", cropped);
        char c = (char)waitKey(25);
        if(c=='q'||c==27){
            break;
        }
        */
        
    }

    auto stop = high_resolution_clock::now();
    duration<float> fs = (stop - start);
    cout << fs.count()<<"\n";

    //save the data to a csv file
    ofstream myfile1("../analysis/m1.csv");
    if (myfile1.is_open())
    {
        myfile1 << "Frame,Queue_density"<<"\n";
        for(int count = 0; count < k; count++){
            myfile1 <<(count+1)<<","<<a[count]<< "\n";
        }
        myfile1.close();
    }
    else cout << "Unable to create csv file";

	//save error value in txt file to calculate error
    ofstream myfile2("../analysis/m1.txt");
    if (myfile2.is_open())
    {
        for(int count = 0; count < k; count++){
            myfile2 <<a[count]<< "\n";
        }
        myfile2.close();
    }
    else cout << "Unable to create txt file";

    free(a);
    return 0;
}

