#ifndef SIGNALRECT_H
#define SIGNALRECT_H
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

class SignalRect
{
private:
    std::vector<cv::Rect> outHeatMapRect;
    cv::Mat heatMap; //Use for the create RectHeatMap
    int savePeroid;
    int innerCount,FireSignalCount;
    std::vector<std::vector<cv::Rect>> longSerialTimeRect;
    bool countFlag;
    int fireThres;
    int releaseStore_Rect();

public:
    SignalRect(int Peroid,int thresh);
    int innerPeroid(std::vector<cv::Rect> eachFrameRect);
    int Store_Rect(std::vector<cv::Rect> in);
    int trackerRect();
    void convertToHeatMap(std::vector<cv::Rect> eachRect);
    std::vector<cv::Rect> getRect();
    void drawRect(cv::Mat src);
};

#endif // SIGNALRECT_H
