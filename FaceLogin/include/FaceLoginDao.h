#ifndef FaceLoginDao_H
#define FaceLoginDao_H
#include "MySqlUtils.h"
#include <QVector>
#include "StudentInfo.h"
#include<TeacherInfo.h>
#include<QFile>
#include<QByteArray>
class FaceLoginDao
{
public:
    FaceLoginDao();
    ~FaceLoginDao();
public:
    //获取所有学生的人脸信息
    QVector<StudentInfo> getAllStuInfo();
    QVector<StudentInfo> getStuInfoByLabId(QString);

    QVector<TeacherInfo> getTeacherInfoByLabId(QString);
private:
    QSqlDatabase db;
};

#endif // FaceLoginDao_H
