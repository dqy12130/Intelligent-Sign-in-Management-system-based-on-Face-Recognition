/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019  Qiyao Dai     2650822367@qq.com                       *
*                     Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                                                                            *                                                                          *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     ActiveMainWindow.h                                              *
*  @brief   计算文件、字符、数据流MD5码                                         *
*                                                                            *
*  @author   Qiyao.Dai,Zixuan.Zhao                                           *
*  @email    2650822367@qq.com                                               *
*  @version  1.0.0.1                                                         *
*  @date     2019.11.10                                                      *
*  @license  GNU General Public License (GPL)                                *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2019/09/10 | 1.0.0.1   | Qiyao Dai,Zixuan.Zhao    | Create file           *
*----------------------------------------------------------------------------*
*  2019/11/1 | 1.0.0.1   | Qiyao Dai                 | Add function ' QByteArraytoMd5' *
*----------------------------------------------------------------------------*
*  2019/11/19 | 1.0.0.1   | Qiyao Dai                 | Add function ' QFiletoMd5' *
*----------------------------------------------------------------------------*  *
*****************************************************************************/
#ifndef STRINGUTILS_H
#define STRINGUTILS_H
#include <QString>
#include<QByteArray>
#include<QFile>
#include<QFileInfo>
#include<QDebug>
class StringUtils
{
public:
    StringUtils();
public:
    //将字符串转换为md5码
    static QString toMd5(QString str);
    static QString QByteArraytoMd5(QByteArray str);
    static QString QFiletoMd5(QString fileName);
};

#endif // STRINGUTILS_H
