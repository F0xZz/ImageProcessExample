# MultipleThread Image Process

How to Use

---

Just set the Image Path and Run will show the speed 

Test On the 1920*1080 pixel IMG

IF use only one Thread it will cost 6000ms

Test on the 4 thread process it cost only 1500ms~

单图测试

Linux依赖libpthread.so

Win可直接使用

多线程测试图片像素点遍历 1920x1080图像下

单线程 整图遍历并计算过滤为 60ms

4线程并发并行， 进行过滤为 15ms~20ms 左右
