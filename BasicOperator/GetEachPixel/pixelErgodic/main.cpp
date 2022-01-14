#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv.hpp>


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
//1080p 69ms 4k 460ms
cv::Mat FireColorRule(cv::Mat src){
    int row = src.rows;
    int col = src.cols;
    //    std::cout<<"SSS"<<std::endl;
    cv::Mat imgHSV;
    cv::cvtColor(src, imgHSV, cv::COLOR_BGR2HSV);
    cv::Mat tempDst;
    int B,G,R,H,S,V;
    tempDst= cv::Mat::zeros(src.size(),CV_8U);
    for (int i = 0; i <row; i++) {
        //        uchar* ptr = img.ptr<uchar>(row);
        for (int j = 0; j < col; j++)
        {

            B = src.at<cv::Vec3b>(i, j)[0];
            //            std::cout<<"BB"<<B<<std::endl;
            G = src.at<cv::Vec3b>(i, j)[1];
            R = src.at<cv::Vec3b>(i, j)[2];

            H = imgHSV.at<cv::Vec3b>(i, j)[0];
            S = imgHSV.at<cv::Vec3b>(i, j)[1];
            V = imgHSV.at<cv::Vec3b>(i, j)[2];

            //            if(R>G&&G>B)
            //            {
            //                if((G/(R+255.0))>0.25 && (G/(R+255.0))<0.65)
            //                {
            //                    if((B/(R+255.0))>0.05 && (B/(R+255.0))<0.45)
            //                    {
            //                        if((B/(G+255.0))>0.20 && (B/(G+255.0))<0.60){
            //                            if(H<60&&S>20&&V>100){(S > ((255 - R) * 0.33))?tempDst.at<uchar>(i,j)=255:tempDst.at<uchar>(i,j)=0;}
            //                            //                            tempDst.at<uchar>(i,j)=255;
            //                        }
            //                    }
            //                }
            //            }
            if(R>G&&G>B&&
                    (G/(R+255.0))>0.25&&(G/(R+255.0))<0.65&&
                    (B/(R+255.0))>0.05 && (B/(R+255.0))<0.45&&
                    (B/(G+255.0))>0.20 && (B/(G+255.0))<0.60){
                if(H<60&&S>20&&V>100){(S > ((255 - R) * 0.33))?tempDst.at<uchar>(i,j)=255:tempDst.at<uchar>(i,j)=0;}
            }

        }
    }
    return tempDst;
}
//1080p 38ms 4k 230ms
cv::Mat colorOptim(cv::Mat _temp){
    int row = _temp.rows;
    int col = _temp.cols;
    cv::Mat tempDst= cv::Mat::zeros(_temp.size(),CV_8U);
    cv::Mat imgHSV ;
    cv::cvtColor(_temp, imgHSV, cv::COLOR_BGR2HSV);
    int B,G,R,H,S,V;
    //    if(row%3 == 0){
    //    }
    for(int j = 0;j<row;++j){
        //        cv::Vec3b *ptr = _temp.ptr<cv::Vec3b>(j);
        //        cv::Vec3b *ptrhsv = imgHSV.ptr<cv::Vec3b>(j);
        const uchar* inData=_temp.ptr<uchar>(j);
        const uchar* inDataHSV = imgHSV.ptr<uchar>(j);
        //B G Rsave method
        for(int i = 0;i<col;++i){
            //B:ptr[col][0] G:ptr[col][1] R:ptr[col][2]
            //
            //            int B = ptr[col][0];
            //            int G = ptr[col][1];
            //            int R = ptr[col][2];
            int ptrnum = i*_temp.channels();
            B = inData[ptrnum];
            G = inData[ptrnum+1];
            R = inData[ptrnum+2];
            H=inDataHSV[ptrnum];
            S=inDataHSV[ptrnum+1];
            V=inDataHSV[ptrnum+2];
            if(R>G&&G>B&&
                    (G/(R+255.0))>0.25&&(G/(R+255.0))<0.65&&
                    (B/(R+255.0))>0.05 && (B/(R+255.0))<0.45&&
                    (B/(G+255.0))>0.20 && (B/(G+255.0))<0.60){
                if(H<60&&S>20&&V>100){(S > ((255 - R) * 0.33))?tempDst.at<uchar>(j,i)=255:tempDst.at<uchar>(j,i)=0;}
            }
        }
    }
    return tempDst;
}
//1080p 34ms 4k 203ms
cv::Mat colorOptimpro(cv::Mat _temp){
    int row = _temp.rows;
    int col = _temp.cols;
    cv::Mat tempDst= cv::Mat::zeros(_temp.size(),CV_8U);
    cv::Mat imgHSV ;
    cv::cvtColor(_temp, imgHSV, cv::COLOR_BGR2HSV);
    int B,G,R,H,S,V;
    for(int j = 0;j<row;++j){

        const uchar* inData=_temp.ptr<uchar>(j);
        const uchar* inDataHSV = imgHSV.ptr<uchar>(j);

        //B G Rsave method
        for(int i = 0;i<col;++i){
            B = inData[0];
            G = inData[1];
            R = inData[2];
            H = inDataHSV[0];
            S = inDataHSV[1];
            V = inDataHSV[2];
            inData+=3;
            inDataHSV+=3;
            if(R>G&&G>B&&
                    (G/(R+255.0))>0.25&&(G/(R+255.0))<0.65&&
                    (B/(R+255.0))>0.05 && (B/(R+255.0))<0.45&&
                    (B/(G+255.0))>0.20 && (B/(G+255.0))<0.60){
                if(H<60&&S>20&&V>100){(S > ((255 - R) * 0.33))?tempDst.at<uchar>(j,i)=255:tempDst.at<uchar>(j,i)=0;}
            }
        }
    }
    return tempDst;
}
//1080p 34ms 4k 200ms
cv::Mat colorOptimpromax(cv::Mat _temp){
    int row = _temp.rows;
    int col = _temp.cols;
    cv::Mat tempDst= cv::Mat::zeros(_temp.size(),CV_8U);
    cv::Mat imgHSV ;
    cv::cvtColor(_temp, imgHSV, cv::COLOR_BGR2HSV);
    int B,G,R,H,S,V;
    int B2,G2,R2,H2,S2,V2;
    int B3,G3,R3,H3,S3,V3;
    for(int j = 0;j<row;j=j+3){

        const uchar* inData =_temp.ptr<uchar>(j);
        const uchar* inDataHSV = imgHSV.ptr<uchar>(j);
        const uchar* inData2 =_temp.ptr<uchar>(j+1);
        const uchar* inDataHSV2 = imgHSV.ptr<uchar>(j+1);
        const uchar* inData3 =_temp.ptr<uchar>(j+2);
        const uchar* inDataHSV3 = imgHSV.ptr<uchar>(j+2);
        //B G Rsave method
        for(int i = 0;i<col;++i){
            B = inData[0];
            G = inData[1];
            R = inData[2];
            H = inDataHSV[0];
            S = inDataHSV[1];
            V = inDataHSV[2];
            inData+=3;
            inDataHSV+=3;
            B2 = inData2[0];
            G2 = inData2[1];
            R2 = inData2[2];
            H2 = inDataHSV2[0];
            S2 = inDataHSV2[1];
            V2 = inDataHSV2[2];
            inData2+=3;
            inDataHSV2+=3;
            B3 = inData3[0];
            G3 = inData3[1];
            R3 = inData3[2];
            H3 = inDataHSV3[0];
            S3 = inDataHSV3[1];
            V3 = inDataHSV3[2];
            inData3+=3;
            inDataHSV3+=3;
            if(R>G&&G>B&&
                    (G/(R+255.0))>0.25&&(G/(R+255.0))<0.65&&
                    (B/(R+255.0))>0.05 && (B/(R+255.0))<0.45&&
                    (B/(G+255.0))>0.20 && (B/(G+255.0))<0.60){
                if(H<60&&S>20&&V>100){(S > ((255 - R) * 0.33))?tempDst.at<uchar>(j,i)=255:tempDst.at<uchar>(j,i)=0;}
            }
            if(R2>G2&&G2>B2&&
                    (G2/(R2+255.0))>0.25&&(G2/(R2+255.0))<0.65&&
                    (B2/(R2+255.0))>0.05 && (B2/(R2+255.0))<0.45&&
                    (B2/(G2+255.0))>0.20 && (B2/(G2+255.0))<0.60){
                if(H2<60&&S2>20&&V2>100){(S2 > ((255 - R2) * 0.33))?tempDst.at<uchar>(j+1,i)=255:tempDst.at<uchar>(j+1,i)=0;}
            }
            if(R3>G3&&G3>B3&&
                    (G3/(R3+255.0))>0.25&&(G3/(R3+255.0))<0.65&&
                    (B3/(R3+255.0))>0.05 && (B3/(R3+255.0))<0.45&&
                    (B3/(G3+255.0))>0.20 && (B3/(G3+255.0))<0.60){
                if(H3<60&&S3>20&&V3>100){(S3 > ((255 - R3) * 0.33))?tempDst.at<uchar>(j+2,i)=255:tempDst.at<uchar>(j+2,i)=0;}
            }
        }
    }
    return tempDst;
}
double cpuSecond()
{
    struct timeval tp;
    gettimeofday(&tp,NULL);
    return((double)tp.tv_sec+(double)tp.tv_usec*1e-6);
}
using namespace std;

