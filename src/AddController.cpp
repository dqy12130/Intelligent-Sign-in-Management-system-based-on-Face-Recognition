/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     AddController.cpp                                               *
*  @brief    Add对话框的Controller层实现                                       *
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

#include "AddController.h"
#include "MySqlUtils.h"
#include "TeacherInfo.h"
#include "ui_AddDialog.h"
#include "CameraDialog.h"
#include <QFileDialog>
#include <QDebug>
#include <QBuffer>

AddController::AddController(int currentLabId, QWidget *parent):AddDialog (parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    //保存当前选中的实验室
    this->currentLabId=currentLabId;
    //保存父窗口
    this->parent=(AdminController*)parent;
    //初始化Service层
    addService=new AddService();
}

AddController::~AddController()
{
    delete addService;
}

/**
 * @brief 弹出fileDialog
 */
void AddController::showFileDialog()
{
    //获取图片文件路径
    QString filePath=QFileDialog::getOpenFileName(this,"选择图片",".",tr("图片文件(*.png *.jpg *.jpeg)"));
    //加载图片
    pixmap.load(filePath);
    pixmap=pixmap.scaled(ui->photoView->size(),Qt::KeepAspectRatio,Qt::TransformationMode::FastTransformation);
    ui->photoView->setPixmap(pixmap);
}

/**
 * @brief 弹出CameraDialog
 */
void AddController::showCameraDialog()
{
    QImage image=CameraDialog::openCameraDialog();
    if(image.isNull()==false)
    {
        pixmap=QPixmap::fromImage(image);
        pixmap=pixmap.scaled(ui->photoView->size(),Qt::KeepAspectRatio,Qt::TransformationMode::FastTransformation);
        ui->photoView->setPixmap(pixmap);
    }
}

/**
 * @brief 添加
 */
void AddController::add()
{
    StudentInfo stuInfo;

    //从ui获取数据
    stuInfo.setStudentId(ui->studentIdLineEdit->text());
    stuInfo.setName(ui->nameLineEdit->text());
    stuInfo.setSex(ui->sexComboBox->currentText());
    stuInfo.setGrade(ui->gradeDateEdit->text().toInt());
    stuInfo.setDepartment(ui->departmentLineEdit->text());
    stuInfo.setMajor(ui->majorLineEdit->text());
    stuInfo.setClasses(ui->classesSpinBox->value());
    stuInfo.setLab(currentLabId);
    //如果图片未设置，就不写入
    if(ui->photoView->pixmap())
    {
        stuInfo.setFaceImage(*(ui->photoView->pixmap()));
    }
    stuInfo.setEmail(ui->emailLineEdit->text());
    stuInfo.setTelephone(ui->telephoneLineEdit->text());
    stuInfo.setPassword(ui->passwordLineEdit->text());
    addService->add(stuInfo);
    this->close();
    //刷新
    this->parent->selectStuInfo();
    this->parent->selectTodaySignInfo();
    this->parent->selectHistorySignInfo();

}

