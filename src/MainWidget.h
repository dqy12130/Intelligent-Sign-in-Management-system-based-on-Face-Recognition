/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019  Qiyao Dai     2650822367@qq.com                       *
*                      Zixuan.Zhao   zxZhao1998@gmail.com                    *
*                                                                            *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     MainWidget.h                                                    *
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
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "LogInWidget.h"

#include<lib/TrackFeatureSystem/include/MainWindow.h>
#include<QProcess>
#include<TeacherInfo.h>
#include<AdminController.h>
#include<QStringList>
namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
private:
    Ui::MainWidget *ui;

    //初始化
    void init();
protected:
    //跳转到登录界面
    virtual void showLogInWidget()=0;
    //跳转到签到界面
    virtual void showSignInWidget()=0;

    //显示训练特征值界面
    virtual void showTrackWidget()=0;

private slots:
    //登录按钮的响应事件
    void onLogInButtonClick(bool);
    //签到按钮的响应事件
    void onSignInButtonClick(bool);

    void onTrackButtonClick(bool);
    void onHostActiveButtonClick(bool);

    void onFaceLoginBtnClicked(bool);
};

#endif // MAINWIDGET_H
