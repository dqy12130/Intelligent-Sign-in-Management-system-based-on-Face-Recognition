#ifndef FaceLoginService_H
#define FaceLoginService_H

#include "FaceLoginDao.h"
#include "ArcSoftFaceUtils.h"
#include <QObject>
#include<QTime>
#include<QMap>
#include<QThread>
#include<StudentInfo.h>
class FaceLoginService:public QObject
{
    Q_OBJECT
public:
    FaceLoginService();
    //重写
    FaceLoginService(QString currentActiveLab);
    ~FaceLoginService();
private:
    FaceLoginDao* signDao;
    //人脸识别引擎句柄
    MHandle handle;
    //存放人脸库
    QVector<StudentInfo> studentsInfo;
    QVector<TeacherInfo> teacherInfo;
signals:
    //人脸比对完成，发送结果

    //void faceResult(float value,StudentInfo stuInfo);//赵子轩
    void faceResult(float value,TeacherInfo teaInfo);

public slots:
    //进行特征值提取等一些工作
    void faceWork(QImage image);
};

#endif // FaceLoginService_H
