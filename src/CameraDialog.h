/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     CameraDialog.h                                                  *
*  @brief    类似于QMesageBox实现方法的一个即用即调的带有捕获图片功能的Dialog       *
*                                                                            *
*  @author   Qiyao Dai,Zixuan Zhao                                           *
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
*  2019/09/10 | 1.0.0.1   | Zixuan.Zhao    | Create file                     *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#ifndef CAMERADIALOG_H
#define CAMERADIALOG_H

#include <QDialog>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>

namespace Ui {
class CameraDialog;
}

/**
 * @brief CameraDialog类
 * 继承自QDialog，弹出一个可返回捕获图片的对话框
 */
class CameraDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CameraDialog(QWidget *parent = nullptr);
    ~CameraDialog();

public:
    /**
     * @brief openCameraDialog 打开对话框
     * @return 捕获到的图片
     */
    static QImage openCameraDialog();

private:
    Ui::CameraDialog *ui;
    QCamera *camera;                            ///< 系统摄像头
    QCameraViewfinder *cameraViewfinder;        ///< 取景部件
    QCameraImageCapture *cameraImageCapture;    ///< 截图部件
    static QImage image;                        ///< 捕获到的图片

    /**
     * @brief 初始化
     */
    void init();

private slots:
    /**
     * @brief okButton的单击响应事件
     */
    void onOkClick(bool);
    /**
     * @brief cancelButton的单击响应事件
     */
    void onCancelClick(bool);
    /**
     * @brief 捕获后保存图片
     * @param id 序列号
     * @param image 图片
     */
    void onCameraCaptured(int id,QImage image);
};

#endif // CAMERADIALOG_H
