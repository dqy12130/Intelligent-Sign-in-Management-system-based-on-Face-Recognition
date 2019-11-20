/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao.Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     StudentInfo.h                                                   *
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

#ifndef STUDENTINFO_H
#define STUDENTINFO_H

#include <QPixmap>
#include <QString>

/**
 * @brief StudentInfo类
 * 学生信息
 */
class StudentInfo
{
public:
    StudentInfo();
private:
    QString studentId;          ///< 学号
    QString name;               ///< 姓名
    QString sex;                ///< 性别
    int grade;                  ///< 年级
    QString department;         ///< 院系
    QString major;              ///< 专业
    int classes;                ///< 班级
    int lab;                    ///< 所在实验室id
    QByteArray faceImage;       ///< 人脸图片
    QByteArray faceFeature;     ///< 特征值
    QString email;              ///< 邮箱
    QString telephone;          ///< 电话号码
    QString password;           ///< 密码
public:
    //打印
    QString toString();

    QString getStudentId() const;
    void setStudentId(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    QString getSex() const;
    void setSex(const QString &value);

    QString getGrade() const;
    void setGrade(int value);

    QString getDepartment() const;
    void setDepartment(const QString &value);

    QString getMajor() const;
    void setMajor(const QString &value);

    QString getClasses() const;
    void setClasses(int value);

    int getLab() const;
    void setLab(const int &value);

    QString getEmail() const;
    void setEmail(const QString &value);

    QString getTelephone() const;
    void setTelephone(const QString &value);

    QString getPassword() const;
    void setPassword(const QString &value);

    QByteArray getFaceImage() const;
    //bytearray形式的重载
    void setFaceImage(const QByteArray &value);
    //pixmap形式的重载
    void setFaceImage(const QPixmap &value);

    QByteArray getFaceFeature() const;
    void setFaceFeature(const QByteArray &value);

    bool isEmpty();

};

#endif // STUDENTINFO_H
