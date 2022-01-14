关于这篇文章本来项目需求做的NCNN部署和mobilenet的方案

记录关于前处理部分对齐Resize

其中Pytorch训练过程中，有部分采用的PIL库进行缩放，而对于Opencv使用的缩放过程方式不同，具体细微影响的话

测试了下PIL的BILinear和OpenCV的BILinear，差距还是蛮多的在32x32的小图中，像素值就存在未对齐情况，大概相差100+个像素，我给出的测试方式是。

```
img = cv2.imread("./test.jpg")
dst = cv2.resize()#opencv的resize过程
cv2.imwrite("resopencv.bmp",dst)
#PIL
img = Image.open()
img.resize()
img.save(".bmp")
#通通保存成bmp格式后再通道一个通道的比对，求方便直接灰度进来比对，其实差距就有体现了
```

具体解释原因参考大老师的文章:

