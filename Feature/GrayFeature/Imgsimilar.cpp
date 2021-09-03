//计算图片的指纹信息
//FEATURE_DIMS use for the featureVector dims = FEATURE_DIMS*FEATURE_DIMS
string ImageHashValue(Mat srcImg)
{
    Scalar mean;
    Scalar stddev;
    string resStr(FEATURE_DIMS*FEATURE_DIMS,'\0');
    if(srcImg.channels()==3){
        cv::cvtColor(srcImg,srcImg,CV_BGR2GRAY);
    }
    int index =0;
    cv::resize(srcImg,srcImg,Size(FEATURE_DIMS,FEATURE_DIMS));
    normalize(srcImg,srcImg,0,64,NORM_MINMAX, CV_8UC1, Mat());
    cv::meanStdDev( srcImg, mean, stddev );
    int average =mean.val[0];
    for (int i = 0;i<srcImg.rows;++i){
        for (int j = 0; j < srcImg.cols; ++j){
            if(srcImg.at<uchar>(i,j)>=average)
                resStr[index++]='1';
            else
                resStr[index++]='0';
        }
    }
    return resStr;
}

//根据指纹信息计算两幅图像的相似度
double ImageSimilarity(string &str1,string &str2)
{
    double similarity = 1.0;
    for(int i=0;i<FEATURE_DIMS*FEATURE_DIMS;i++)
    {
        char c1 = str1[i];
        char c2 = str2[i];
        if(c1!=c2)
            similarity = similarity -1.0/(FEATURE_DIMS*FEATURE_DIMS);
    }
    return similarity;
}
//根据指纹信息计算两幅图像的相似度

float Caculate_similartiy(Mat firstFrame,Mat secondFrame)
{
    string imgPrint1 = ImageHashValue(firstFrame);
    string imgPrint2 = ImageHashValue(secondFrame);
    double similarity = ImageSimilarity(imgPrint1,imgPrint2);
    std::cout<<"there are two similar img is value:" <<similarity<<std::endl;
    return similarity;
}
