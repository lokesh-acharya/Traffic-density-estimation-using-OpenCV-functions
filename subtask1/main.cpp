#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

using namespace std;
using namespace cv;

#define pb push_back

vector<Point2f> src_pts;
int n = 0;

void mouse_callback(int  event, int  x, int  y, int  flag, void *param){
    //consider only left clicks
    if (event == EVENT_LBUTTONDOWN){      
        printf("x = %d, y = %d\n", x, y);   //display point clicked
        n++;                                //increase count of selected points            
        src_pts.pb(Point2f(x, y));          //store point coordinates clicked
    }
}

int main(int argc, char** argv){
    
    string img_path = argv[1];
    Mat img = imread(img_path);
    //Mat img = imread("empty.jpg");          //read image
    
    //check validation of image
    if(img.empty()){
        cout<<"Image can't be loaded or not found\n";
        cin.get();
        return -1;
    }

    //convert to gray image
    Mat gimg;
    cvtColor(img, gimg, COLOR_BGR2GRAY);

    //selected postion display size
    vector<Point2f> dst_pts;
    Size s = {300, 500};
    dst_pts.pb(Point2f(0,0));
    dst_pts.pb(Point2f(s.width,0));
    dst_pts.pb(Point2f(s.width,s.height));
    dst_pts.pb(Point2f(0,s.height));

    while(true){
        //create image window for selection
        string win = "Select corners";
        namedWindow(win, WINDOW_NORMAL);
        imshow(win, gimg);

        printf("\nCheck points in cyclic order :)\n");          //user prompt            
        setMouseCallback("Select corners", mouse_callback);     //callback to maouse 
        
        //loop running till 4 points are selected or window is quit('q')
        for(;;){
            if(n==4) break;
            if((waitKey(1) & 0xFF) == 'q') break;
        }
        destroyWindow(win);                                     //remove selection window

        //check valid selection
        if(n<4){
            printf("\nDon't quit before selected all points, select again\n\n");
            //reinitiate selection data and parameters
            src_pts = {};
            n = 0;
        }
        //exit loop on valid selection
        else{
            break;
        }
    }

    Mat H = getPerspectiveTransform(src_pts, dst_pts);          //get homography matrix for transformation
    Mat final_img;                                              //initialize resulting image
    warpPerspective(gimg, final_img, H, s);                     //setup resulting image

    //show reulting image
    imshow("Congo!!", final_img);
    waitKey(0);
    printf("\nPress any key to exit\n");

    return 0;
}
