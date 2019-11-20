/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     AdminService.h                                                  *
*  @brief    Admin面板的Service层实现                                          *
*                                                                            *
*  @author    Qiyao Dai,Zixuan Zhao                                          *
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

#ifndef ADMINSERVICE_H
#define ADMINSERVICE_H

#include "AdminDao.h"

/**
 * @brief AdminService类
 * Admin面板的Service层，用以初始化Dao层，提供获取学生信息，删除学生，获取今日签到排名，获取历史签到排名
 */
class AdminService
{
public:
    AdminService();
    ~AdminService();
public:

    /**
     * @brief 获取学生信息
     * @param[in] labid 归属实验室
     * @return 学生信息
     */
    QVector<StudentInfo> selectStuInfo(int labid);
    /**
     * @brief 删除学生
     * @param[in] studentsId 待删除学生的id
     */
    void deletStuInfo(QVector<QString> studentsId);
    /**
     * @brief 获取今日签到排名
     * @param[in] labIdForToday 所属实验室
     * @return 今日签到排名
     */
    QVector<TodaySignInfo> selectTodaySignInfo(int labIdForToday);
    /**
     * @brief 获取时间区间内的签到排名
     * @param[in] begin 起始时间
     * @param[in] end 终止时间啊
     * @param[in] labidForHistory 所属实验室
     * @return 历史签到信息
     */
    QVector<HistorySignInfo> selectHistorySignInfo(QDateTime begin,QDateTime end,int labidForHistory);
    /**
     * @brief 获取实验室的设备信息
     * @param labid 实验室Id
     * @return 设备信息
     */
    QVector<DevicesInfo> selectDevicesInfo(int labId);
    /**
     * @brief 获取实验室的某日的设备信息
     * @param labId 实验室id
     * @param dateTime 日期
     * @return 日志
     */
    QVector<LogInfo> selectLogsInfo(int labId,QDateTime dateTime);
    /**
     * @brief 初始化checkbox
     * @param labId
     * @return 实验室是否已绑定该主机
     */
    bool initCheckBox(int labId);
    /**
     * @brief 更新认证信息
     * @param labId 实验室id
     * @param state 更新状态（认证/取消认证）
     */
    void updateApproveState(int labId,int state);
private:
    AdminDao* adminDao;     ///< DAO层
};

#endif // ADMINSERVICE_H
