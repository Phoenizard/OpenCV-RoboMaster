#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat image = imread ("/home/shay/Workspace/DisplayImage/1.jpeg");

int main()
{
    if (image.empty())
    {
        cout << "No image" << endl;
        cin.get();
        return -1;
    }

    Mat imageBrightness50; // create a new image object for saving the change of brightness
    image.convertTo(imageBrightness50, -1, 1,40);
    /* image.convertTo(m:the var for new Image, rtype , alpha, beta);
     * rtype: if rtype <0 , the type of Image won't change, if it is >0, I don't know
     * image(x,y) = input_image(x*alpha,y*alpha) + beta
     * if the RGB of the input_image is (10,10,10), then the output RGB is (10*alpha+beta,10*alpha+beta,10*alpha+beta)
     * [The max is 255, if the value is over 255, it will be 255]
     */

    String WindowNameOriginalImage = "OriginalImage";
    String WindowNameNewImage = "NewImage";

    namedWindow(WindowNameOriginalImage, WINDOW_NORMAL);
    namedWindow(WindowNameNewImage, WINDOW_NORMAL);

    imshow(WindowNameOriginalImage, image);
    imshow(WindowNameNewImage, imageBrightness50);

    waitKey(0);
    destroyAllWindows();

    return 0;
}
