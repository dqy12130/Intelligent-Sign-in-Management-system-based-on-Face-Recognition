/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     DevicesInfo.cpp                                                   *
*  @brief    设备信息类，保存与设备信息有关的各项数据                              *
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
*  2019/11/12 | 1.0.0.1   | Qiyao Dai      | Create file            s         *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#include "DevicesInfo.h"

DevicesInfo::DevicesInfo()
{

}

QString DevicesInfo::getName() const
{
    return name;
}

void DevicesInfo::setName(const QString &value)
{
    name = value;
}

QString DevicesInfo::getMax() const
{
    return QString::number(max);
}

void DevicesInfo::setMax(int value)
{
    max = value;
}

QString DevicesInfo::getLoan() const
{
    return QString::number(loan);
}

void DevicesInfo::setLoan(int value)
{
    loan = value;
}

QString DevicesInfo::getDemage() const
{
    return QString::number(demage);
}

void DevicesInfo::setDemage(int value)
{
    demage = value;
}

QString DevicesInfo::getRemain() const
{
    return QString::number(remain);
}

void DevicesInfo::setRemain(int value)
{
    remain = value;
}

QString DevicesInfo::getId() const
{
    return QString::number(Id);
}

void DevicesInfo::setId(int value)
{
    Id = value;
}
