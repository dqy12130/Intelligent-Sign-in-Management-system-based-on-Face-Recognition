/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao.Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     SignInWidget.vpp                                                 *
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

#include "SignInWidget.h"
#include "ui_SignInWidget.h"
#include <QDebug>
SignInWidget::SignInWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignInWidget)
{
    ui->setupUi(this);
    init();
}

SignInWidget::~SignInWidget()
{
    delete camera;
    delete cameraImageCapture;
    delete cameraViewfinder;
    delete timer;
    delete ui;
}

/**
 * @brief SignInWidget的初始化操作
 */
void SignInWidget::init()
{
    //Widget初始化
    setFixedSize(this->width(), this->height());

    //部件初始化
    isKeepOnCapture=true;
    //初始化摄像头
    camera=new QCamera();
    //初始化finder
    cameraViewfinder=new QCameraViewfinder(ui->cameraLabel);
    //取景器大小
    cameraViewfinder->setGeometry(0,0,ui->cameraLabel->size().width(),ui->cameraLabel->height());
    cameraViewfinder->show();
    camera->setViewfinder(cameraViewfinder);
    //初始化capture
    cameraImageCapture=new QCameraImageCapture(camera);
    camera->setCaptureMode(QCamera::CaptureStillImage);
    //如果支持，则将图片存入缓冲区
    if(cameraImageCapture->isCaptureDestinationSupported(QCameraImageCapture::CaptureToBuffer))
    {
        cameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);
        cameraImageCapture->setBufferFormat(QVideoFrame::PixelFormat::Format_Jpeg);
        //设置编码格式
        QImageEncoderSettings imageSetting;
        imageSetting.setResolution(640,360);
        cameraImageCapture->setEncodingSettings(imageSetting);
    }

    //Slots初始化
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimerOuted()));
    connect(cameraImageCapture,SIGNAL(imageCaptured(int,QImage)),this,SLOT(onCameraCaptured(int,QImage)));
    connect(ui->backButton,SIGNAL(clicked(bool)),this,SLOT(onBackClick(bool)));
    //开启
    camera->start();
    timer->start(1000);
}

/**
 * @brief backButton单击事件
 */
void SignInWidget::onBackClick(bool)
{
    showMainWidget();
}
/**
 * @brief CameraCapturedSlot
 * 每进行一次图像捕捉，触发一次该slot
 * @param[in] id 从开始捕获到现在的第几张图片
 * @param[in] image 本次捕获到的图片
 */
void SignInWidget::onCameraCaptured(int id, QImage image)
{
    doWork(image);
}

/**
 * @brief TimerOutSlot
 * 定时器每隔固定时间触发一次该slot
 */
void SignInWidget::onTimerOuted()
{
    //判断是否继续捕获
    if(isKeepOnCapture==true)
    {
        cameraImageCapture->capture();
    }
}
