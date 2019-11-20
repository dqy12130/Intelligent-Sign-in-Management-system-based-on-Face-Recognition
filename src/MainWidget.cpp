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
*  @file     MainWidget.cpp                                                    *
*  @brief    Main面板的Widget层实现                                            *
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
*  2019/11/1 | 1.0.0.1   |Qiyao Dai       | Add function 'onTrackButtonClick'*
*----------------------------------------------------------------------------*
*  2019/11/10| 1.0.0.1   |Qiyao Dai       | Add function 'onHostActiveButtonClick'*
* *----------------------------------------------------------------------------*
*  2019/11/19| 1.0.0.1   |Qiyao Dai       | Add function 'onFaceLoginBtnClicked'*
*****************************************************************************/
#include "MainWidget.h"
#include "ui_MainWidget.h"
#include <QDebug>
#include<LoginService.h>
#include<MySqlUtils.h>
#include<QSqlDatabase>
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{

    qDebug()<<"MainWidget";
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());  //禁止改变大小
    //初始化
    init();
}

MainWidget::~MainWidget()
{
    qDebug()<<"~MainWidget";
    delete ui;
}

//初始化
void MainWidget::init()
{
    //绑定登录按钮的槽
    connect(ui->logInButton,SIGNAL(clicked(bool)),this,SLOT(onLogInButtonClick(bool)));
    //绑定签到按钮的槽
    connect(ui->signInButton,SIGNAL(clicked(bool)),this,SLOT(onSignInButtonClick(bool)));
    //特征值训练
    connect(this->ui->TrackButton,&QPushButton::clicked,this,&MainWidget::onTrackButtonClick);
    //加载签到机认证程序
    connect(this->ui->hostActiveButton,&QPushButton::clicked,this,&MainWidget::onHostActiveButtonClick);

    connect(this->ui->FaceLoginBtn,&QPushButton::clicked,this,&MainWidget::onFaceLoginBtnClicked);

}

//登录按钮点击事件
void MainWidget::onLogInButtonClick(bool)
{
    //跳转到登录界面
    this->showLogInWidget();
}

//签到按钮点击事件
void MainWidget::onSignInButtonClick(bool)
{
    //跳转到签到界面
    this->showSignInWidget();
}

void MainWidget::onTrackButtonClick(bool)
{
    //显示特征值训练界面
    //this->showTrackWidget();//弃用
    QProcess process;
    process.start("TrackFeatureSystem.exe");
    process.waitForFinished(30000); //等待命令执行结束
    QByteArray result = process.readAllStandardOutput();
    if(-1==result.indexOf("TrackFeatureSystem.exe"))
    {
        process.startDetached("TrackFeatureSystem.exe");
    }
}

void MainWidget::onHostActiveButtonClick(bool)
{
    QProcess process;
    process.start("HostActiveSystem.exe");
    process.waitForFinished(30000); //等待命令执行结束
    QByteArray result = process.readAllStandardOutput();
    if(-1==result.indexOf("HostActiveSystem.exe"))
    {
        process.startDetached("HostActiveSystem.exe");
    }
}

void MainWidget::onFaceLoginBtnClicked(bool)
{
    QProcess process;
    process.start("FaceLogin.exe");
    if(process.state()==QProcess::NotRunning)
        return;
    process.waitForFinished(30000); //等待命令执行结束
    QByteArray result = process.readAllStandardOutput();
    if(result.isEmpty()==true)
        return;
//    qDebug()<<"result"<<result;
    QString string=result;
    QStringList  processResult=string.split(",");
//    qDebug()<<processResult.at(0)<<",,,"<<processResult.at(1)<<",,,"<<processResult.at(2);
    if("true"==processResult.at(0))
    {
        this->close();
        //获取登录的教师信息
        LogInService logInService;
        TeacherInfo teacherInfo=logInService.getTeacherInfo(processResult.at(1));
        //进入管理员界面
        AdminController* adminController=new AdminController(teacherInfo);
        adminController->show();
        //进入管理员界面
    }
}










