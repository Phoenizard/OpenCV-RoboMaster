#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat image = imread("/home/shay/Workspace/1.jpeg",0);

int main()
{
    namedWindow("OriginalImage", WINDOW_NORMAL);
    imshow("OriginalImage", image);
    image = imread("/home/shay/Workspace/1.jpeg",0);
    Mat newImage;
    newImage = image.clone();
    //进行二值化处理，选择30，200.0为阈值
    threshold(image, newImage, 150, 200, 0);
    namedWindow("BinaryImage",WINDOW_NORMAL);
    imshow("BinaryImage", newImage);
    waitKey(0);
    return 0;
}

/* Threshold types
 *   CV_THRESH_BINARY      =0,  value = value > threshold ? max_value : 0
 *
 *   CV_THRESH_BINARY_INV  =1,  value = value > threshold ? 0 : max_value
 *
 *   CV_THRESH_TRUNC       =2,  value = value > threshold ? threshold : value
 *
 *   CV_THRESH_TOZERO      =3,  value = value > threshold ? value : 0
 *
 *   CV_THRESH_TOZERO_INV  =4,  value = value > threshold ? 0 : value
 *
 *   CV_THRESH_OTSU        =8   use Otsu algorithm to choose the optimal threshold value; combine the flag with one of the above CV_THRESH_* values

*/