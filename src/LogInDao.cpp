/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     LogInDao.cpp                                                     *
*  @brief    LogIn面板的DAO层实现                                              *
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
*  2019/11/13 | 1.0.0.1   | Zixuan.Zhao    | Add function 'getLabInfo'       *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#include "LogInDao.h"
#include <QSqlQuery>
#include <QDebug>
#include <StringUtils.h>
#include "TeacherInfo.h"
LogInDao::LogInDao()
{
    db=MySqlUtils::getConnection("LogInDB");
}

LogInDao::~LogInDao()
{
    MySqlUtils::release(db,"LogInDB");
}

//判断是否登录成功
bool LogInDao::isLogInSuccess(QString userName, QString password)
{
    bool isSuccess=false;
    //设置sql语句
    QSqlQuery query("select * from accounts where accountId='"+userName+"' and password='"+StringUtils::toMd5(password+"Face@4A02")+"' and identity='teacher'",db);
    //查询结果
    isSuccess=query.next();
    //返回登录状态
    return isSuccess;
}

//获取教师和教师管理的实验室信息
TeacherInfo LogInDao::getTeacherInfo(QString userName)
{
    TeacherInfo teacherInfo;
    QMap<int,QString> labs;

    //设置sql语句
    QSqlQuery teacherInfoQuery("select * from teachers where teacherId='"+userName+"'",db);
    //获取管理员名字
    if(teacherInfoQuery.next())
    {
        //填充管理员信息
        teacherInfo.setTeacherId(teacherInfoQuery.value(0).toString());
        teacherInfo.setName(teacherInfoQuery.value(1).toString());
        teacherInfo.setSex(teacherInfoQuery.value(2).toString());
        teacherInfo.setDepartment(teacherInfoQuery.value(3).toString());
    }
    //获取管辖的实验室
    QSqlQuery labQuery("select labid,name from labs where director='"+userName+"'",db);
    //填充
    while (labQuery.next())
    {
        labs.insert(labQuery.value(0).toInt(),labQuery.value(1).toString());
    }
    teacherInfo.setLabs(labs);
    return teacherInfo;
}

/**
 * @brief 获取管辖的实验室信息
 * @param teacherId 教职工号
 * @return 所有管辖的实验室
 */
QVector<LabInfo> LogInDao::getLabInfo(QString teacherId)
{
    QVector<LabInfo> labsInfo;
    //获取管辖的实验室
    QSqlQuery labQuery("select labid,name,address,department,state,max,current from labs where director='"+teacherId+"'",db);
    //填充
    while (labQuery.next())
    {
        LabInfo labInfo;
        labInfo.setId(labQuery.value(0).toInt());
        labInfo.setName(labQuery.value(1).toString());
        labInfo.setAddress(labQuery.value(2).toString());
        labInfo.setDepartment(labQuery.value(3).toString());
        labInfo.setState(labQuery.value(4).toString());
        labInfo.setMax(labQuery.value(5).toInt());
        labInfo.setCurrent(labQuery.value(6).toInt());

        labsInfo.push_back(labInfo);
    }
    return labsInfo;
}
