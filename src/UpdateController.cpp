/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao.Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     UpdateController.cpp                                            *
*  @brief    Update对话框的Controller层实现                                    *
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

#include "UpdateController.h"
#include "CameraDialog.h"
#include "MySqlUtils.h"
#include "TeacherInfo.h"
#include "ui_UpdateDialog.h"
#include <QFileDialog>
#include <QDebug>
#include <QBuffer>

UpdateController::UpdateController(QMap<int, QString> labMap, StudentInfo oldStuInfo, QWidget *parent):UpdateDialog (parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    //保存子窗口
    this->parent=(AdminController*)parent;
    //保存待修改的学生学号
    this->oldStudentId=oldStuInfo.getStudentId();
    //保存实验室
    this->labMap=labMap;
    //开启服务
    updateService=new UpdateService();

    //初始化窗口
    ui->studentIdLineEdit->setText(oldStuInfo.getStudentId());
    ui->nameLineEdit->setText(oldStuInfo.getName());
    if(oldStuInfo.getSex()=="女")
    {
        ui->sexComboBox->setCurrentIndex(1);
    }
    ui->gradeDateEdit->setDate(QDate(oldStuInfo.getGrade().toInt(),1,1));
    ui->labComboBox->addItems(labMap.values());
    ui->labComboBox->setCurrentText(labMap.value(oldStuInfo.getLab()));
    ui->departmentLineEdit->setText(oldStuInfo.getDepartment());
    ui->majorLineEdit->setText(oldStuInfo.getMajor());
    ui->classesSpinBox->setValue(oldStuInfo.getClasses().toInt());
    ui->emailLineEdit->setText(oldStuInfo.getEmail());
    ui->telephoneLineEdit->setText(oldStuInfo.getTelephone());
    if(oldStuInfo.getFaceImage().isEmpty()==false)
    {
        pixmap.loadFromData(oldStuInfo.getFaceImage());
        pixmap=pixmap.scaled(ui->photoView->size(),Qt::KeepAspectRatio,Qt::TransformationMode::FastTransformation);
        ui->photoView->setPixmap(pixmap);
    }
}

UpdateController::~UpdateController()
{
    delete updateService;
}
/**
 * @brief 弹出FileDialog
 */
void UpdateController::showFileDialog()
{
    //获取图片文件路径
    QString filePath=QFileDialog::getOpenFileName(this,"选择图片",".",tr("图片文件(*.png *.jpg *.jpeg)"));
    //加载图片
    if(filePath.isEmpty()==false)
    {
        pixmap.load(filePath);
        pixmap.scaled(ui->photoView->size(),Qt::KeepAspectRatio,Qt::TransformationMode::FastTransformation);
        ui->photoView->setPixmap(pixmap);
    }
}
/**
 * @brief 弹出CameraDialog
 */
void UpdateController::showCameraDialog()
{
    QImage image=CameraDialog::openCameraDialog();
    if(image.isNull()==false)
    {
        pixmap=QPixmap::fromImage(image);
        pixmap=pixmap.scaled(ui->photoView->size(),Qt::KeepAspectRatio,Qt::TransformationMode::FastTransformation);
        //qDebug()<<ui->photoView->size().width()<<ui->photoView->size().height();
        ui->photoView->setPixmap(pixmap);
    }
}

/**
 * @brief 执行修改操作
 */
void UpdateController::update()
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
    stuInfo.setLab(labMap.keys().at(ui->labComboBox->currentIndex()));
    //如果图片未设置，就不写入
    if(ui->photoView->pixmap())
    {
        stuInfo.setFaceImage(*(ui->photoView->pixmap()));
    }
    stuInfo.setEmail(ui->emailLineEdit->text());
    stuInfo.setTelephone(ui->telephoneLineEdit->text());
    stuInfo.setPassword(ui->passwordLineEdit->text());
    updateService->update(oldStudentId,stuInfo);
    this->close();
    this->parent->selectStuInfo();
    this->parent->selectTodaySignInfo();
    this->parent->selectHistorySignInfo();
}
