#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>
#include <map>

using namespace cv;
using namespace std;

struct data_rect{
    float angle,x,y,area;
    Point2f ps[4];
};

struct analyze{
    int rank_degree,flag1,flag2;
    float dis;
};

bool cmp(const analyze x,const analyze y)
{
        if(x.rank_degree == y.rank_degree) return x.dis < y.dis;
        return x.rank_degree < y.rank_degree;

}

int main()
{
    Mat srcImage = imread("/home/shay/Workspace/7.jpeg");
    if (srcImage.empty()){
        cout << "No Image" << endl;
        return -1;
    }
    String InputImage = "InputImage";
    namedWindow(InputImage,WINDOW_NORMAL);
    imshow(InputImage,srcImage);

    vector<Mat>mv;
    split(srcImage,mv);
    Mat gray_red = mv[2];
    // Gray is the grayImage by the red Channel which has been split by mv
    Mat BinImage;
    threshold(gray_red,BinImage , 248,255,0);
    // Binary
    medianBlur(BinImage,BinImage,3);

    vector<vector<Point>>contours;
    vector<Vec4i>hierarchy;
    findContours(BinImage,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE);
    Mat dst = srcImage;
    vector<RotatedRect> minAreaRects(contours.size());
    map<int,data_rect>dataRect;
    int Rect_size = 1;
    for(int i=0;i<contours.size();++i){
        double AreaTemp = contourArea(contours[i], false);
        if (!(AreaTemp > 50 && AreaTemp < 200)) continue;
        minAreaRects[i] = minAreaRect(contours[i]);
        data_rect tmp;
        if ((minAreaRects[i].size.width / minAreaRects[i].size.height)<=1){
            // The second section
            tmp.angle = abs(minAreaRects[i].angle);
        } else{
            tmp.angle = 90 - abs(minAreaRects[i].angle);
        }
        tmp.x = minAreaRects[i].center.x;
        tmp.y = minAreaRects[i].center.y;
        tmp.area = AreaTemp;
        minAreaRects[i].points(tmp.ps);
        dataRect[Rect_size] = tmp;
        Rect_size++;
        cout << "No." << i << ":";
        cout << "Width="<< minAreaRects[i].size.width << " " << "Height=" << minAreaRects[i].size.height;
        cout << "   Center: (" << minAreaRects[i].center.x << "," << minAreaRects[i].center.y << ")";
        cout << "   Angle=" << minAreaRects[i].angle << endl;
    }
    analyze proTable[Rect_size*Rect_size+1];
    int k = 0;
    for (int i = 1; i <= Rect_size; i++) {
        for (int j = i+1; j <= Rect_size; j++) {
            proTable[k].flag1 = i,proTable[k].flag2 = j;
            proTable[k].dis = sqrt(pow((dataRect[i].x-dataRect[j].x),2)+pow((dataRect[i].y-dataRect[j].y),2));
            if (abs(dataRect[i].angle-dataRect[j].angle)<5) proTable[k].rank_degree = 1;
            else if (abs(dataRect[i].angle-dataRect[j].angle)<10) proTable[k].rank_degree = 2;
            else if (abs(dataRect[i].angle-dataRect[j].angle)<20) proTable[k].rank_degree = 3;
            else proTable[k].rank_degree = 4;
            k++;
        }
    }
    sort(proTable,proTable + k,cmp);
    for (int i=0;i<k;i++){
        cout << proTable[i].rank_degree << " " << proTable[i].dis << " " << proTable[i].flag1 << " " << proTable[i].flag2 << endl;
    }

    for (int j = 0; j < 4; j++) {
        line(dst,Point(dataRect[proTable[0].flag1].ps[j]),Point(dataRect[proTable[0].flag1].ps[(j+1)%4]),Scalar(0,255,0),2);
        line(dst,Point(dataRect[proTable[0].flag2].ps[j]),Point(dataRect[proTable[0].flag2].ps[(j+1)%4]),Scalar(0,255,0),2);
        // putText(dst, to_string(j),ps[j],0,1,Scal
        // ar(0,255,0),1);
    }

     namedWindow("dst",WINDOW_NORMAL);
     imshow("dst",dst);
     waitKey(0);
     destroyAllWindows();
    return 0;
}
