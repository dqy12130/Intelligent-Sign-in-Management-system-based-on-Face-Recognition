/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao.Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     MainDao.h                                                       *
*  @brief    Main面板的DAO层实现                                               *
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

#ifndef MAINDAO_H
#define MAINDAO_H

#include "MySqlUtils.h"

/**
 * @brief MainDao类
 * Main面板的DAO层，提供与数据库的交互接口，包括查询当前主机所属实验室的id
 */

class MainDao
{
public:
    MainDao();
    ~MainDao();
public:
    /**
     * @brief 获取与当前主机关联的实验室id
     * @return 与当前主机关联的实验室id
     * @retval -1 未绑定的主机
     */
    int isApproveHost();
private:
    QSqlDatabase db;        ///< 数据库引擎

};

#endif // MAINDAO_H
