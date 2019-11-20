/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao.Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     SignInDao.h                                                     *
*  @brief    SignIn面板的DAO层实现                                             *
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

#ifndef SIGNINDAO_H
#define SIGNINDAO_H
#include <QVector>
#include "MySqlUtils.h"
#include "StudentInfo.h"
/**
 * @brief SignInDao类
 * 属于SignIn面板的DAO层，用以提供数据库的交互接口，包括获取某实验室人脸库，判断是否已签到
 */
class SignInDao
{
public:
    SignInDao();
    ~SignInDao();
public:
    /**
     * @brief 获取某实验室所有学生的信息
     * @param[in] labId 实验室id
     * @return 该实验室id所对应的实验室中所有学生的信息
     */
    QVector<StudentInfo> getAllStuInfo(int labId);
    /**
     * @brief 判断某学生是否已签到，如果未签到，签到后返回false
     * @param[in] studentId 学号
     * @return 是否已签到
     */
    bool isSignInSuccess(QString studentId);

private:
    QSqlDatabase db;        ///< 数据库引擎
};

#endif // SIGNINDAO_H
