/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     SignInWidget.h                                                  *
*  @brief    签到面板的Wideget层实现                                            *
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


#ifndef SIGNINWIDGET_H
#define SIGNINWIDGET_H

#include <QWidget>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QTimer>

namespace Ui {
class SignInWidget;
}

/**
 * @brief SignInWidgetl类
 * 继承自QWidget,属于SignIn面板的Widget层,用来初始化GUi界面，开启摄像头，定时捕捉图像，显示SignIn状态信息
 * 捕获到图像后，将图像传给doFaceWork进行后续处理
 */
class SignInWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SignInWidget(QWidget *parent = nullptr);
    ~SignInWidget();
protected:
    Ui::SignInWidget *ui;
    bool isKeepOnCapture;       ///< 开关，用于标识是否继续捕获图像
    /**
     * @brief 跳转到Main面板
     */
    virtual void showMainWidget()=0;
    /**
     * @brief 对捕获的图片做后续的处理
     * @param[in] image 定时捕获的图片
     */
    virtual void doWork(QImage image)=0;

private:
    QCamera *camera;                            ///< 默认摄像头
    QCameraViewfinder *cameraViewfinder;        ///< 摄像头取景器
    QCameraImageCapture *cameraImageCapture;    ///< 摄像头捕获器
    QTimer* timer;                              ///< 定时器，定时进行图像捕获
    /**
     * @brief SignInWidget的初始化操作
     */
    void init();

private slots:
    /**
     * @brief backButton单击事件
     */
    void onBackClick(bool);
    /**
     * @brief CameraCapturedSlot
     * 每进行一次图像捕捉，触发一次该slot
     * @param[in] id 从开始捕获到现在的第几张图片
     * @param[in] image 本次捕获到的图片
     */
    void onCameraCaptured(int id,QImage image);
    /**
     * @brief TimerOutSlot
     * 定时器每隔固定时间触发一次该slot
     */
    void onTimerOuted();
};

#endif // SIGNINWIDGET_H
