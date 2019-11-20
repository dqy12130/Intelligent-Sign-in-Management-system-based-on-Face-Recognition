
/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019  Qiyao.Dai     2650822367@qq.com                       *
*                      Zixuan.Zhao   zxZhao1998@gmail.com                    *
*                                                                            *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     MainController.h                                                *
*  @brief    Main面板的Controller层实现                                        *
*                                                                            *
*  @author   Qiyao.Dai,Zixuan Zhao                                           *
*  @email    2650822367@qq.com,zxZhao1998@gmail.com                          *
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
*  2019/09/10 | 1.0.0.1   | Qiyao Dai,Zixuan.Zhao    | Create file           *
*----------------------------------------------------------------------------*
*  2019/11/19 | 1.0.0.1   |Qiyao Dai       | Add function 'showTrackWidget'  *                                                                     *
*****************************************************************************/
#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include "MainWidget.h"
#include<lib/TrackFeatureSystem/include/MainWindow.h>
#include<ActiveMainWindow.h>
class MainController : public MainWidget
{

public:
    MainController(QWidget* parent=nullptr);
    ~MainController();
protected:
    //纯虚函数实现
    void showLogInWidget();//管理员登录
    void showSignInWidget();//签到

    void showTrackWidget();//特征值训练
};

#endif // MAINCONTROLLER_H
