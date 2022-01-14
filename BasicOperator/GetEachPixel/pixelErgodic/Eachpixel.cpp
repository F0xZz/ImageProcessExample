#include <iostream>
#include <ergodic_pixel_speed.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <time.h>
#ifdef _WIN32
#	include <windows.h>
#else
#	include <sys/time.h>
#endif
#ifdef _WIN32
int gettimeofday(struct timeval *tp, void *tzp)
{
    time_t clock;
    struct tm tm;
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    tm.tm_year   = wtm.wYear - 1900;
    tm.tm_mon   = wtm.wMonth - 1;
    tm.tm_mday   = wtm.wDay;
    tm.tm_hour   = wtm.wHour;
    tm.tm_min   = wtm.wMinute;
    tm.tm_sec   = wtm.wSecond;
    tm. tm_isdst  = -1;
    clock = mktime(&tm);
    tp->tv_sec = clock;
    tp->tv_usec = wtm.wMilliseconds * 1000;
    return (0);
}
#endif
double cpuSecond()
{
    struct timeval tp;
    gettimeofday(&tp,NULL);
    return((double)tp.tv_sec+(double)tp.tv_usec*1e-6);

}
using namespace std;
using namespace cv;
// A mat storage in the cache is
/**
 * storage in the memory struct
 * rowPoint[colwidth*3] BGRBGRBGR....BGRBGR
 * rowPoint[colwidth*3] BGRBGRBGR....BGRBGR
 * rowPoint[colwidth*3] BGR....BGRBGRBGRBGR
 */
int main()
{
    double iStart,iElaps;



    cv::Mat img = cv::imread("/home/ubuntu/MyTemp/img/car.jpg");
    unsigned char* src = img.data;
    int rowS = img.rows;
    int colS = img.cols;
    iStart=cpuSecond();
    //method 1 0.57217s 57ms/per
    //    for(int j = 0;j<10;j++){

    //        for (int row = 0; row < rowS; row++)
    //        {
    //            uchar* ptr = img.ptr<uchar>(row);
    //            //每一次跳跃三列，也就是跳跃一个像素，三列也就是B,G,R
    //            for (int col = 0; col < colS*3; col+=3)
    //            {
    //                ptr[col+0] =  ptr[col+1];
    //                ptr[col+1] =  ptr[col+2];
    //                ptr[col+2] =  ptr[col+0];
    //            }
    //        }
    //    }
    //    iElaps=cpuSecond()-iStart;
    //    printf("Time elapsed %f sec\n",iElaps);

    //method 2 1.72s 172ms/per
    //    for(int j = 0;j<10;j++){

    //        for (int row = 0; row < rowS; row++)
    //        {
    //            Vec3b* ptr = img.ptr<Vec3b>(row);
    //            for (int col = 0; col < colS; col++)
    //            {
    //                ptr[col][0] =ptr[col][1];
    //                ptr[col][1] =  ptr[col][2];
    //                ptr[col][2] = ptr[col][0];
    //            }
    //        }
    //    }
    //    iElaps=cpuSecond()-iStart;
    //    printf("Time elapsed %f sec\n",iElaps);
    //method 3 0.4s   40ms/per
//        for(int j = 0;j<10;j++){

//            for (int row = 0;row < rowS; row++)
//            {
//                uchar *imagedata = img.ptr<uchar>(row);
//                for(int col = 0;col < colS;col++)
//                {
//                    imagedata[0] = imagedata[1];
//                    imagedata[1] =  imagedata[2];
//                    imagedata[2] =  imagedata[0];
//                    imagedata+=3;//指针偏移3
//                }
//            }
//        }
//            iElaps=cpuSecond()-iStart;
//            printf("Time elapsed %f sec\n",iElaps);
    //method 4 3.327s 330ms/per cols first
    //    4.2s 420ms/per if rows first
//        for(int k = 0;k<10;k++){
//            for(int j=0;j<img.cols;j++)
//            {
//                for(int i=0;i<img.rows;i++)
//                {
//                    img.at<Vec3b>(i,j)[0]=img.at<Vec3b>(i,j)[1];
//                    img.at<Vec3b>(i,j)[1]=img.at<Vec3b>(i,j)[2];
//                    img.at<Vec3b>(i,j)[2]=img.at<Vec3b>(i,j)[0];
//                }
//            }
//        }
//                iElaps=cpuSecond()-iStart;
//                printf("Time elapsed %f sec\n",iElaps);

    //method 6 0.63s 63ms/per
//    for(int k = 0;k<10;k++){
//        for(int i = 0;i<rowS;++i){
//            //            unsigned char* rowPtr = &src[i];
//            //            uchar *rowPtr = img.ptr<uchar>(i);
//            //               uchar *rowPtr = img.ptr<uchar>(i);
//           unsigned char *rowPtr = src+i*colS;
//            for(int j = 0;j<colS;j++){
//                //BGR
//                rowPtr[j]=rowPtr[j+1];
//                rowPtr[j+1]=rowPtr[j+2];
//                rowPtr[j+2]=rowPtr[j];
//                rowPtr+=3;
//            }
//        }

//    }
//    iElaps=cpuSecond()-iStart;
//    printf("Time elapsed %f sec\n",iElaps);
    //    float *kernal = new float[9];
    //    for (int i = 0;i<9;++i){
    //        kernal[i]=float(i);
    //    }
    //    float *k0 = kernal;
    //    float *k1 = kernal+3;
    //    float *k2 = kernal+6;
    //    //drop the Catch Miss problem
    //    std::cout<<k1[4]<<"   k2::  "<<k1[5]<<std::endl;
    //    cout << "Hello World!" << endl;
    return 0;
}
