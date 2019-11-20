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
*  @file     LabInfo.h                                                       *
*  @brief    实验室信息                                                        *
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

#ifndef LABINFO_H
#define LABINFO_H

#include <QString>


/**
 * @brief LabInfo类
 * 实验室信息
 */
class LabInfo
{
public:
    LabInfo();
    int getId() const;
    void setId(int value);

    QString getName() const;
    void setName(const QString &value);

    QString getAddress() const;
    void setAddress(const QString &value);

    QString getDepartment() const;
    void setDepartment(const QString &value);

    QString getState() const;
    void setState(const QString &value);

    int getMax() const;
    void setMax(int value);

    int getCurrent() const;
    void setCurrent(int value);

private:
    int id;                 ///< 实验室id
    QString name;           ///< 实验室名称
    QString address;        ///< 实验室地址
    QString department;     ///< 所属部门
    QString state;          ///< 状态
    int max;                ///< 容纳人数
    int current;            ///< 现有人数
};

#endif // LABINFO_H
