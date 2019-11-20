/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     imageFromat.h                                                   *
*  @brief    opencv库与Qt库常用图片格式的转换                                   *
*                                                                            *
*  @author   Qiyao Dai,Zixuan Zhao                                           *
*  @email   2650822367@qq.com ,zxZhao1998@gmail.com                          *
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
*  2019/010/10 | 1.0.0.1   |Zixuan Zhao      | Create file                   *
*----------------------------------------------------------------------------*
*  2019/11/13 | 1.0.0.1   | Qiyao Dai      | Add function 'getFaceFeature    *
*             |           |                |    Imag   ',setFaceFeature'     *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#ifndef TEACHERINFO_H
#define TEACHERINFO_H

#include <QMap>
#include <QString>
#include <QVector>
#include<LabInfo.h>
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
