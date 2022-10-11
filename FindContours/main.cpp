#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

Mat srcImage = imread("/home/shay/Workspace/1.jpeg");
Mat gray,binImage,res;

int main()
{
    if(srcImage.empty()){
        cout << "No Image" << endl;
        return -1;
    }

    resize(srcImage,srcImage,Size(srcImage.cols*0.5,srcImage.rows*0.5));
    String nameWindowsOriginalImage = "OriginalImage";
    namedWindow(nameWindowsOriginalImage,WINDOW_NORMAL);
    imshow(nameWindowsOriginalImage,srcImage);


    cvtColor(srcImage,gray,COLOR_BGR2GRAY);
    GaussianBlur(gray,gray,Size(9,9),2,2);
    // Turn the image into gary with GaussianBlur

    threshold(gray,binImage,170,255,THRESH_BINARY|THRESH_OTSU);
    // Turn the image into Binary mood

    vector<vector<Point>>contours;
    // Save the data of contour
    vector<Vec4i>hierarchy;
    // Save the structure[level] of the contours
    findContours(binImage,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE);

    res = srcImage;

    for(int i=0;i<contours.size();++i){
        drawContours(res,contours,i,Scalar(0,0,255),2,8);
    }

    for(int i=0;i<hierarchy.size();++i){
        cout << hierarchy[i] << endl;
    }


    String nameWindowsGrayImage = "GrayImage";
    String nameWindowsBinaryImage = "BinaryImage";
    String nameWindowsResult = "ResultImage";

    namedWindow(nameWindowsGrayImage,WINDOW_NORMAL);
    namedWindow(nameWindowsBinaryImage,WINDOW_NORMAL);
    namedWindow(nameWindowsResult,WINDOW_NORMAL);
    imshow(nameWindowsGrayImage,gray);
    imshow(nameWindowsBinaryImage,binImage);
    imshow(nameWindowsResult,res);

    waitKey(0);
    destroyAllWindows();
    return 0;
}
