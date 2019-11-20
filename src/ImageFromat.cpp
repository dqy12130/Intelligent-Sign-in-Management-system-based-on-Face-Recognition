#include "ImageFromat.h"

QPixmap ImageFromat::MatToQPixMap(const cv::Mat &frame)//Mat转QPixmap
{
    QPixmap pixma;
    bool flag=MatIsNull(frame);//检测frame是否有效
    QImage img=MatToQImage(frame);//将Mat转化为QImage
    if(img.byteCount()<=1)
        ;//img若数据无效则进行空操作
    else
        pixma=QPixmap::fromImage(img);//QImage转换成QPixmap
    return pixma;
}

QImage ImageFromat::MatToQImage(const cv::Mat &mat)//Mat转QImage
{
    QImage img(0);
    if(mat.empty()==true)
        return img;
    switch (mat.channels())
    {
    case 3://彩色图片
    {
        cv::cvtColor(mat, mat, CV_BGR2RGB);//BGR转RGB
        img = QImage(mat.data,mat.cols, mat.rows,mat.cols*mat.channels(),QImage::Format_RGB888);
    };break;
    case 1://灰度图片
    {
        img = QImage((const unsigned char*)(mat.data),mat.cols, mat.rows,mat.cols*mat.channels(),QImage::Format_Indexed8);
        QVector<QRgb> colorFroamt;

        for (int i = 0; i<256; i++)
        {
            colorFroamt.push_back(qRgb(i, i, i));
        }
        img.setColorTable(colorFroamt);//把qImg的颜色按像素点的颜色给设置
    } ;break;
    default: img = QImage((const unsigned char*)(mat.data),mat.cols, mat.rows,mat.cols*mat.channels(),QImage::Format_RGB888);
        break;
    }
    return img;
}

QByteArray ImageFromat::MatToQByteArray(const cv::Mat& frame)//Map转QByteArray
{
    QByteArray  imageByte(0);
    bool flag=MatIsNull(frame);//检测frame是否有效
    if(flag==false)
        return imageByte;
    QImage img= MatToQImage(frame);//将Mat转化为QImage
    QBuffer buffer(&imageByte);//数据流
    // buffer.open(QIODevice::ReadWrite);//读写文件
    // img.save(&buffer, "png");//写入数据
    return imageByte;
}


cv::Mat  ImageFromat::QPixmapToMat(const QPixmap& frame)//QPixmap转Mat
{
    //先构造一个QImage，通过QPIxmap转成QIMage后转成Mat
    cv::Mat mat;
    if(!frame.isNull())
        return mat;
    QImage image;
    QPainter pen;
    image=frame.toImage();
    mat=QImageToMat(image);
    return mat;
}

cv::Mat ImageFromat::QImageToMat(const QImage &image)
{
    cv::Mat mat;
    if(!image.isNull())
        return  mat;

    qDebug() << image.format();
    switch(image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    }
    return mat;
}

cv::Mat ImageFromat::QByteArrayToMat(const QByteArray& byteImg)//QByteArray转Mat
{
    //通过构造一个QImage，将QByteArray中的数据构造成一个QImage，然后转换成一个Mat
    QImage image;
    cv::Mat mat;
    if(!byteImg.isEmpty())//字节数组为空
        return  mat;
    image.loadFromData(byteImg);
    //    if(!image.isNull())//QImage构造失败（为空）
    //        return  mat;
    mat=QImageToMat(image);//图片转换
    return  mat;
}

IplImage ImageFromat::QPixmapToIplImage(const QPixmap& frame)//QPixmap转IplImage
{
    //通过将QPixmap构造成一个Mat，然后由Mat转换成IplImage
    cv::Mat mat;
    IplImage lpImage;
    if(!frame.isNull())//为空
        return lpImage;
    mat=QPixmapToMat(frame);

    bool flag=MatIsNull(mat);//判断mat是否有效
    if(flag=false)
        return  lpImage;
    lpImage=(IplImage)mat;
    return  lpImage;
}

IplImage ImageFromat::QImageToIplImage(const QImage& img)//QImage转IplImage
{
    //通过构造一个QImage，将其转换为Mat，然后通过Mat转换成IplImage
    cv::Mat mat;
    IplImage lpImage;
    if(!img.isNull())//为空
        return  lpImage;
    mat=QImageToMat(img);//QImage转Mat
    lpImage=MatToIplImage(mat);//Mat转IplImage
    return  lpImage;
}

IplImage ImageFromat::QByteArrayToIplImage(const QByteArray& byteImg)//QByteArray转IplImage
{
    //通过构造Mat,然后通过Mat转换成IplImage
    cv::Mat mat;
    IplImage lpImage;
    if (!byteImg.isEmpty())
        return lpImage;
    mat=QByteArrayToMat(byteImg);
    lpImage=  MatToIplImage(mat);
    return  lpImage;
}

cv::Mat ImageFromat::IplImageToMat(const IplImage& lpImage)//IplImage转Mat
{
    cv::Mat mat;
    mat=cv::cvarrToMat(&lpImage);
    MatIsNull(mat);
    return  mat;
}
IplImage ImageFromat::MatToIplImage(const cv::Mat& mat)//Mat转IplImage
{
    IplImage lpImage;
    bool flag=MatIsNull(mat);//判断mat是否有效
    if(flag=false)
        return  lpImage;
    lpImage=(IplImage)mat;
    return  lpImage;
}

QImage ImageFromat::QPixmapToQImage(QPixmap pixmap)
{
    QImage img;
    if(pixmap.isNull()==true)
        return  img;
    img=pixmap.toImage();
    return  img;
}
QPixmap ImageFromat::QImageToQPixmap(QImage img)
{
    QPixmap pixmap;
    if(img.isNull()==true)
        return  pixmap;
    pixmap=QPixmap::fromImage(img);
    return  pixmap;
}

bool ImageFromat::MatIsNull(const cv::Mat &mat)//判断Mat是否为空
{
    if(mat.empty()==true)
        return  false;//不为空
    else
        return   true;//为空
}

bool  ImageFromat::IplImageIsNull( const IplImage & img)//判断IplImage是否为空
{
    if(img.imageSize<=0)
    {
        return  false;
    }
    else
        return  true;
}

bool ImageFromat::QPixmapIsNull(const QPixmap & Pixmap)
{
    if(Pixmap.isNull()==true)
        return  false;//为空
    else
        return  true;
}
bool ImageFromat::QImageIsNull(const QImage &img)
{
    if(img.isNull()==true)
        return  false;//为空
    else
        return  true;
}

bool ImageFromat::QByteArrayIsNull(const QByteArray & byte)
{

    if(byte.isEmpty()==true)
        return  false;//为空
    else
        return  true;
}














