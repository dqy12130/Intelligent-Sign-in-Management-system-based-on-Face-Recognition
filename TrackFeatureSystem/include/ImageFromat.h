#ifndef IMAGEFROMAT_H
#define IMAGEFROMAT_H
#include<faceincludefile.h>

class Q_DECL_EXPORT  ImageFromat
{
public:
    /*OPenCV和Qt图片格式的相互转换*/
    static QPixmap MatToQPixMap( const cv::Mat& frame);//Mat转QPixmap
    static QImage MatToQImage  (const cv::Mat &frame);//Mat转QImage
    static  QByteArray MatToQByteArray(const cv::Mat& frame);//Map转QByteArray
    /*OPenCV和Qt图片格式的相互转换*/
    static cv::Mat  QPixmapToMat(const QPixmap&);//QPixmap转Mat
    static cv::Mat QImageToMat(const QImage&);//QImage转Mat
    static cv::Mat QByteArrayToMat(const QByteArray&);//QByteArray转Mat

    /*OPenCV和Qt图片格式的相互转换*/
    static IplImage QPixmapToIplImage(const QPixmap&);//QPixmap转IplImage
    static IplImage QImageToIplImage(const QImage&);//QImage转IplImage
    static IplImage QByteArrayToIplImage(const QByteArray&);//QByteArray转IplImage

    /*QPixmap 和QImage互转*/
    static QImage QPixmapToQImage(QPixmap);
    static QPixmap  QImageToQPixmap(QImage);

    /*OPenCVMat和IplImage相互转换*/
    static cv::Mat IplImageToMat(const IplImage&);//IplImage转Mat
    static IplImage MatToIplImage(const cv::Mat&);//Mat转IplImage

    static bool MatIsNull(const cv::Mat &mat);//判断Mat是否为空
    static bool IplImageIsNull(const IplImage & img);//判断IplImage是否为空
    static bool QPixmapIsNull(const QPixmap & Pixmap);//判断QPixmap是否为空
    static bool QImageIsNull(const QImage &img);//判断QImage是否为空
    static bool QByteArrayIsNull(const QByteArray & byte);//判断QByteArray内的数据是否为空

};



#endif // IMAGEFROMAT_H
