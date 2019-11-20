#ifndef TEACHERINFO_H
#define TEACHERINFO_H

#include <QMap>
#include <QString>
#include <QVector>

//在登录后立刻初始化
class TeacherInfo
{
public:
    TeacherInfo();
public:
    QString getTeacherId() const;
    void setTeacherId(const QString &value);
    QString getName() const;
    void setName(const QString &value);
    QString getSex() const;
    void setSex(const QString &value);
    QString getDepartment() const;
    void setDepartment(const QString &value);
    QMap<int, QString> getLabs() const;
    void setLabs(const QMap<int, QString> &value);

    QByteArray getFaceFeature() const;
    void setFaceFeature(const QByteArray &value);

private:
    QString teacherId;                      //教职工号
    QString name;                           //姓名
    QString sex;                            //性别
    QString department;                     //部门
    QMap<int,QString> labs;                 //所管辖的所有实验室的id-名称
    QByteArray faceFeature;     //特征值
};

#endif // TEACHERINFO_H
