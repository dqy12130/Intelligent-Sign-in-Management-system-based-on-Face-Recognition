/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     LogInWidget.cpp                                                   *
*  @brief    LogIn面板的Widget层实现                                           *
*                                                                            *
*  @author   Qiyao Dai                                                       *
*  @email   2650822367@qq.com                                                *
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
*  2019/11/13 | 1.0.0.1   | Zixuan.Zhao    | Add function 'getLabInfo'       *
*----------------------------------------------------------------------------*
*  2019/11/19 | 1.0.0.1   |Qiyao Dai       | Add function 'onFaceLogInClick' *
*****************************************************************************/
#include "LogInWidget.h"
#include "ui_LogInWidget.h"
#include <QMessageBox>
#include <QDebug>
#include<FaceLogin.h>
LogInWidget::LogInWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogInWidget)
{
    ui->setupUi(this);

    //初始化
    init();
}

LogInWidget::~LogInWidget()
{
    delete ui;
}

//初始化
void LogInWidget::init()
{
    //UI相关
    setFixedSize(this->width(), this->height()); //禁止改变大小
    m_loginFailedCount=0;//初始化账户登陆失败次数
    //槽相关
    //绑定登录按钮槽
    connect(ui->logInButton,SIGNAL(clicked(bool)),this,SLOT(onLogInClick(bool)));
    connect(ui->FaceLoginButton,SIGNAL(clicked(bool)),this,SLOT(onFaceLogInClick(bool)));
    //绑定返回按钮槽
    connect(ui->backButton,SIGNAL(clicked(bool)),this,SLOT(onBackClick(bool)));
    connect(this->ui->RepaintButton,&QPushButton::clicked,this,&LogInWidget::onRepaintClick);
}

//返回按钮单击事件
void LogInWidget::onBackClick(bool)
{
    //展示MainWidget界面
    showMainWidget();
}

void LogInWidget::onRepaintClick(bool)//刷新验证码
{
    this->ui->CodeLable->slt_reflushVerification();//刷新验证码
}
//登录按钮单击事件
void LogInWidget::onLogInClick(bool)
{
    if(ui->userNameLineEdit->text().isEmpty()||ui->passwordLineEdit->text().isEmpty())
    {
        //为空
        QMessageBox::warning(this,"提示","账号或密码不能为空！");
        return;
    }
    else if(ui->CodeEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"提示","验证码为空");
        return;
    }
    else if(ui->CodeLable->getVerificationCode()!=ui->CodeEdit->text().toUpper())
    {
        qDebug()<<ui->CodeLable->getVerificationCode()<<";"<<ui->CodeEdit->text().toUpper();
        QMessageBox::warning(this,QString("提示"),QString("验证码错误"));
        return;
    }
    else if(isLogInSuccess())
    {
        //登录成功跳转到管理员界面
        showAdminWidget();
    }
    else
    {
        //登录失败
        m_loginFailedCount++;
        QMessageBox::warning(this,"提示","账号或密码错误！");
    }
    if(m_loginFailedCount>=3)
    {
        QMessageBox::warning(this,QString("警告"),QString("账户被锁定"));
        this->ui->logInButton->setEnabled(false);
    }
}

void LogInWidget::onFaceLogInClick(bool)
{

    QProcess process;
    process.start("FaceLogin.exe");//人脸识别登录
    if(process.state()==QProcess::NotRunning)
        return;
    process.waitForFinished(30000); //等待命令执行结束
    QByteArray result = process.readAllStandardOutput();
    if(result.isEmpty()==true)
        return;
    qDebug()<<"result"<<result;
    QString string=result;
    QStringList  processResult=string.split(",");
    //qDebug()<<processResult.at(0)<<",,,"<<processResult.at(1)<<",,,"<<processResult.at(2);
    if("true"==processResult.at(0))
    {

        ui->userNameLineEdit->setText(processResult.at(1));//设置数据
        showAdminWidget();
    }

}



