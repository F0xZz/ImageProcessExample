# 图像遍历取值运算

取值运算方式不同，取值的运算时间也不同

大致分为地址指针偏移取值，直接寻址取值

总共测了5种方式，在Main.cpp中显示，测试在4400*3300图像上，测试时CPU在测试其他程序，但是总体是不影响测试表现。

57ms左右单张

```
//        for (int row = 0; row < rowS; row++)
//        {
//            uchar* ptr = img.ptr<uchar>(row);
//            //每一次跳跃三列，也就是跳跃一个像素，三列也就是B,G,R
//            for (int col = 0; col < colS*3; col+=3)
//            {
//                ptr[col+0] =  ptr[col+1];
//                ptr[col+1] =  ptr[col+2];
//                ptr[col+2] =  ptr[col+0];
//            }
//        }
//    }
```

172ms单张

```
//    for(int j = 0;j<10;j++){
//        for (int row = 0; row < rowS; row++)
//        {
//            Vec3b* ptr = img.ptr<Vec3b>(row);
//            for (int col = 0; col < colS; col++)
//            {
//                ptr[col][0] =ptr[col][1];
//                ptr[col][1] =  ptr[col][2];
//                ptr[col][2] = ptr[col][0];
//            }
//        }
//    }
```

40ms左右单张

```
//        for(int j = 0;j<10;j++){
//            for (int row = 0;row < rowS; row++)
//            {
//                uchar *imagedata = img.ptr<uchar>(row);
//                for(int col = 0;col < colS;col++)
//                {
//                    imagedata[0] = imagedata[1];
//                    imagedata[1] =  imagedata[2];
//                    imagedata[2] =  imagedata[0];
//                    imagedata+=3;//指针偏移3
//                }
//            }
//        }
```

400ms单张

```
//        for(int k = 0;k<10;k++){
//            for(int j=0;j<img.cols;j++)
//            {
//                for(int i=0;i<img.rows;i++)
//                {
//                    img.at<Vec3b>(i,j)[0]=img.at<Vec3b>(i,j)[1];
//                    img.at<Vec3b>(i,j)[1]=img.at<Vec3b>(i,j)[2];
//                    img.at<Vec3b>(i,j)[2]=img.at<Vec3b>(i,j)[0];
//                }
//            }
//        }
```

