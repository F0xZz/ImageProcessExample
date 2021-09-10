Mat CustomThread(Mat src,int threadIndex){

    thread MatThreadProcess[threadIndex];

    int srcHeight = src.size().height;
    int srcWidth = src.size().width;
    int cropHeight = srcHeight/threadIndex;

    Mat DstTemp;

    vector<Mat> dstThreadMat=vector<Mat>(threadIndex);

    Rect initRect(0,0,srcWidth,cropHeight);
    Point movePoint(0,cropHeight);

    //CREATE THE THREAD
    for (int i =0;i<threadIndex;++i){
        MatThreadProcess[i]=thread(&colorFilter::ThreadUseColorRule,&cfProcess,
                                   src(initRect),std::ref(dstThreadMat.at(i)));
        initRect = initRect+movePoint;
    }

    //RUN THE THREAD
    for (auto& t: MatThreadProcess){
        t.join();
    }

    // MIX THE CROP IMAGE
    for(int j = 0;j<threadIndex-1;++j){
        if(j==threadIndex-2){
            vconcat(dstThreadMat.at(j),
                    dstThreadMat.at(j+1),
                    DstTemp);
        }
        vconcat(dstThreadMat.at(j),
                dstThreadMat.at(j+1),
                dstThreadMat.at(j+1));
    }
    return DstTemp;
}
