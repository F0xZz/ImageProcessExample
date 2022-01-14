import numpy as np
from PIL import Image
import cv2
from torch import imag
def letterbox_image(image, size):
    
    '''resize image with unchanged aspect ratio using padding'''
    iw, ih = image.size
    img = cv2.cvtColor(np.asarray(image),cv2.COLOR_RGB2BGR)
    h, w = size
    print(h,w)
    print(ih,iw)
    if(h==ih and w==iw):
        print("no preprocess")
        return image

    scale = min(w/iw, h/ih)

    nw = int(iw*scale)
    nh = int(ih*scale)
    img = cv2.resize(img,(nw,nh),interpolation=cv2.INTER_LINEAR)
    image = Image.fromarray(cv2.cvtColor(img,cv2.COLOR_BGR2RGB))
    # image = image.resize((nw,nh), Image.BILINEAR)
    new_image = Image.new('RGB', size, (128,128,128))
    print(nw,nh)
       #set the tlx tly 
    new_image.paste(image, ((w-nw)//2, (h-nh)//2))

    new_image.save("dstpython.bmp")
    return new_image
def srcresize(image,w,h,iw,ih):
    scale = min(w/iw, h/ih)
    nw = int(iw*scale)
    nh = int(ih*scale)
    dx = (w-nw)//2
    dy = (h-nh)//2

    #---------------------------------#
    #   将图像多余的部分加上灰条
    #---------------------------------#
    # image       = image.resize((nw,nh), Image.BICUBIC)
    image       = image.resize((nw,nh), Image.BILINEAR)
    new_image   = Image.new('RGB', (w,h), (128,128,128))
    new_image.paste(image, (dx, dy))
    # new_image.save()
    image_data  = np.array(new_image, np.float32)

    return image_data
def opencvresize(img,size):
    ih,iw = img.shape[0:2]
    h, w = size
    # img = cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
    scale = min(w/iw, h/ih)
    nw = int(iw*scale)
    nh = int(ih*scale)
    dx = (w-nw)//2
    dy = (h-nh)//2
    img = cv2.resize(img,(nw,nh),interpolation=cv2.INTER_LINEAR)
    new_image = np.full((h,w,3),128,dtype=np.float32)
    
    # rect = [dx,dy,nw,nh]
    
    new_image[dy:dy+nh,dx:dx+nw]=img
    # cv2.imwrite("1.bmp",new_image)
    # print(new_image.dtype)
    return new_image
if __name__=="__main__":
    # a = np.full((30,26,3),128,dtype=np.uint8)
    # print(type(a))
    # print(a.shape)
    # cv2.imwrite("back.bmp",a)


    # img = Image.open("./F_004_04.jpg")
    test = cv2.imread("./test.jpg")
    print(test.shape)
    # print(test.shape[0:2])
    # print(type(test))
    # new_Img = letterbox_image(img,(32,32))
    # print(type(new_Img))
    # srcT = srcresize(img,32,32,26,30)
    # print(type(srcT))
    image_data = opencvresize(test,(32,32))
    a = np.expand_dims(np.array(image_data, np.float32), 0)
    print(a.shape)
    image_data  = np.transpose(np.expand_dims(np.array(image_data, np.float32), 0), (0, 3, 1, 2))
    print(image_data.shape)

