#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// Dilation -> Erosion
Mat openImage,closeImage;
Mat structCross = getStructuringElement(1,Size(3,3));
Mat image = (Mat_<uchar>(6,6) <<
        0,0,0,0,255,0,
        0,255,255,255,255,255,
        0,255,255,0,255,0,
        0,0,0,0,0,0,
        0,255,0,255,0,255,
        0,0,0,0,0,0);

void close()
{
    Mat tmp;
    dilate(image,tmp,structCross);
    erode(tmp,openImage ,structCross);
}

void open()
{
    Mat tmp;
    erode(image,tmp,structCross);
    dilate(tmp,closeImage ,structCross);
}

int main()
{
    Mat DilatedImage;
    Mat ErodeImage;
    // define struct image
    dilate(image,DilatedImage,structCross);
    erode(image, ErodeImage,structCross);

    open();
    close();

    String namedWindowOriginalImage = "OriginalImage";
    String namedWindowDilation = "Dilation";
    String namedWindowErode = "Erode";
    String namedWindowOpen = "OpenImage";
    String namedWindowClose = "CloseImage";

    namedWindow(namedWindowErode,WINDOW_NORMAL);
    namedWindow(namedWindowOriginalImage,WINDOW_NORMAL);
    namedWindow(namedWindowDilation, WINDOW_NORMAL);
    namedWindow(namedWindowOpen,WINDOW_NORMAL);
    namedWindow(namedWindowClose,WINDOW_NORMAL);

    imshow(namedWindowOriginalImage,image);
    imshow(namedWindowDilation,DilatedImage);
    imshow(namedWindowErode,ErodeImage);
    imshow(namedWindowOpen,openImage);
    imshow(namedWindowClose,closeImage);

    waitKey(0);
    destroyAllWindows();
    return 0;
}
