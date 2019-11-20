#include "TeacherInfo.h"

TeacherInfo::TeacherInfo()
{

}

QMap<int, QString> TeacherInfo::getLabs() const
{
    return labs;
}

void TeacherInfo::setLabs(const QMap<int, QString> &value)
{
    labs = value;
}

QByteArray TeacherInfo::getFaceFeature() const
{
    return faceFeature;
}

void TeacherInfo::setFaceFeature(const QByteArray &value)
{
    faceFeature = value;
}

QString TeacherInfo::getDepartment() const
{
    return department;
}

void TeacherInfo::setDepartment(const QString &value)
{
    department = value;
}

QString TeacherInfo::getSex() const
{
    return sex;
}

void TeacherInfo::setSex(const QString &value)
{
    sex = value;
}

QString TeacherInfo::getName() const
{
    return name;
}

void TeacherInfo::setName(const QString &value)
{
    name = value;
}

QString TeacherInfo::getTeacherId() const
{
    return teacherId;
}

void TeacherInfo::setTeacherId(const QString &value)
{
    teacherId = value;
}


