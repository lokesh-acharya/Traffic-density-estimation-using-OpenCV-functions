#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;


vector<Point2f> src_points; // Global Variable

void onMouseClick(int event, int x, int y, int flags, void* userdata)
{
    //capture points if left button pressed wiht control key pressed
    if( event == EVENT_LBUTTONDOWN ){
        src_points.push_back(Point2f(x,y));
        cout<< "coordinate- ("<< x <<","<< y << ")"<< endl;
    }
    if(src_points.size() ==4){
        destroyWindow("Win");
        return;
    }
}

int main(int argc, char** argv){
    
    if(argv[1]==NULL){
        cout<<"enter the image to be processed"<<endl;
        return 0;
    }
    string img_path = argv[1];
    string final_path = img_path + ".jpg";
    
    //read the Image
    Mat imsrc = imread(final_path);
    
    //check if the Image has loaded or not
    if (imsrc.empty()){
        cout<<"Image not loaded"<<endl;
        return -1;
    }

    // converting the colored image to grayscale 
    Mat gray_img;
    cvtColor(imsrc,gray_img,COLOR_BGR2GRAY);
    //resize(gray_img,gray_img,Size(gray_img.cols/3,gray_img.rows/3));
    namedWindow("Win",0);
    resizeWindow("Win",1000,1000);
    imshow("Win", gray_img);
    
    
    //projecting the grayscaled image to the required image 
    
    
    //give the instructions to click the points
    
    cout<<"click 4 points on Win "<<endl;
    cout<<"top-left"<<endl;
    cout<<"bottom-left"<<endl;
    cout<<"bottom-right"<<endl;
    cout<<"top-right"<<endl;
    

    setMouseCallback("Win",onMouseClick,0);

    waitKey(0);
    
    vector<Point2f> dst_points;
    dst_points.push_back(Point2f(472,52));
    dst_points.push_back(Point2f(472,832));
    dst_points.push_back(Point2f(800,830));
    dst_points.push_back(Point2f(800,52));
    
    Mat homography = findHomography(src_points,dst_points);
    Mat im_out;

    warpPerspective(gray_img,im_out,homography,gray_img.size());
    //resize(im_out,im_out,Size(im_out.cols/3,im_out.rows/3));
    //show the image projected
    namedWindow("projected image",0);
    resizeWindow("projected image",1000,1000);
    imshow("projected image",im_out);
    //save the projected image
    bool check1 = imwrite("projected.jpg",im_out);
    if(check1 == false){
        cout<<"Image could not be saved"<<endl;
    }
    waitKey(0);
    destroyWindow("projected image");

    //croping the image
    int top_left_x = 472;
    int top_left_y = 52;
    int width = 800 - 472;
    int height = 830 - 52;
    Rect cropped_img(top_left_x,top_left_y,width,height);
    Mat im_crop = im_out(cropped_img);
    namedWindow("cropped image",0);
    resizeWindow("cropped image",500,500);
    //show the image cropped 
    imshow("cropped image",im_crop);
    bool check2 = imwrite("cropped.jpg",im_crop);
    if(check2 == false){
        cout<<"Image could not be saved"<<endl;
    }
    
    waitKey(0);

    destroyAllWindows();    
    return 0;

}
