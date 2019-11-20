/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     AddDialog.cpp                                                   *
*  @brief    Add对话框的Dialog层实现                                           *
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

#include "AddDialog.h"
#include "ui_AddDialog.h"

#include <QMessageBox>

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
    init();
}

AddDialog::~AddDialog()
{
    delete ui;
}

/**
 * @brief 初始化
 */
void AddDialog::init()
{
    //初始化Dialog
    this->setFixedSize(this->width(),this->height());
    setWindowTitle("添加学生");

    //初始化Slots
    //fileOpenButton
    connect(ui->fileOpenButton,SIGNAL(clicked(bool)),this,SLOT(onOpenFileClick(bool)));
    //cameraOpenButton
    connect(ui->cameraOpenButton,SIGNAL(clicked(bool)),this,SLOT(onOpenCameraClick(bool)));
    //okButton
    connect(ui->okButton,SIGNAL(clicked(bool)),this,SLOT(onOkClick(bool)));
    //cancelButton
    connect(ui->cancelButton,SIGNAL(clicked(bool)),this,SLOT(onCancelClick(bool)));
}

/**
 * @brief OpenFileDialogButton的单击响应事件
 */
void AddDialog::onOpenFileClick(bool)
{
    showFileDialog();
}
/**
 * @brief OpenCameraDialogButton的单击响应事件
 */
void AddDialog::onOpenCameraClick(bool)
{
    showCameraDialog();
}

/**
 * @brief okButton的单击响应事件
 */
void AddDialog::onOkClick(bool)
{
    //判空
    if(ui->studentIdLineEdit->text().isEmpty()||
            ui->nameLineEdit->text().isEmpty()||
            ui->departmentLineEdit->text().isEmpty()||
            ui->majorLineEdit->text().isEmpty()||
            ui->classesSpinBox->value()==0||
            ui->emailLineEdit->text().isEmpty()||
            ui->telephoneLineEdit->text().isEmpty()||
            ui->passwordLineEdit->text().isEmpty()||
            ui->rePasswordLineEdit->text().isEmpty())
    {

        QMessageBox::information(this,"提示","信息填写不完整");
    }
    //判断密码位数
    else if(ui->passwordLineEdit->text().length()<6)
    {
        QMessageBox::information(this,"提示","密码不能少于6位");
    }
    //判断密码
    else if(ui->passwordLineEdit->text()!=ui->rePasswordLineEdit->text())
    {
        QMessageBox::information(this,"提示","密码不一致");
    }
    //二次确认
    else if(QMessageBox::question(this,"添加","确定添加？")==QMessageBox::Yes)
    {
        add();
    }
}

/**
 * @brief cancelButon的单击响应事件
 */
void AddDialog::onCancelClick(bool)
{
    this->close();
}

