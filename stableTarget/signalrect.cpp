#include "signalrect.h"
/*   init the paraments
 *   store the paraments
 */
SignalRect::SignalRect(int Peroid,int thresh)
{
    savePeroid = Peroid;
    innerCount = 0;
    FireSignalCount = 0;
    countFlag = false;
    fireThres = thresh;
    heatMap= cv::Mat::zeros(cv::Size(1920,1080),CV_8U);
    std::vector<std::vector<cv::Rect>>().swap(longSerialTimeRect);
}
int SignalRect::innerPeroid(std::vector<cv::Rect> eachFrameRect){
    if(innerCount<savePeroid){
        if(innerCount==0&&countFlag==false){
            if(eachFrameRect.size()==0){
                return -1; //return out the None Rect State
            }else {
                countFlag=true;
            }
        }
        if(countFlag==true){
            ++innerCount;
            if(eachFrameRect.size()==0){
                return 0; //No Fire Count ;
            }else{
                ++FireSignalCount;
                Store_Rect(eachFrameRect);
                return 1; //Has Fire Count ;
            }
        }
    }

    else {
        if(FireSignalCount>fireThres){
            heatMap = cv::Mat::zeros(cv::Size(1920,1080),CV_8U);
            if(trackerRect()){
                innerCount = 0;
                FireSignalCount = 0;
                countFlag = false;
                releaseStore_Rect();
                return 55; // there was an Fire Signal
            }
            innerCount = 0;
            FireSignalCount = 0;
            countFlag = false;
            releaseStore_Rect();
            return 999; // there was not a stable rect
        }
        innerCount = 0;
        FireSignalCount = 0;
        countFlag = false;
        releaseStore_Rect();
        return 666; //A peroid has end and not get the thresh
    }
}
int SignalRect::Store_Rect(std::vector<cv::Rect> in){
    longSerialTimeRect.push_back(in);
    return 0;
}
int SignalRect::releaseStore_Rect(){
    std::vector<std::vector<cv::Rect>>().swap(longSerialTimeRect);
    return 0;
}
//This rect use for the store the possible rect
int SignalRect::trackerRect()
{
    for(int i = 0 ; i <longSerialTimeRect.size(); ++i){
        convertToHeatMap(longSerialTimeRect[i]);
    }
    cv::imshow("stepHeatMap",heatMap);
    cv::waitKey();
    cv::destroyAllWindows();
    cv::threshold(heatMap,heatMap,150,255,cv::THRESH_BINARY);
    //    cv::imshow("stepHeatMap2",heatMap);
    //    cv::waitKey();
    //    cv::destroyAllWindows();
    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(heatMap, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    std::vector<cv::Rect> boundRect(contours.size());
    std::cout<<"this method use detect the "<< contours.size()<<" rect"<<std::endl;
    if(contours.size()==0){
        return 0;
    }
    for (int i = 0; i < contours.size(); i++)
    {
        boundRect[i] = cv::boundingRect(contours[i]);
        //        rectangle(dst, boundRect[i], Scalar(0, 255, 0), 2);//在result上绘制正外接矩形
    }
    outHeatMapRect=boundRect;
    //    return 0; // there was no fire
    return 1; // there was a fire possible
}
void SignalRect::convertToHeatMap(std::vector<cv::Rect> eachRect){
    int stepCount = 255/FireSignalCount;
    //    std::cout<<"stddd"<<stepCount<<std::endl;
    for(int i = 0;i < eachRect.size();++i){
        int tx = eachRect[i].tl().x;
        int ty = eachRect[i].tl().y;
        int cx = tx+eachRect[i].width/2;
        int cy = ty+eachRect[i].height/2;
        int ctx = cx - (eachRect[i].width/2)/2;
        int cty = cy - (eachRect[i].height/2)/2;
        for (int k = ty; k < ty+std::max(eachRect[i].height,3) ; ++k){
            for (int q = tx+2; q < tx+std::max((eachRect[i].width-2),3) ; ++q){
                heatMap.at<uchar>(k,q)+=stepCount;
            }
        } 
    }
}
std::vector<cv::Rect> SignalRect::getRect(){
    return outHeatMapRect;
}
void SignalRect::drawRect(cv::Mat src){
    for (int i = 0; i < outHeatMapRect.size(); i++){
        cv::rectangle(src, outHeatMapRect[i], cv::Scalar(0, 125, 255), 2);//在result上绘制正外接矩形
    }
    cv::imwrite("dst.jpg",src);
}
