/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao.Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     HistorySignInfo.h                                               *
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

#ifndef HISTORYSIGNINFO_H
#define HISTORYSIGNINFO_H

#include "StudentInfo.h"

/**
 * @brief HistorySignInfo类
 * 记录历史签到信息，显示在historyTableWidget中
 */
class HistorySignInfo
{
public:
    HistorySignInfo();
    int getSignInTimes() const;
    void setSignInTimes(int value);

    int getUnSignInTimes() const;
    void setUnSignInTimes(int value);

    float getRate() const;
    void setRate(float value);

    StudentInfo getStuInfo() const;
    void setStuInfo(const StudentInfo &value);

private:

    int signInTimes;        ///< 签到次数
    int unSignInTimes;      ///< 未签次数
    float rate;             ///< 缺勤率
    StudentInfo stuInfo;    ///< 学生信息
};

#endif // HISTORYSIGNINFO_H
