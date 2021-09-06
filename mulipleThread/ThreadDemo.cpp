#include <iostream>
#include <thread>
#include <stdio.h>
#include <chrono>
#include <time.h>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;
void C(Mat src,Mat &dstOut){

    time_t rawtime;
    struct tm *info;
    char buffer[80];

    time( &rawtime );

    info = localtime( &rawtime );
    printf("当前的本地时间和日期：%s", asctime(info));

    int row = src.rows;
    int col = src.cols;
    //    int channels = src.channels();
    Mat imgHSV;
    cvtColor(src, imgHSV, COLOR_BGR2HSV);
    Mat dst(row, col, CV_8UC3);
    Mat tempDst;
    tempDst= Mat::zeros(dst.size(),CV_8U);
    int index = 0;
    while(index<100){
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++)
            {
                int B = src.at<Vec3b>(i, j)[0];
                int G = src.at<Vec3b>(i, j)[1];
                int R = src.at<Vec3b>(i, j)[2];

                int H = imgHSV.at<Vec3b>(i, j)[0];
                int S = imgHSV.at<Vec3b>(i, j)[1];
                int V = imgHSV.at<Vec3b>(i, j)[2];
                if(R>G&&G>B)
                {
                    if((G/(R+255.0))>0.25 && (G/(R+255.0))<0.65)
                    {
                        if((B/(R+255.0))>0.05 && (B/(R+255.0))<0.45)
                        {
                            if((B/(G+255.0))>0.20 && (B/(G+255.0))<0.60){
                                if(H<60&&S>20&&V>100){(S > ((255 - R) * 0.33))?tempDst.at<uchar>(i,j)=255:tempDst.at<uchar>(i,j)=0;}
                            }
                        }
                    } 
                }
            }
        }
        ++index;
        dstOut=tempDst.clone();
    }
    time( &rawtime );

    info = localtime( &rawtime );
    printf("inner function 当前的本地时间和日期：%s", asctime(info));
    //    tempDst = AfterProcess(tempDst);
    //    return tempDst;
}
int main(){

    double totaltime;
    Mat combine ;
    int i =0;
    Mat img = cv::imread("/home/ubuntu/Pictures/vlcsnap-2021-09-06-10h26m52s689.png");
    Mat Dst ;
    Dst= Mat::zeros(img.size(),CV_8U);
    // crop the img
    Mat CropImgtop,CropImgdown;
    Mat CropImgtop2,CropImgdown2;
    Rect Top(0,0,1920,270);
    Rect Top2(0,270,1920,270);
    Rect Down(0,540,1920,270);
    Rect Down2(0,810,1920,270);
    CropImgtop = img(Top);
    CropImgdown = img(Down);
    CropImgtop2 = img(Top2);
    CropImgdown2 = img(Down2);
    Mat DstTop,DstDown;
    Mat DstTop2,DstDown2;
    DstTop = Mat::zeros(CropImgtop.size(),CV_8U);
    DstDown = Mat::zeros(CropImgdown.size(),CV_8U);
    DstTop2 = Mat::zeros(CropImgtop2.size(),CV_8U);
    DstDown2 = Mat::zeros(CropImgdown2.size(),CV_8U);
    //method get the
    while(i<10){
        std::thread th1(C,img,std::ref(Dst));

        //method one filter by only one img
        th1.join();

        //method one filter by only two pair
        std::thread th2(C,CropImgtop,std::ref(DstTop));
        std::thread th3(C,CropImgdown,std::ref(DstDown));
        std::thread th4(C,CropImgtop2,std::ref(DstTop2));
        std::thread th5(C,CropImgdown2,std::ref(DstDown2));

        time_t rawtime;
        struct tm *info;
        char buffer[80];

        time( &rawtime );

        info = localtime( &rawtime );

        printf("Out begin 4 thread  当前的本地时间和日期：%s", asctime(info));

        th2.join();
        th3.join();
        th4.join();
        th5.join();

        time( &rawtime );

        info = localtime( &rawtime );

        printf("Out end 4 thread  当前的本地时间和日期：%s", asctime(info));
        ++i;
    }
    return 0;
    //    hconcat(DstTop, DstDown, combine); //横向拼接
    //    vconcat(combine, DstDown2, combine);//纵向拼接
}
