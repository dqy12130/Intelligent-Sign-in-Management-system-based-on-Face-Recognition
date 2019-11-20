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
*                                                                            */
#include "LogInController.h"
#include "MainController.h"
#include "AdminController.h"
#include "ui_LogInWidget.h"
#include <QDebug>
LogInController::LogInController(QWidget* parent):LogInWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    //开启登录服务
    logInService=new LogInService();
}

LogInController::~LogInController()
{
    //关闭登录服务
    delete logInService;
}

//跳转到主界面
void LogInController::showMainWidget()
{
    this->close();
    MainController* mainController=new MainController();
    mainController->show();
}

//跳转到管理员界面
void LogInController::showAdminWidget()
{
    //关闭窗口
    this->close();
    //获取登录的教师信息
    TeacherInfo teacherInfo=logInService->getTeacherInfo(ui->userNameLineEdit->text());
    QVector<LabInfo> labsInfo=logInService->getLabInfo(ui->userNameLineEdit->text());
    //进入管理员界面
    AdminController* adminController=new AdminController(teacherInfo,labsInfo);
    adminController->show();
}

//判断是否登录成功
bool LogInController::isLogInSuccess()
{
    bool isSuccess=false;
    //获取账号密码
    QString userName=ui->userNameLineEdit->text();
    QString password=ui->passwordLineEdit->text();
    isSuccess=logInService->isLogInSuccess(userName,password);
    return isSuccess;
}
