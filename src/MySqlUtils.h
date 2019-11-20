/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao.Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     MySqlUtils.h                                                    *
*  @brief    MySql数据库处理中心                                               *
*                                                                            *
*  @author   Zixuan Zhao ,Qiyao Dai                                          *
*  @email    zxZhao1998@gmail.com,2650822367@qq.com                          *
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
*  2019/11/19 | 1.0.0.1   | Qiyao Dai      | update function'getConnection'  *
*----------------------------------------------------------------------------*                                                                        *
*****************************************************************************/

#ifndef MYSQLUTILS_H
#define MYSQLUTILS_H

#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include<SystemConf.h>//系统配置类

/**
 * @brief MySqlUtils类
 * 提供初始化数据库，释放数据库连接的静态函数
 */
class MySqlUtils
{
public:
    /**
     * @brief 获取数据库连接
     * @param connectName 连接命名
     * @return 数据库连接
     */
    static QSqlDatabase getConnection(QString connectName);
    /**
     * @brief 释放数据库连接
     * @param db 释放的数据库
     * @param connectName 目标名
     */
    static void release(QSqlDatabase db, QString connectName);
};

#endif // MYSQLUTILS_H
