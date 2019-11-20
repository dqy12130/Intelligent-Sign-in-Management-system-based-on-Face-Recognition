/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     LogInfo.cpp                                                     *
*  @brief    设备信息                                                         *
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

#include "LogInfo.h"

LogInfo::LogInfo()
{

}

QString LogInfo::getDeviceName() const
{
    return deviceName;
}

void LogInfo::setDeviceName(const QString &value)
{
    deviceName = value;
}

QDateTime LogInfo::getDate() const
{
    return date;
}

void LogInfo::setDate(const QDateTime &value)
{
    date = value;
}

QString LogInfo::getContent() const
{
    return content;
}

void LogInfo::setContent(const QString &value)
{
    content = value;
}
