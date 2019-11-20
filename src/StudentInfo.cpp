/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao.Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     StudentInfo.cpp                                                 *
*  @brief    学生信息                                                         *
*                                                                            *
*  @author   Zixuan Zhao                                                     *
*  @email    zxZhao1998@gmail.com                                            *
*  @version  1.0.0.1                                                         *
*  @date                                                                     *
*  @license  GNU General Public License (GPL)                                *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2019/09/10 | 1.0.0.1   | Zixuan.Zhao    | Create file                     *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#include "StudentInfo.h"

#include <QBuffer>

StudentInfo::StudentInfo()
{

}

QString StudentInfo::getStudentId() const
{
    return studentId;
}

void StudentInfo::setStudentId(const QString &value)
{
    studentId = value;
}

QString StudentInfo::getName() const
{
    return name;
}

void StudentInfo::setName(const QString &value)
{
    name = value;
}

QString StudentInfo::getSex() const
{
    return sex;
}

void StudentInfo::setSex(const QString &value)
{
    sex = value;
}

QString StudentInfo::getGrade() const
{
    return QString::number(grade);
}

void StudentInfo::setGrade(int value)
{
    grade = value;
}

QString StudentInfo::getDepartment() const
{
    return department;
}

void StudentInfo::setDepartment(const QString &value)
{
    department = value;
}

QString StudentInfo::getMajor() const
{
    return major;
}

void StudentInfo::setMajor(const QString &value)
{
    major = value;
}

QString  StudentInfo::getClasses() const
{
    return QString::number(classes);
}

void StudentInfo::setClasses(int value)
{
    classes = value;
}

int StudentInfo::getLab() const
{
    return lab;
}

void StudentInfo::setLab(const int &value)
{
    lab = value;
}

QString StudentInfo::toString()
{
    QString str="studentid:"+this->studentId
            +" name:"+this->name
            +" sex:"+this->sex
            +" grade:"+QString::number(this->grade)
            +" department:"+this->department
            +" major:"+this->major
            +" classes:"+QString::number(this->classes)
            +" lab:"+QString::number(this->lab)
            +" email:"+this->email
            +" telephone:"+this->telephone;
    return str;
}

QString StudentInfo::getEmail() const
{
    return email;
}

void StudentInfo::setEmail(const QString &value)
{
    email = value;
}

QString StudentInfo::getTelephone() const
{
    return telephone;
}

void StudentInfo::setTelephone(const QString &value)
{
    telephone = value;
}

QString StudentInfo::getPassword() const
{
    return password;
}

void StudentInfo::setPassword(const QString &value)
{
    password = value;
}

QByteArray StudentInfo::getFaceImage() const
{
    return faceImage;
}

//bytearray形式重载
void StudentInfo::setFaceImage(const QByteArray &value)
{
    faceImage=value;
}

//pixmap形式重载
void StudentInfo::setFaceImage(const QPixmap &value)
{
    QPixmap pixmap=value.scaled(384,288,Qt::KeepAspectRatio,Qt::TransformationMode::SmoothTransformation);
    //转换格式
    QByteArray bArray;
    QBuffer buffer(&bArray);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer,"PNG",0);
    setFaceImage(bArray);
}
QByteArray StudentInfo::getFaceFeature() const
{
    return faceFeature;
}

void StudentInfo::setFaceFeature(const QByteArray &value)
{
    faceFeature = value;
}

bool StudentInfo::isEmpty()
{
    if(this->studentId.isEmpty())
    {
        return true;
    }
    else
    {
        return false;
    }
}


