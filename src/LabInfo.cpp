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
*  @file     LabInfo.cpp                                                     *
*  @brief    实验室信息                                                       *
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
#include "LabInfo.h"

LabInfo::LabInfo()
{

}

int LabInfo::getId() const
{
    return id;
}

void LabInfo::setId(int value)
{
    id = value;
}

QString LabInfo::getName() const
{
    return name;
}

void LabInfo::setName(const QString &value)
{
    name = value;
}

QString LabInfo::getAddress() const
{
    return address;
}

void LabInfo::setAddress(const QString &value)
{
    address = value;
}

QString LabInfo::getDepartment() const
{
    return department;
}

void LabInfo::setDepartment(const QString &value)
{
    department = value;
}

QString LabInfo::getState() const
{
    return state;
}

void LabInfo::setState(const QString &value)
{
    state = value;
}

int LabInfo::getMax() const
{
    return max;
}

void LabInfo::setMax(int value)
{
    max = value;
}

int LabInfo::getCurrent() const
{
    return current;
}

void LabInfo::setCurrent(int value)
{
    current = value;
}
