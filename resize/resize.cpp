#include <iostream>
#include "benchmark.h"
#include "cpu.h"
//#include "gpu.h"
#include "datareader.h"
#include "net.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
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
cv::Mat preprocess(cv::Mat in,int dstw ,int dsth){

    int srch = in.size().height;
    int srcw = in.size().width;
    if(srch==dsth&&srcw==dstw){
        return in;
    }
    float ration = std::min(1.0*dstw/srcw,1.0*dsth/srch);
    cv::Size size = cv::Size(int(srcw*ration),int(srch*ration));
    cv::Mat backgridimg = cv::Mat(dsth,dstw,CV_8UC3,cv::Scalar(128,128,128));
    cv::Mat medianimg;
    //    bgr.resize(size);
    cv::resize(in,medianimg,size,cv::INTER_LINEAR);

    // x y w h --> convert  size.height size.width
    cv::Rect dstrect = cv::Rect((dstw-size.width)/2,(dsth-size.height)/2,
                                size.width,size.height);
    medianimg.copyTo(backgridimg(dstrect));
//    cv::imwrite("dst.bmp",backgridimg);
    return backgridimg;
}
int main()
{

    cv::Mat bgr = cv::imread("./test.jpg");

    bgr=preprocess(bgr,32,32);

    cv::Mat img;

    cv::cvtColor(bgr,img,CV_BGR2RGB);

    int w = bgr.size().width;
    int h = bgr.size().height;

    ncnn::Mat in = ncnn::Mat::from_pixels(img.data,ncnn::Mat::PIXEL_RGB,w,h);
return 0;
}
