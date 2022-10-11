#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat src = imread("/home/shay/Workspace/1.jpeg");
    if (src.empty())
    {
        printf("No image");
        return -1;
    }
    namedWindow("SrcImg", WINDOW_AUTOSIZE);
    imshow("SrcImg", src);
    vector<Mat> mv;
    Mat dstBlue, dstGreen, dstRed;
    //分离图片的BGR通道图片至Vector
    split(src, mv);

    mv[0] = Scalar(0);
    //此时整个图片的BG通道均为0，图片整体颜色偏红R
    merge(mv, dstBlue);
    split(src, mv);
    mv[1] = Scalar(0);
    merge(mv, dstGreen);
    split(src, mv);
    mv[2] = Scalar(0);

    merge(mv, dstRed);
    imshow("DstB", dstBlue);
    imshow("DstG", dstGreen);
    imshow("DstR", dstRed);
    waitKey(0);
    return 0;
}
//in-range可以提取特定颜色

