/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     AdminController.h                                               *
*  @brief    Admin面板的Controller层实现                                       *
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
*  2019/11/12 | 1.0.0.1   | Zixuan.Zhao    | Add function 'selectDeviceInfo' *
*----------------------------------------------------------------------------*
*  2019/11/13 | 1.0.0.1   | Zixuan.Zhao    | Update function                 *
*             |           |                | 'AdminController'               *
*             |           |                | 'selectAllDeviceLogInfo'        *
*             |           |                | Add variable 'labs'             *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#ifndef ADMINCONTROLLER_H
#define ADMINCONTROLLER_H

#include "AdminWidget.h"
#include "AdminService.h"
#include "TeacherInfo.h"
#include "LabInfo.h"
#include <QStandardItemModel>


/**
 * @brief AdminController类
 * 属于Admin面板的Controller层，继承自AdminWidget，用以显示刷新tableWidget，弹出增删改查对话框等，
 * 需要使用已登录教师的信息进行初始化
 */
class AdminController : public AdminWidget
{
public:
    AdminController(TeacherInfo teacherInfo,QVector<LabInfo> labs,QWidget* parent=nullptr);
    AdminController(TeacherInfo teacherInfo);
    ~AdminController();

public:
    /**
     * @brief 刷新userManagePage中infoTableWidget的内容,用于展示当前所选实验室中
     * 所有学生的信息，便于进一步增删改查
     */
    void selectStuInfo();
    /**
     * @brief 刷新attendancePage中todaySignInfoTableWidget的内容，显示当天签到
     * 情况排名
     */
    void selectTodaySignInfo();
    /**
     * @brief 刷新attendancePage中historySignInfoTableWidget的内容，显示当前所选
     * 时间区间内的签到排名
     */
    void selectHistorySignInfo();
    /**
     * @brief 刷新devicePage中deviceInfotableWidget的内容，显示当前实验室中的设备信息
     */
    void selectDeviceInfo();
    /**
     * @brief 刷新devicePage中deviceLogInfo的内容，根据实验室id和datetime显示当前实验室中的当天所有的设备日志
     */
    void selectAllDeviceLogInfo();
protected:
    /**
     * @brief 显示学生的照片在photoView
     */
    void showPhoto();
    /**
     * @brief 注销（跳转到LogIn面板）
     */
    void showLogInWidget();
    /**
     * @brief 弹出用来添加学生的Dialog
     */
    void showAddDialog();
    /**
     * @brief 删除已选学生，支持多选
     */
    void deleteStuInfo();
    /**
     * @brief 弹出用来修改学生信息的Dialog
     */
    void showUpdateDialog();
    /**
     * @brief 初始化checkbox
     */
    void initCheckBox();
    /**
     * @brief 更新认证信息
     */
    void updateApproveState();
private:
    AdminService *adminService;             ///< Service层

    //! Admin面板
    //! 登录后自动获取，重新登录以更新
    TeacherInfo teacherInfo;                ///< 记录当前登录教师的信息
    QVector<LabInfo> labs;                  ///< 记录当前登录教师管辖的实验室信息

    //! userManagePage
    //! 随用户操作而改变
    int currentUserManagePageLabId;         ///< 记录userManagePage中labCmb选中的实验室id,便于后续的add和update操作
    QVector<StudentInfo> currentStuInfo;    ///< 记录userMangePage中infoTableWidget当前显示的内容

    //! devicesManagePage
    //! 随用户操作而改变
    int currentDevicesManagePageLabId;      ///< 记录devicesManagePage中labCmb选中的实验室id
    QVector<DevicesInfo> currentDevInfo;    ///< 记录devicesManagePage中devicesInfoTableWidget当前显示的内容
    QVector<LogInfo> currentLogInfo;        ///< 记录devicesManagePage中devicesLogInfoListsWidget当前显示的内容
};

#endif // ADMINCONTROLLER_H
