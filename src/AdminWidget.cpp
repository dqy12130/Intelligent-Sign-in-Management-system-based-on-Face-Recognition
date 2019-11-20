/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     AdminWidget.cpp                                                 *
*  @brief    Admin面板的Widget层实现，Admin面板有3个Page,userManagePage、        *
*            attendancePage、devicesManagePage,分别表示学生管理页面、            *
*            签到统计页面、设备管理页面                                          *
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
*  2019/11/12 | 1.0.0.1   | Zixuan.Zhao    | Add function                    *
*             |           |                | 'onDeviceComboBoxChanged'       *
*             |           |                | Add connection                  *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#include "AdminWidget.h"
#include "ui_AdminWidget.h"
#include "TeacherInfo.h"
#include "QTableWidget"
#include <QMessageBox>
#include <QDebug>
AdminWidget::AdminWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWidget)
{
    ui->setupUi(this);
    init();
}

AdminWidget::~AdminWidget()
{
    delete ui;
}

/**
 * @brief 初始化操作
 */
void AdminWidget::init()
{
    //Widget初始化
    setFixedSize(this->width(), this->height());  //禁止改变大小

    //listWidget初始化
    ui->listWidget->setCurrentRow(0);

    //设置dateTimeEdit的默认时间
    ui->beginDateEdit->setDateTime(QDateTime::currentDateTime());
    ui->endDateEdit->setDateTime(QDateTime::currentDateTime());
    //设置dateTimeEdit的最大时间
    ui->beginDateEdit->setMaximumDateTime(QDateTime::currentDateTime());
    ui->endDateEdit->setMaximumDateTime(QDateTime::currentDateTime());
    //设置logDateTimeEdit的当前时间和最大时间
    ui->deviceLogDateEdit->setMaximumDateTime(QDateTime::currentDateTime());
    ui->deviceLogDateEdit->setDateTime(QDateTime::currentDateTime());

    //初始化Slots
    //侧边栏与Page
    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
    //labCmb和infoTableWidget关联
    connect(ui->labCmb,SIGNAL(currentIndexChanged(int)),this,SLOT(onComboBoxChanged()));
    //infoTableWidget
    connect(ui->infoTableWidget,SIGNAL(itemSelectionChanged()),this,SLOT(onTableWidgetChanged()));
    //logOutButton
    connect(ui->logOutButton,SIGNAL(clicked(bool)),this,SLOT(onLogOutClick(bool)));
    //addButton
    connect(ui->addButton,SIGNAL(clicked(bool)),this,SLOT(onAddClick(bool)));
    //deleteButton
    connect(ui->deleteButton,SIGNAL(clicked(bool)),this,SLOT(onDeleteClick(bool)));
    //updateButton
    connect(ui->updateButton,SIGNAL(clicked(bool)),this,SLOT(onUpdateClick(bool)));
    //关联DateTimeEditChanged和historyWidget(放在初始化之后防止初始化过程中默认发送信号)
    connect(ui->beginDateEdit,SIGNAL(dateTimeChanged(QDateTime)),this,SLOT(onHistoryComboBoxChanged()));
    connect(ui->endDateEdit,SIGNAL(dateTimeChanged(QDateTime)),this,SLOT(onHistoryComboBoxChanged()));
    //关联todayComobBox和todayWidget
    connect(ui->todayLabComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onTodayComboBoxChanged()));
    //关联historyComboBox和historyWidget
    connect(ui->historyComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onHistoryComboBoxChanged()));
    //关联deviceLabComobBox和deviceInfoTableWidget
    connect(ui->deviceLabComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onDeviceComboBoxChanged()));
    //关联deviceDateEdit的ChangedSlots
    connect(ui->deviceLogDateEdit,SIGNAL(dateTimeChanged(QDateTime)),this,SLOT(onDeviceDateEditChanged()));
    //关联ckeckbox的单击事件
    connect(ui->boundCheckBox, SIGNAL(stateChanged(int)), this, SLOT(onCheckBoxStateChanged(int)));
}

/**
 * @brief userManagePage中labCmb的ChangedSlot
 */
void AdminWidget::onComboBoxChanged()
{
    selectStuInfo();
}

/**
 * @brief userManagePage中infoTableWidget的ChangedSlot
 */
void AdminWidget::onTableWidgetChanged()
{
    showPhoto();
}
/**
 * @brief userManagePage中logOutbutton的clickSlot
 */
void AdminWidget::onLogOutClick(bool)
{
    showLogInWidget();
}

/**
 * @brief userManagePage中addButton的clickSlot
 */
void AdminWidget::onAddClick(bool)
{
    showAddDialog();
}

/**
 * @brief userManagePage中deleteButton的clickSlot
 */
void AdminWidget::onDeleteClick(bool)
{
    if(ui->infoTableWidget->selectedItems().isEmpty())
    {
        QMessageBox::warning(this,"提示","请选择学生");
    }
    else if(QMessageBox::question(this,"删除","是否删除？")==QMessageBox::Yes)
    {
        deleteStuInfo();
    }
}

/**
 * @brief userManagePage中updateButton的clickSlot
 */
void AdminWidget::onUpdateClick(bool)
{
    if(ui->infoTableWidget->selectedItems().isEmpty())
    {
        QMessageBox::warning(this,"提示","请选择学生");
    }
    else
    {
        showUpdateDialog();
    }
}
/**
 * @brief attendancePage中todayComboBox的ChangedSlot
 */
void AdminWidget::onTodayComboBoxChanged()
{
    selectTodaySignInfo();
}

/**
 * @brief attendancePage中historyComboBox的ChangedSlot
 */
void AdminWidget::onHistoryComboBoxChanged()
{
    selectHistorySignInfo();
}

/**
 * @brief devicePage中deviceLabComboBox的ChangedSlot
 */
void AdminWidget::onDeviceComboBoxChanged()
{
    selectDeviceInfo();
    selectAllDeviceLogInfo();
    initCheckBox();
}

/**
 * @brief devicePage中dateEdit的ChangedSlot
 */
void AdminWidget::onDeviceDateEditChanged()
{
    selectAllDeviceLogInfo();
}

/**
 * @brief CheckBox的ChangedSlot
 */
void AdminWidget::onCheckBoxStateChanged(int state)
{
    updateApproveState();
}
