/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     AdminDao.h                                                      *
*  @brief    Admin面板的DAO层实现                                              *
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
*             |           |                | 'selectLogInfo'                 *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#include "AdminDao.h"
#include "NetUtils.h"
#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

AdminDao::AdminDao()
{
    db=MySqlUtils::getConnection("AdminDB");
}

AdminDao::~AdminDao()
{
    MySqlUtils::release(db,"AdminDB");
}

/**
 * @brief 获取学生信息
 * @param[in] labid 归属实验室
 * @return 学生信息
 */
QVector<StudentInfo> AdminDao::selectStuInfo(int labId)
{
    QVector<StudentInfo> stuInfoVec;
    //设置语句
    QSqlQuery query("select students.studentId,name,sex,grade,department,major,classes,labId,faceImage,faceFeature,email,telephone"
                    " from students inner join information on information.accountId=students.studentId"
                    " where labId="+QString::number(labId),db);
    //获取结果
    while (query.next()) {
        StudentInfo stuInfo;
        stuInfo.setStudentId(query.value(0).toString());
        stuInfo.setName(query.value(1).toString());
        stuInfo.setSex(query.value(2).toString());
        stuInfo.setGrade(query.value(3).toInt());
        stuInfo.setDepartment(query.value(4).toString());
        stuInfo.setMajor(query.value(5).toString());
        stuInfo.setClasses(query.value(6).toInt());
        stuInfo.setLab(query.value(7).toInt());
        stuInfo.setFaceImage(query.value(8).toByteArray());
        stuInfo.setFaceFeature(query.value(9).toByteArray());
        stuInfo.setEmail(query.value(10).toString());
        stuInfo.setTelephone(query.value(11).toString());
        stuInfoVec.push_back(stuInfo);
    }

    return stuInfoVec;
}

/**
 * @brief 删除学生
 * @param[in] studentsId 待删除学生的id
 */
void AdminDao::deletStuInfo(QVector<QString> studentsId)
{
    //获取所有的学号
    for(QString studentId:studentsId)
    {
        //删除附加信息表
        QSqlQuery deleteInfo("delete from information where accountId='"+studentId+"'",db);
        //删除账户表
        QSqlQuery deleteAcc("delete from accounts where accountId='"+studentId+"'",db);
        //删除学生表
        QSqlQuery deleteStu("delete from students where studentId='"+studentId+"'",db);
    }
}
/**
 * @brief 刷新attendancePage中todaySignInfoTableWidget的内容，显示当天签到
 * 情况排名
 */
QVector<TodaySignInfo> AdminDao::selectTodaySignInfo(int labIdForToday)
{
    //获取今日时间
    QDateTime currentTime=QDateTime::currentDateTime();
    //获取年月日
    QString yyyyMMdd=currentTime.toString("yyyy-MM-dd");

    //所有的签到情况
    QVector<TodaySignInfo> todaySignInfoAll;

    //获取今日的已签到信息
    QSqlQuery signInfo("select date,studentId,name,sex,department,grade,major,classes"
                       " from attendance,students"
                       " where accountId in (select studentid from students where labId="+QString::number(labIdForToday)+")"
                       " and accountId = studentId"
                       " and date like '"+yyyyMMdd+"%'"
                       " order by date",db);
    while (signInfo.next())
    {
        TodaySignInfo todaySignInfo;
        todaySignInfo.setSignInDateTime(signInfo.value(0).toDateTime());

        StudentInfo stuInfo;
        stuInfo.setStudentId(signInfo.value(1).toString());
        stuInfo.setName(signInfo.value(2).toString());
        stuInfo.setSex(signInfo.value(3).toString());
        stuInfo.setDepartment(signInfo.value(4).toString());
        stuInfo.setGrade(signInfo.value(5).toInt());
        stuInfo.setMajor(signInfo.value(6).toString());
        stuInfo.setClasses(signInfo.value(7).toInt());
        todaySignInfo.setStuInfo(stuInfo);

        todaySignInfoAll.push_back(todaySignInfo);
    }

    //获取未签到学生的信息
    QSqlQuery unSignInfo("select studentId,name,sex,department,grade,major,classes"
                         " from students"
                         " where studentId not in"
                         " (select accountId"
                         " from attendance"
                         " where accountId in (select studentid from students where labId="+QString::number(labIdForToday)+")"
                         " and date like '"+yyyyMMdd+"%')"
                         " and labId="+QString::number(labIdForToday),db);
    while (unSignInfo.next())
    {
        TodaySignInfo todaySignInfo;

        StudentInfo stuInfo;
        stuInfo.setStudentId(unSignInfo.value(0).toString());
        stuInfo.setName(unSignInfo.value(1).toString());
        stuInfo.setSex(unSignInfo.value(2).toString());
        stuInfo.setDepartment(unSignInfo.value(3).toString());
        stuInfo.setGrade(unSignInfo.value(4).toInt());
        stuInfo.setMajor(unSignInfo.value(5).toString());
        stuInfo.setClasses(unSignInfo.value(6).toInt());
        todaySignInfo.setStuInfo(stuInfo);

        todaySignInfoAll.push_back(todaySignInfo);
    }

    return todaySignInfoAll;
}

