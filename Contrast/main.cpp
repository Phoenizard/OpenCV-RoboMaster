#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat image = imread("/home/shay/Workspace/1.jpeg");
    if (image.empty())
    {
        cout << "No image" << endl;
        cin.get();
        return -1;
    }

    Mat imageContrastHigh;
    image.convertTo(imageContrastHigh,-1,1.2,0);
    // alpha -> >0    1 = normal

    String windowNameOrientImage = "OrientImage";
    String windowNameNew = "NewImage";

    namedWindow(windowNameOrientImage, WINDOW_NORMAL);
    namedWindow(windowNameNew,WINDOW_NORMAL);
    imshow(windowNameOrientImage,image);
    imshow(windowNameNew,imageContrastHigh);

    waitKey(0);
    destroyAllWindows();

    return 0;
}