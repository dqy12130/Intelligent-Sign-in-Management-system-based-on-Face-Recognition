/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     AdminService.cpp                                                *
*  @brief    Admin面板的Service层实现                                          *
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
*  2019/11/13 | 1.0.0.1   | Zixuan.Zhao    | Add function 'selectDevicesInfo'*
*             |           |                | 'selectLogsInfo'                *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#include "AdminService.h"

AdminService::AdminService()
{
    adminDao=new AdminDao();
}

AdminService::~AdminService()
{
    delete adminDao;
}

/**
 * @brief 获取学生信息
 * @param[in] labid 归属实验室
 * @return 学生信息
 */
QVector<StudentInfo> AdminService::selectStuInfo(int labId)
{
    return adminDao->selectStuInfo(labId);
}

/**
 * @brief 删除学生
 * @param[in] studentsId 待删除学生的id
 */
void AdminService::deletStuInfo(QVector<QString> studentsId)
{
    adminDao->deletStuInfo(studentsId);
}

/**
 * @brief 获取今日签到排名
 * @param[in] labIdForToday 所属实验室
 * @return 今日签到排名
 */
QVector<TodaySignInfo> AdminService::selectTodaySignInfo(int labIdForToday)
{
    return adminDao->selectTodaySignInfo(labIdForToday);
}

/**
 * @brief 获取时间区间内的签到排名
 * @param[in] begin 起始时间
 * @param[in] end 终止时间啊
 * @param[in] labidForHistory 所属实验室
 * @return 历史签到信息
 */
QVector<HistorySignInfo> AdminService::selectHistorySignInfo(QDateTime begin, QDateTime end, int labidForHistory)
{
    return adminDao->selectHistorySignInfo(begin,end,labidForHistory);
}

/**
 * @brief 获取实验室的设备信息
 * @param labid 实验室Id
 * @return 设备信息
 */
QVector<DevicesInfo> AdminService::selectDevicesInfo(int labId)
{
    return adminDao->selectDevicesInfo(labId);
}

/**
 * @brief 获取实验室的某日的设备信息
 * @param labId 实验室id
 * @param dateTime 日期
 * @return 日志
 */
QVector<LogInfo> AdminService::selectLogsInfo(int labId, QDateTime dateTime)
{
    return  adminDao->selectLogsInfo(labId,dateTime);
}

/**
 * @brief 初始化checkbox
 * @param labId
 * @return 实验室是否已绑定该主机
 */
bool AdminService::initCheckBox(int labId)
{
    return adminDao->initCheckBox(labId);
}

/**
 * @brief 更新认证信息
 * @param labId 实验室id
 * @param state 更新状态（认证/取消认证）
 */
void AdminService::updateApproveState(int labId, int state)
{
    adminDao->updateApproveState(labId,state);
}