/**
 * @brief 获取时间区间内的签到排名
 * @param[in] begin 起始时间
 * @param[in] end 终止时间啊
 * @param[in] labidForHistory 所属实验室
 * @return 历史签到信息
 */
QVector<HistorySignInfo> AdminDao::selectHistorySignInfo(QDateTime begin, QDateTime end, int labidForHistory)
{
    //历史签到信息
    QVector<HistorySignInfo> historySignInfoAll;

    //延后一天，保证当天能够被查询到
    end=end.addDays(1);
    //计算总签到次数
    QSqlQuery totalTimesQuery("select timestampdiff(day,'"+begin.toString("yyyy-MM-dd 00:00:00")+"','"+end.toString("yyyy-MM-dd 00:00:00")+"') as total",db);
    int total;
    if(totalTimesQuery.next())
    {
       total=totalTimesQuery.value(0).toInt();
    }
    //查询签到次数不为0的同学
    QSqlQuery signInInfoQuery("select  count(date) as signInTimes,studentId,name,sex,department,grade,major,classes"
                         " from students left join attendance on  studentId=accountId"
                         " where labid="+QString::number(labidForHistory)+" and date>='"+begin.toString("yyyy-MM-dd 00:00:00")+"' and date<='"+end.toString("yyyy-MM-dd 00:00:00")+"'"
                         " group by studentId"
                         " order by signInTimes desc",db);
    while(signInInfoQuery.next())
    {
        HistorySignInfo historyInfo;
        //签到的次数
        int signInTimes=signInInfoQuery.value(0).toInt();
        //未签次数
        int unSignInTimes=total-signInTimes;
        //录入签到信息
        historyInfo.setSignInTimes(signInTimes);
        historyInfo.setUnSignInTimes(unSignInTimes);
        historyInfo.setRate((float)unSignInTimes/(float)total);

        //录入学生信息
        StudentInfo stuInfo;
        stuInfo.setStudentId(signInInfoQuery.value(1).toString());
        stuInfo.setName(signInInfoQuery.value(2).toString());
        stuInfo.setSex(signInInfoQuery.value(3).toString());
        stuInfo.setDepartment(signInInfoQuery.value(4).toString());
        stuInfo.setGrade(signInInfoQuery.value(5).toInt());
        stuInfo.setMajor(signInInfoQuery.value(6).toString());
        stuInfo.setClasses(signInInfoQuery.value(7).toInt());
        historyInfo.setStuInfo(stuInfo);

        //记录到all
        historySignInfoAll.push_back(historyInfo);
    }

    //查询签到次数为0的同学
    QSqlQuery unSignInQuery("select studentId,name,sex,grade,department,major,classes"
                            " from students"
                            " where labid="+QString::number(labidForHistory)+
                            " and studentid not in"
                            " (select studentId"
                            " from students inner join attendance on studentId=accountId"
                            " where labid="+QString::number(labidForHistory)+" and date>='"+begin.toString("yyyy-MM-dd 00:00:00")+"' and date<= '"+end.toString("yyyy-MM-dd 00:00:00")+"'"
                            " group by studentId)",db);
    while (unSignInQuery.next())
    {
        HistorySignInfo historySignInfo;
        //签到信息
        historySignInfo.setSignInTimes(0);
        historySignInfo.setUnSignInTimes(total);
        historySignInfo.setRate(1.0f);

        //学生信息
        StudentInfo stuInfo;
        stuInfo.setStudentId(unSignInQuery.value(0).toString());
        stuInfo.setName(unSignInQuery.value(1).toString());
        stuInfo.setSex(unSignInQuery.value(2).toString());
        stuInfo.setGrade(unSignInQuery.value(3).toInt());
        stuInfo.setDepartment(unSignInQuery.value(4).toString());
        stuInfo.setMajor(unSignInQuery.value(5).toString());
        stuInfo.setClasses(unSignInQuery.value(6).toInt());
        historySignInfo.setStuInfo(stuInfo);

        //记录到所有签到信息中
        historySignInfoAll.push_back(historySignInfo);
    }
    return historySignInfoAll;
}

