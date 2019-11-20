
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
*  @brief    Main面板的Controller层实现,集成特征值批量处理，签到机认证             *
*                                                                            *
*  @author   Qiyao.Dai,Zixuan Zhao                                           *
*  @email    2650822367@qq.com,zxZhao1998@gmail.com                          *
*  @version  1.0.0.1                                                         *
*  @date     2019.11.19                                                      *
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

#include "MainController.h"
#include "LogInController.h"
#include "SignInController.h"
#include <QDebug>
#include<QApplication>
MainController::MainController(QWidget *parent):MainWidget(parent)
{
    qDebug()<<"MainController";

}

MainController::~MainController()
{
    qDebug()<<"~MainController";
}
//实现跳转到登录界面的接口
void MainController::showLogInWidget()
{
    this->close();
    LogInController *logInController=new LogInController();
    logInController->show();
}

//实现跳转到签到界面的接口
void MainController::showSignInWidget()
{
    QMap<bool,QString> activeResult= ActiveMainWindow::HostIsActiveLab();//签到机认证
    if(activeResult.isEmpty()==true)
    {
        QMessageBox::warning(nullptr,QString("错误"),QString("本机未被认证"),QMessageBox::Ok);
        return;
    }
    bool flag=activeResult.begin().key();
    QString currentActiveHostLab=activeResult.begin().value();
    qDebug()<<currentActiveHostLab;

    this->close();
    SignInController* signInController=new SignInController(currentActiveHostLab.toInt(),nullptr);
    signInController->show();
}

void MainController::showTrackWidget()
{
    //弃用
    this->close();
    MainWindow* signInController=new MainWindow;
    signInController->InitSystem();
}
