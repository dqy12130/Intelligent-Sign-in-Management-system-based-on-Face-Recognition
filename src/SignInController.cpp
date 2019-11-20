/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao.Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     SignInContorller.cpp                                            *
*  @brief    SignIn面板的Controller层实现                                      *
*                                                                            *
*  @author   Zixuan Zhao,Qiyao.Dai                                           *
*  @email    zxZhao1998@gmail.com ,2650822367@qq.com                         *
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
*  2019/09/10 | 1.0.0.1   | Zixuan.Zhao Qiyao Dai   | Create file            *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/



#include "SignInController.h"
#include "MainController.h"
#include "LogInController.h"
#include "ui_SignInWidget.h"

SignInController::SignInController(int labId,QWidget* parent):SignInWidget(parent)
{
    //关闭Widget时析构
    setAttribute(Qt::WA_DeleteOnClose);

    //初始化SignIn面板的Service层
    signInService=new SignInService(labId);
    //初始化新线程
    signInServiceThread=new QThread();
    //将Service层移到新线程中
   signInService->moveToThread(signInServiceThread);

    //初始化slots
    //Thread退出时释放serviceThread
    connect(signInServiceThread,SIGNAL(finished()),signInServiceThread,SLOT(deleteLater()));
    //Thread退出时释放service
    connect(signInServiceThread,SIGNAL(finished()),signInService,SLOT(deleteLater()));
    //sendImage信号触发receiveImage Slot
    connect(this,SIGNAL(sendImage(QImage)),signInService,SLOT(receiveImage(QImage)));
    //sendResult信号触发receiveResult Slot
    connect(signInService,SIGNAL(sendResult(QString)),this,SLOT(receiveResult(QString)));

    //开启SignInServiceThread
    signInServiceThread->start();
}

SignInController::~SignInController()
{
    //退出signInServiceThread
    if(signInServiceThread)
    {
        signInServiceThread->quit();
    }
    signInServiceThread->wait();
}

/**
 * @brief 跳转到Main面板
 */
void SignInController::showMainWidget()
{
    this->close();
    MainController* mainController=new MainController();
    mainController->show();
}

/**
 * @brief 对捕获的每一张图片进行后续处理
 * @param[in] image 捕获的图片
 */
void SignInController::doWork(QImage image)
{
    emit sendImage(image);
}

/**
 * @brief 接收图片后续处理过程的状态信息
 * @param text 状态信息
 */
void SignInController::receiveResult(QString text)
{
    ui->stateLabel->setText(text);
}


