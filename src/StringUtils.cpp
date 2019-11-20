/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019  Qiyao.Dai     2650822367@qq.com                       *
*                                                                            *
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
*  2019/09/10 | 1.0.0.1   | Qiyao.Dai,Zixuan.Zhao    | Create file           *
*----------------------------------------------------------------------------*
*  2019/11/1 | 1.0.0.1   | Qiyao.Dai                 | Add function ' QByteArraytoMd5' *
*----------------------------------------------------------------------------*
*  2019/11/19 | 1.0.0.1   | Qiyao.Dai                 | Add function ' QFiletoMd5' *
*----------------------------------------------------------------------------*  *
*****************************************************************************/
#include "StringUtils.h"
#include "QByteArray"
#include "QCryptographicHash"
StringUtils::StringUtils()
{

}
//计算字符串的MD5码
QString StringUtils::toMd5(QString str)
{
    QString md5;
    QByteArray ba,bb;
    QCryptographicHash md(QCryptographicHash::Md5);
    ba.append(str);
    md.addData(ba);
    bb=md.result();
    md5.append(bb.toHex());
    return md5;
}

QString StringUtils::QByteArraytoMd5(QByteArray buffer)
{
    QString md5;
    QByteArray bb;
    QCryptographicHash md(QCryptographicHash::Md5);
    md.addData(buffer);
    bb=md.result();
    md5.append(bb.toHex());
    return md5;
}
QString StringUtils::QFiletoMd5(QString fileName)
{
   // qDebug()<<fileName;
    QFile file(fileName);
    QFileInfo fileInfo=file;
    QString fileNameCompere=fileInfo.fileName();
   // qDebug()<<fileNameCompere;
    QByteArray byte;
    file.open(QIODevice::ReadOnly);
    byte=file.readAll();
    file.close();
    QString fileMd5=StringUtils::QByteArraytoMd5(byte);
    //qDebug()<<fileMd5;
    return fileMd5;
}
















