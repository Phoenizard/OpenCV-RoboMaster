#include "opencv2/opencv.hpp"
#include "iostream"

using namespace cv;
using namespace std;

// Read the image
Mat image = imread("/home/shay/Workspace/DisplayImage/1.jpeg",1);
Mat image_draw(600,800,CV_8UC3,Scalar(100,250,30));
// Scalar : 24bit Three Channels 0-255
/*
 *  CV_ X  +      U/S     +   C     +       N
 *     bit Unsigned/signed Channels + Number of Channels
 */

int main(int argc,char** argv)
{
    if(image.empty())
    {
        cout << "No image" << endl;
        cin.get(); // wait for any key press
        return -1;
    }
    String windowName = "Window";
    namedWindow(windowName,WINDOW_AUTOSIZE); // define window's name
    imshow(windowName,image); // windows + image
    waitKey(0); // wait for any key press
    destroyWindow(windowName); // close the windows
    return 0;
}


