/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     LogInfo.h                                                       *
*  @brief    设备信息                                                        *
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
*  2019/11/13 | 1.0.0.1   | Zixuan.Zhao    | Create file                     *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#ifndef LOGINFO_H
#define LOGINFO_H

#include <QDateTime>
#include <QString>


class LogInfo
{
public:
    LogInfo();
    QString getDeviceName() const;
    void setDeviceName(const QString &value);

    QDateTime getDate() const;
    void setDate(const QDateTime &value);

    QString getContent() const;
    void setContent(const QString &value);

private:
    QString deviceName;     ///< 设备名
    QDateTime date;         ///< 时间
    QString content;        ///< 内容

};

#endif // LOGINFO_H