/**
 * @brief 获取实验室的设备信息
 * @param labid 实验室Id
 * @return 设备信息
 */
QVector<DevicesInfo> AdminDao::selectDevicesInfo(int labid)
{
    QVector<DevicesInfo> devices;
    QSqlQuery devicesQuery("select deviceId,name,max,loan,demage,remain from devices where labId="+QString::number(labid),db);
    while (devicesQuery.next())
    {
        DevicesInfo deviceInfo;
        deviceInfo.setId(devicesQuery.value(0).toInt());
        deviceInfo.setName(devicesQuery.value(1).toString());
        deviceInfo.setMax(devicesQuery.value(2).toInt());
        deviceInfo.setLoan(devicesQuery.value(3).toInt());
        deviceInfo.setDemage(devicesQuery.value(4).toInt());
        deviceInfo.setRemain(devicesQuery.value(5).toInt());

        devices.push_back(deviceInfo);
    }
    return devices;
}

/**
 * @brief 获取实验室的某日的设备信息
 * @param labId 实验室id
 * @param dateTime 日期
 * @return 日志
 */
QVector<LogInfo> AdminDao::selectLogsInfo(int labId, QDateTime dateTime)
{
    QVector<LogInfo> logsInfo;
    QSqlQuery logsInfoQuery("select devices.name,date,content"
                       " from deviceslog inner join labs on deviceslog.labId=labs.labId"
                       " inner join devices on deviceslog.deviceId=devices.deviceId"
                       " where deviceslog.labId="+QString::number(labId)+" and date like '"+dateTime.toString("yyyy-MM-dd")+"%'",db);
    while (logsInfoQuery.next()) {
        LogInfo logInfo;
        logInfo.setDeviceName(logsInfoQuery.value(0).toString());
        logInfo.setDate(logsInfoQuery.value(1).toDateTime());
        logInfo .setContent(logsInfoQuery.value(2).toString());
        logsInfo.push_back(logInfo);
    }
    return logsInfo;
}

/**
 * @brief 获取当前主机是否已绑定所选实验室
 * @param labId 实验室id
 * @return 是否已绑定本主机
 */
bool AdminDao::initCheckBox(int labId)
{
    //默认为未绑定
    bool isApprove=false;
    //获取本机的所有mac地址
    QVector<QString> allMac=NetUtils::getAllMac();
    //逐个判断mac地址
    for(QString mac:allMac)
    {
        QSqlQuery macQuery("select * from mac where macaddress='"+mac+"' and labid="+QString::number(labId),db);
        if(macQuery.next())
        {
            isApprove=true;
            break;
        }
    }
    return isApprove;
}

/**
 * @brief 更新认证信息
 * @param labId 实验室id
 * @param state 更新状态（认证/取消认证）
 */
void AdminDao::updateApproveState(int labId, int state)
{
    //获取本机的所有mac地址
    QVector<QString> allMac=NetUtils::getAllMac();
    //如果是添加认证，则使用insert语句
    if(state==Qt::Checked)
    {
        for(QString mac:allMac)
        {
            QSqlQuery insertQuery("insert into mac values('"+mac+"',"+QString::number(labId)+")",db);
        }
    }
    else
    {
        for(QString mac:allMac)
        {
            QSqlQuery deleteQuery("delete from mac where macAddress='"+mac+"' and labid="+QString::number(labId),db);
        }
    }
}
