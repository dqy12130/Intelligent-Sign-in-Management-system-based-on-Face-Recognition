/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Qiyao Dai   2650822367@qq.com                          *
*                     Zixuan.Zhao   zxZhao1998@gmail.com                     *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     VerificationCodeLabel.h                                         *
* 感谢来源CSDN的作者提供了相应的源码                                             *
*  @brief    验证码的生成                                                      *
*                                                                            *
*  @author   Qiyao Dai                                                       *
*  @email    2650822367@qq.com                                               *
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
*  2019/11/14 | 1.0.0.1   | Qiyao Dai    | Create file                       *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#ifndef VERIFICATIONCODELABEL_H
#define VERIFICATIONCODELABEL_H

#include <QObject>
#include<QLabel>
#include<QTime>
#include<QPainter>
class VerificationCodeLabel : public QLabel
{
    Q_OBJECT

public:
    VerificationCodeLabel(QWidget *parent=0);
    ~VerificationCodeLabel();
    //返回一个字符串（字母一律都按照大写返回）
    QString getVerificationCode() const;
public slots:
    //公共槽函数
    //刷新验证码，在用户不确定的时候进行相应刷新
    void slt_reflushVerification();
protected:
    //重写绘制事件,以此来生成验证码
    void paintEvent(QPaintEvent *event);
private:
    const int letter_number =4;//产生字符的数量
    int noice_point_number ;//噪点的数量
    enum {  //枚举分类，也可自己定义
        NUMBER_FLAG,
        UPLETTER_FLAG,
        LOWLETTER_FLAG
    };
    //这是一个用来生成验证码的函数
    void produceVerificationCode() const;
    //产生一个随机的字符
    QChar produceRandomLetter() const;
    //产生随机的颜色
    void produceRandomColor() const;

    QChar *verificationCode;
    QColor *colorArray;
};

#endif // VERIFICATIONCODELABEL_H
