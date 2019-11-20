/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao.Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     HistorySignInfo.cpp                                             *
*  @brief    历史签到信息类，保存于历史签到信息有关的各项数据                        *
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

#include "HistorySignInfo.h"

HistorySignInfo::HistorySignInfo()
{

}

int HistorySignInfo::getSignInTimes() const
{
    return signInTimes;
}

void HistorySignInfo::setSignInTimes(int value)
{
    signInTimes = value;
}

int HistorySignInfo::getUnSignInTimes() const
{
    return unSignInTimes;
}

void HistorySignInfo::setUnSignInTimes(int value)
{
    unSignInTimes = value;
}

float HistorySignInfo::getRate() const
{
    return rate;
}

void HistorySignInfo::setRate(float value)
{
    rate = value;
}

StudentInfo HistorySignInfo::getStuInfo() const
{
    return stuInfo;
}

void HistorySignInfo::setStuInfo(const StudentInfo &value)
{
    stuInfo = value;
}
