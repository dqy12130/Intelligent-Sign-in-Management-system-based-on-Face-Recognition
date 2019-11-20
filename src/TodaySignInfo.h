/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao.Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     todaySignInfo.h                                                 *
*  @brief    今日签到信息类，保存今日签到信息有关的各项数据                          *
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

#ifndef TODAYSIGNINFO_H
#define TODAYSIGNINFO_H

#include <QDateTime>
#include "StudentInfo.h"

/**
 * @brief TodaySignInfo类
 * 今日签到信息
 */
class TodaySignInfo
{
public:
    TodaySignInfo();
    QDateTime getSignInDateTime() const;
    void setSignInDateTime(const QDateTime &value);

    StudentInfo getStuInfo() const;
    void setStuInfo(const StudentInfo &value);

private:

    QDateTime signInDateTime;    ///< 签到时间
    StudentInfo stuInfo;         ///< 学生信息
};

#endif // TODAYSIGNINFO_H
