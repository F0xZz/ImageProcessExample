线程问题

线程如果不设置异步机制

会存在打印问题，详解问题

[异步机制](https://blog.csdn.net/coolwriter/article/details/79883253?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_baidulandingword~default-0.no_search_link&spm=1001.2101.3001.4242)

1. easy demo

linux跨平台使用thread类

需要引用libpthread库

```c++
#include <iostream>
#include <thread>
#include <stdio.h>
#include <time.h>
using namespace std;
void t1()
{
    float a = 0;
    for (int i = 0; i < 10; ++i)
    {
        a=a+i;
    }
}
void t2()
{
    float a = 0;
    for (int i = 0; i < 10; ++i)
    {
        a=a+i;
    }
}
int main(){
    clock_t start,finish;
    double totaltime;

    start=clock();

    thread th1(t1);
    thread th2(t2);

    th1.join(); //等待th1执行完
    th2.join(); //等待th2执行完

    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"\n此程序的运行时间为"<<totaltime<<"秒！"<<endl;
    cout << "here is main\n\n";
    return 0;
}
```

2. 传参

对于x，使用的是引用传递，但是数字对象地址在主线程和子线程中地址不同。要在子线程中共享数据x，即地址相同，必须使用std::ref进行修饰，下面再在类对象作为参数传递时会有更详细说明

```c++
#include <iostream>
#include <thread>
 
void foo(const int  &x,char *mychar)
{
	std::cout << &x << "   " << &mychar << std::endl;
	std::cout << "正在运行的线程为：" << std::this_thread::get_id() << "线程的参数为： " << x <<"  "<<mychar<< std::endl;
	return;
}
 
int main()
{
	std::cout << "主线程的线程id为： " << std::this_thread::get_id() << std::endl;
	
	int x = 1;
	char mybuff[] = "This is a test";
	std::cout << &x << "   " << &mybuff << std::endl;
	std::thread second(foo, std::ref(x), mybuff);
	second.join();
 
	std::cout << "主线程运行结束" << std::endl;
	return 0;
}
```

```
std::thread threads[5];
for (int i = 0; i < 5; i++) 
{
        threads[i] = std::thread(thread_task, i + 1);
}

    std::cout << "Done spawning threads! Now wait for them to join\n";
    for (auto& t: threads) {
        t.join();
    }
```

