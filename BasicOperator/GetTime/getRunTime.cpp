#include <iostream>
#include <time.h>
#include <ctime>
#include <sys/timeb.h>
using namespace std;

long long getSystemTime(){
    timeb t;
    ftime(&t);
    return t.time * 1000 + t.millitm;
}
int main()
{
    time_t tv;
    tv = time(NULL);//time(&tv); get current time;
    std::cout << tv << std::endl;//距离1970-01-01 00:00:00经历的秒数
    std::cout << ctime(&tv) << std::endl;//显示当前时间
    tm *local;
    local = localtime(&tv);
    std::cout << asctime(local) << std::endl;//显示当前时
    long long t_start = getSystemTime();
    int i =0;
    while(i<100){
        Mat img = cv::imread("/home/ubuntu/Pictures/vlcsnap-2021-09-06-10h26m52s689.png");
        ++i;
    }
    long long t_end = getSystemTime();
    std::cout << t_end - t_start <<"ms"<< std::endl;
    return 0;
}
