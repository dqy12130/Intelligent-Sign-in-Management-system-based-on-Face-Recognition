/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     AdminWidget.h                                                   *
*  @brief    Admin面板的Widget层实现，Admin面板有3个Page,userManagePage、       *
*            attendancePage、devicesManagePage,分别用来表示学生管理页面、        *
*            签到统计页面、设备管理页面                                          *
*                                                                            *
*  @author   Zixuan Zhao ,Qiyao Dai                                          *
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
*  2019/11/12 | 1.0.0.1   | Zixuan.Zhao    | Add function 'selectDeviceInfo' *
*             |           |                | 'onDeviceComboBoxChanged'       *
*  2019/11/13 | 1.0.0.1   | Zixuan.Zhao    | 'selectAllDeviceLogInfo'        *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include <QWidget>

namespace Ui {
class AdminWidget;
}

/**
 * @brief AdminWidget类
 * 属于Admin面板的Widget层实现，继承自QWidget,用以初始化GUI,提供管理员的一系列操作
 */
class AdminWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdminWidget(QWidget *parent = nullptr);
    ~AdminWidget();
public:
    /**
     * @brief 刷新userManagePage中infoTableWidget的内容,用于展示当前所选实验室中
     * 所有学生的信息
     */
    virtual void selectStuInfo()=0;
    /**
     * @brief 刷新attendancePage中todaySignInfoTableWidget的内容，显示当天签到
     * 情况排名
     */
    virtual void selectTodaySignInfo()=0;
    /**
     * @brief 刷新attendancePage中historySignInfoTableWidget的内容，显示当前所选
     * 时间区间内的签到排名
     */
    virtual void selectHistorySignInfo()=0;
    /**
     * @brief 刷新devicePage中deviceInfotableWidget的内容，显示当前实验室中的设备信息
     */
    virtual void selectDeviceInfo()=0;
    /**
     * @brief 刷新devicePage中deviceLogInfo的内容，根据实验室id和datetime显示当前实验室中的当天所有的设备日志
     */
    virtual void selectAllDeviceLogInfo()=0;
protected:
    Ui::AdminWidget *ui;

    /**
     * @brief 显示学生的照片在photoView
     */
    virtual void showPhoto()=0;
    /**
     * @brief 注销（跳转到LogIn面板）
     */
    virtual void showLogInWidget()=0;
    /**
     * @brief 弹出用来添加学生的Dialog
     */
    virtual void showAddDialog()=0;
    /**
     * @brief 删除已选学生，支持多选
     */
    virtual void deleteStuInfo()=0;
    /**
     * @brief 弹出用来修改学生信息的Dialog
     */
    virtual void showUpdateDialog()=0;

    /**
     * @brief 初始化devicesManagerPage的checkbox
     */
    virtual void initCheckBox()=0;
    /**
     * @brief 改变认证状态
     */
    virtual void updateApproveState()=0;

private:
    /**
     * @brief 初始化操作
     */
    void init();
private slots:
    /**
     * @brief userManagePage中labCmb的ChangedSlot
     */
    void onComboBoxChanged();
    /**
     * @brief userManagePage中infoTableWidget的ChangedSlot
     */
    void onTableWidgetChanged();
    /**
     * @brief userManagePage中logOutbutton的clickSlot
     */
    void onLogOutClick(bool);
    /**
     * @brief userManagePage中addButton的clickSlot
     */
    void onAddClick(bool);
    /**
     * @brief userManagePage中deleteButton的clickSlot
     */
    void onDeleteClick(bool);
    /**
     * @brief userManagePage中updateButton的clickSlot
     */
    void onUpdateClick(bool);
    /**
     * @brief attendancePage中todayComboBox的ChangedSlot
     */
    void onTodayComboBoxChanged();
    /**
     * @brief attendancePage中historyComboBox的ChangedSlot
     */
    void onHistoryComboBoxChanged();
    /**
     * @brief devicePage中deviceLabComboBox的ChangedSlot
     */
    void onDeviceComboBoxChanged();
    /**
     * @brief devicePage中dateEdit的ChangedSlot
     */
    void onDeviceDateEditChanged();
    /**
     * @brief CheckBox的ChangedSlot
     */
    void onCheckBoxStateChanged(int state);
};

#endif // ADMINWIDGET_H
