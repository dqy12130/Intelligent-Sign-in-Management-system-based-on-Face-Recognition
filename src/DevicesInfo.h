/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     DevicesInfo.h                                                   *
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

#ifndef DEVICESINFO_H
#define DEVICESINFO_H
#include <QString>

class DevicesInfo
{
public:
    DevicesInfo();
    QString getName() const;
    void setName(const QString &value);

    QString getMax() const;
    void setMax(int value);

    QString getLoan() const;
    void setLoan(int value);

    QString getDemage() const;
    void setDemage(int value);

    QString getRemain() const;
    void setRemain(int value);

    QString getId() const;
    void setId(int value);

private:
    int Id;             ///< 设备id
    QString name;       ///< 设备名
    int max;            ///< 额定数量
    int loan;           ///< 借出数量
    int demage;         ///< 损坏数量
    int remain;         ///< 剩余数量
};

#endif // DEVICESINFO_H
