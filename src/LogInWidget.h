/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     LogInWidget.h                                                   *
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
#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include<QProcess>
namespace Ui {
class LogInWidget;
}

class LogInWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LogInWidget(QWidget *parent = nullptr);
    ~LogInWidget();

protected:
    Ui::LogInWidget *ui;

    //显示主界面
    virtual void showMainWidget()=0;
    //显示管理员界面
    virtual void showAdminWidget()=0;
    //判断是否登录成功
    virtual bool isLogInSuccess()=0;
private:
    //初始化
    void init();
private slots:
    //返回按钮单击事件
    void onRepaintClick(bool);//刷新验证码
    void onBackClick(bool);
    //登录按钮单击事件

    void onLogInClick(bool);

    void onFaceLogInClick(bool);


private:
    int m_loginFailedCount;
};

#endif // LOGINWIDGET_H
