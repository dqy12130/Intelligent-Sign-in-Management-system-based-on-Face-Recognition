/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     CameraDialog.cpp                                                *
*  @brief    类似于QMesageBox实现方法的一个即用即调的带有捕获图片功能的Dialog       *
*                                                                            *
*  @author   Qiyao Dai,Zixuan Zhao                                           *
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
*  2019/09/10 | 1.0.0.1   | Qiyao Dai,Zixuan.Zhao    | Create file           *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#include "CameraDialog.h"
#include "ui_CameraDialog.h"

QImage CameraDialog::image=QImage();

CameraDialog::CameraDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CameraDialog)
{
    ui->setupUi(this);
    init();
}

CameraDialog::~CameraDialog()
{
    delete camera;
    delete cameraImageCapture;
    delete cameraViewfinder;
    delete ui;
}

void CameraDialog::init()
{
    //初始化摄像头
    camera=new QCamera();
    //初始化finder
    cameraViewfinder=new QCameraViewfinder(ui->cameraLabel);
    //取景器大小
    cameraViewfinder->setGeometry(0,0,ui->cameraLabel->size().width(),ui->cameraLabel->size().height());
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
    //确定按钮的单击事件
    connect(ui->okButton,SIGNAL(clicked(bool)),this,SLOT(onOkClick(bool)));
    //取消按钮的单击事件
    connect(ui->cancelButton,SIGNAL(clicked(bool)),this,SLOT(onCancelClick(bool)));
    //捕获图片后的触发事件
    connect(cameraImageCapture,SIGNAL(imageCaptured(int,QImage)),this,SLOT(onCameraCaptured(int,QImage)));
    camera->start();
}

/**
 * @brief openCameraDialog 打开对话框
 * @return 捕获到的图片
 */
QImage CameraDialog::openCameraDialog()
{
    CameraDialog camera;
    if(camera.exec()==QDialog::Accepted)
    {
        return CameraDialog::image;
    }
    else
    {
        return QImage();
    }
}

/**
 * @brief okButton的单击响应事件
 */
void CameraDialog::onOkClick(bool)
{
    cameraImageCapture->capture();
}

/**
 * @brief cancelButton的单击响应事件
 */
void CameraDialog::onCancelClick(bool)
{
    emit reject();
}

/**
 * @brief 捕获后保存图片
 * @param id 序列号
 * @param image 图片
 */
void CameraDialog::onCameraCaptured(int id, QImage image)
{
    CameraDialog::image=image;
    emit accept();
}


