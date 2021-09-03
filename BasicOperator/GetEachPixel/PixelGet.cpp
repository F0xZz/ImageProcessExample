#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;
//three channels Get
Mat ColorRule(Mat src){
    int row = src.rows;
    int col = src.cols;
    int channels = src.channels();
    Mat imgHSV;
    cvtColor(src, imgHSV, COLOR_BGR2HSV);
    Mat dst(row, col, CV_8UC3);
    Mat tempDst;
    tempDst= Mat::zeros(dst.size(),CV_8U);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
        {
            int B = src.at<Vec3b>(i, j)[0];
            int G = src.at<Vec3b>(i, j)[1];
            int R = src.at<Vec3b>(i, j)[2];
            //            std::cout<<R<<std::endl;
            int H = imgHSV.at<Vec3b>(i, j)[0];
            int S = imgHSV.at<Vec3b>(i, j)[1];
            int V = imgHSV.at<Vec3b>(i, j)[2];
            //            ((G/(R+255))>0.25)?((G/(R+255))<0.65)?tempDst.at<uchar>(i,j)=255:tempDst.at<uchar>(i,j)=0:tempDst.at<uchar>(i,j)=0;
            //            ((B/(R+255))>0.05)?((B/(R+255))<0.45)?tempDst.at<uchar>(i,j)=255:tempDst.at<uchar>(i,j)=0:tempDst.at<uchar>(i,j)=0;
            //            ((B/(G+255))>0.20)?((B/(G+255))<0.60)?tempDst.at<uchar>(i,j)=255:tempDst.at<uchar>(i,j)=0:tempDst.at<uchar>(i,j)=0;
            if(R>G&&G>B)
            {

                //                tempDst.at<uchar>(i,j)=255;
                if((G/(R+255.0))>0.25 && (G/(R+255.0))<0.65)
                {

                    if((B/(R+255.0))>0.05 && (B/(R+255.0))<0.45)
                    {

                        if((B/(G+255.0))>0.20 && (B/(G+255.0))<0.60){
                            //tempDst.at<uchar>(i,j)=255;
                            if(H<60&&S>20&&V>100){(S > ((255 - R) * 0.33))?tempDst.at<uchar>(i,j)=255:tempDst.at<uchar>(i,j)=0;}
                        }
                    }
                    //
                }
                //            tempDst.at<uchar>(i,j)=255;
            }
        }
    }
    return tempDst;
}
void Get_byPointerStep(){
    Mat Img(10, 10, CV_8UC1,Scalar(0)); //创建10x10的1通道图像，图像的像素值随机生成
    uchar * data = Img.data;
    // return the pointer
    for (int i = 4; i < 6; i++)
    {
        for (int j = 4; j < 6; j++)
        {
            uchar * pixel = data + i * Img.step; //find the date by the address
            pixel[j] = 100;
        }
    }
}
void Get_byPtr(){
    Mat Img(10, 10, CV_8UC1,Scalar(0)); //创建120×120的三通道图像，图像的像素值随机生成
    for (int i = 4; i < 6; i++)
    {
            uchar * ptr = Img.ptr<uchar>(i);
            for (int j = 4; j < 6; j++)
            {
                    ptr[j] = 100;
            }
    }
}
