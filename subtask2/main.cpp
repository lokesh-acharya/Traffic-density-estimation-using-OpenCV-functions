#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <unistd.h>

using namespace cv;
using namespace std;

/*------------Global variables-----------------*/
#define ul unsigned long
#define ARRAY_SIZE 10000

float* a;       //to store the queue density
float* b;       //to store the dynamic density
unsigned long mag_g = 0;

/* Initializing the array */
void init(){ 
    a = (float *)malloc(sizeof(float)*ARRAY_SIZE);
    b = (float *)malloc(sizeof(float)*ARRAY_SIZE);
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

Mat project_crop(Mat imsrc){
    Mat gray_img;
    cvtColor(imsrc,gray_img,COLOR_BGR2GRAY);
    
    //projecting the grayscaled image to the required image     
    vector<Point2f> dst_points;
    dst_points.push_back(Point2f(472,52));
    dst_points.push_back(Point2f(472,832));
    dst_points.push_back(Point2f(800,830));
    dst_points.push_back(Point2f(800,52));
    
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
    
    /*check if camera opened successfully*/
    if(!cap.isOpened()){
        cout << "Could not open the video file" << endl;
        return -1;
    }
    
    /*set the projection points*/
    Mat frame, cropped, empty, prev;
    cap >> empty;
    if(empty.empty()) return -1;

    cap >> prev;
    if(prev.empty()) return -1;
    
    /*set the 4 coordinates*/
    setPoints(empty);
    empty = project_crop(empty);
    prev = project_crop(prev);
    namedWindow("frame",0);
    resizeWindow("frame",300,500);
    
    int time = 1;
    int k = 0;
    int cnt = 0;

    while(k<1000000){
        // capture new frame
        cap >> frame;
        if(frame.empty()) break;
        
        //correction of camera anlge and cropping        
        cropped = project_crop(frame);

        if(cnt == 15){

            //Estimate Queue Density            
            Mat dst;
            absdiff(cropped,empty,dst);
            ul mag = cal_magnitude(dst);
            float mag1 = (mag*1.0)/(mag_g*1.0);
            a[k] = mag1;

            //Estimate Dynamic Density
            Mat dst_;
            absdiff(cropped,prev,dst_);
            ul mag_ = cal_magnitude(dst_);
            float mag_1 = (mag_*1.0)/(mag_g*1.0);
            b[k] = mag_1;

            prev = cropped;
            k++;
            time = k;
            cnt = 0;
            /*dispaly out the time, Queue Density, Dynamic Density*/
            cout<<time<<","<<a[k-1]<<","<<b[k-1]<< "\n";
        }
        else cnt++;

        /*display new cropped frame*/
        imshow("frame", cropped);
        char c = (char)waitKey(25);
        if(c=='q'||c==27){
            break;
        }
    }

    /*project the data to a csv file to plot the graph*/
    ofstream myfile("data.csv");
    if (myfile.is_open())
    {
        myfile << "Time(in sec)," <<"Queue_density,"<<"dynamic density"<<"\n";
        for(int count = 0; count < k; count++){
            myfile <<(count+1)<<","<<a[count]<<","<<b[count]<< "\n";
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    free(a);
    free(b);
    return 0;
}
