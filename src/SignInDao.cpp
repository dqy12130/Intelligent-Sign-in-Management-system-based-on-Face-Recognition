/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao.Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     SignInDao.cpp                                                   *
*  @brief    SignIn面板的DAO层实现                                             *
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

#include "SignInDao.h"
#include <QDateTime>
#include <QDebug>
SignInDao::SignInDao()
{
    db=MySqlUtils::getConnection("SignInDB");
}

SignInDao::~SignInDao()
{
    MySqlUtils::release(db,"SignInDB");
}

/**
 * @brief 获取某实验室所有学生的信息
 * @param[in] labId 实验室id
 * @return 该实验室id所对应的实验室中所有学生的信息
 */
QVector<StudentInfo> SignInDao::getAllStuInfo(int labId)
{
    QVector<StudentInfo> studentsInfo;
    //获取所有学生的信息
    QSqlQuery allStuInfoQuery("select studentId,name,sex,grade,department,major,classes,facefeature from students where labId="+QString::number(labId),db);
    while(allStuInfoQuery.next())
    {
      StudentInfo stuInfo;
      stuInfo.setStudentId(allStuInfoQuery.value(0).toString());
      stuInfo.setName(allStuInfoQuery.value(1).toString());
      stuInfo.setSex(allStuInfoQuery.value(2).toString());
      stuInfo.setGrade(allStuInfoQuery.value(3).toInt());
      stuInfo.setDepartment(allStuInfoQuery.value(4).toString());
      stuInfo.setMajor(allStuInfoQuery.value(5).toString());
      stuInfo.setClasses(allStuInfoQuery.value(6).toInt());
      stuInfo.setFaceFeature(allStuInfoQuery.value(7).toByteArray());

      //保存
      studentsInfo.push_back(stuInfo);
    }
    return studentsInfo;
}

/**
 * @brief 判断某学生是否已签到，如果未签到，签到后返回false
 * @param[in] studentId 学号
 * @return 是否已签到
 */
bool SignInDao::isSignInSuccess(QString studentId)
{
    //获取当前时间
    QDateTime currentTime=QDateTime::currentDateTime();
    //获取年月日
    QString yyyyMMdd=currentTime.toString("yyyy-MM-dd");
    //查询是否已签到
    QSqlQuery isSignInQuery("select * from attendance where accountId='"+studentId+"' and date like '"+yyyyMMdd+"%'",db);
    if(isSignInQuery.next())
    {
        //如果已签到
        return true;
    }
    else
    {
       //如果未签到,插入签到信息
       QSqlQuery signInQuery("insert into attendance values('"+studentId+"','"+currentTime.toString("yyyy-MM-dd hh:mm:ss")+"')",db);
       return false;
    }
}
