#include <iostream>
#include <map>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat testImage = (Mat_<uchar>(8,8) <<
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 0,   0,   0,   255, 255, 255,
        255, 255, 0,   255, 0,   0,   255, 255,
        255, 255, 0,   0,   0,   255, 255, 255,
        255, 255, 255, 0,   0,   255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255);
// The data's Type in BinImage is uchar, while data type of the RGB  is <Vec3b>

int fx[5] = {0,0,0,-1,1};
int fy[5] = {0,-1,1,0,0};
map<int, map<int, int>>flag;

void PrintRGBChannel(Mat img);
void dfs(Mat img, int x, int y);
bool SumRct(int x, int y);

int main()
{
    for (int i = 0; i < testImage.rows; i++) {
        for (int j = 0; j < testImage.cols; j++) {
            flag[i][j] = 1;
        }
    }

    String srcImage = "SrcImage";
    namedWindow(srcImage,WINDOW_NORMAL);
    imshow(srcImage,testImage);
    // Depth First Search
    dfs(testImage,0,0);

    // Print the outline
    for (int i = 0; i < testImage.rows; i++) {
        for (int j = 0; j < testImage.cols; j++) {
            cout << flag[i][j] << " ";
            if (!flag[i][j] && SumRct(i,j)) testImage.at<uchar>(i,j) = (255/2);
        }
        cout << endl;
    }

    String nameWindowTestImage = "TestImage";
    namedWindow(nameWindowTestImage,WINDOW_NORMAL);
    imshow(nameWindowTestImage,testImage);

    waitKey(0);
    destroyAllWindows();
    return 0;
}

void PrintRGBChannel(Mat img)
{
    for (int i = 1; i < img.rows; ++i) {
        for (int j = 1; j < img.cols; ++j) {
            int cB = img.at<Vec3b>(i, j)[0];
            int cG = img.at<Vec3b>(i, j)[1];
            int cR = img.at<Vec3b>(i, j)[2];
            cout << "(R:" << cR << " G:" << cG << " B:" << cB << ")   ";
        }
        cout << endl;
    }
}

void dfs(Mat img, int x, int y) {
    if (!(x>=0 && y>=0 && x < img.rows && y < img.cols && img.at<uchar>(x,y) && flag[x][y] != 0)){
        return;
    }
    flag[x][y] = 0;
    for (int k = 1; k <= 4; k++) {
        dfs(img ,x+fx[k], y+fy[k]);
    }
}

bool SumRct(int x,int y) {
    return flag[x-1][y-1] + flag[x-1][y] + flag[x-1][y+1] + flag[x][y-1] + flag[x][y] + flag[x][y+1] + flag[x+1][y-1] + flag[x+1][y] + flag[x+1][y+1];
}

/*
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 1 1 0 0 0
0 0 1 1 1 1 0 0
0 0 1 1 1 0 0 0
0 0 0 0 1 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
 */