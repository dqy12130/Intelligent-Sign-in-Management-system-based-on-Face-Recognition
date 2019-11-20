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
*  @file     LogInController.h                                               *
*  @brief    登录控制                                                         *
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
#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include "LogInWidget.h"
#include "LogInService.h"
class LogInController : public LogInWidget
{
public:
    LogInController(QWidget* parent=nullptr);
    ~LogInController();
protected:
    //跳转到主界面
    void showMainWidget();
    //跳转到管理员界面
    void showAdminWidget();
    //判断是否登录成功
    bool isLogInSuccess();
private:
    //登录服务
    LogInService* logInService;
};

#endif // LOGINCONTROLLER_H