int main()
{


    cv::Mat tempoptim,tempelder,tempoptimpro,tempoptimpromax;
cv::Mat imgtest = cv::imread("./car.jpg");
    for(int j = 0;j<10;++j){

        tempelder = FireColorRule(imgtest);
    }


    double iStart=cpuSecond();
    for(int j = 0;j<100;++j){
     
        tempelder = FireColorRule(imgtest);
    }
    double time = cpuSecond()-iStart;
    printf("Time elapsed %f sec\n",time);

    iStart = cpuSecond();
    for(int i = 0;i<100;++i){
        tempoptim = colorOptim(imgtest);
    }
    time = cpuSecond()-iStart;
    printf("Time elapsed2 %f sec\n",time);
    iStart = cpuSecond();
    for(int i = 0;i<100;++i){
        tempoptimpro = colorOptimpro(imgtest);
    }
    time = cpuSecond()-iStart;
    printf("Time elapsed3 %f sec\n",time);

    iStart = cpuSecond();
    for(int i = 0;i<100;++i){
        tempoptimpromax = colorOptimpromax(imgtest);
    }
    time = cpuSecond()-iStart;
    printf("Time elapsed4 %f sec\n",time);
    cv::Mat compare;
    compare =tempelder-tempoptim;

    int sum = cv::countNonZero(compare);
    printf("sumcompare %d \n",sum);

    compare =tempelder-tempoptimpro;
    sum = cv::countNonZero(compare);

    printf("sumcompare2 %d\n",sum);

    compare =tempelder-tempoptimpro;
    sum = cv::countNonZero(compare);

    printf("sumcompare3 %d\n",sum);


    return 0;
}
