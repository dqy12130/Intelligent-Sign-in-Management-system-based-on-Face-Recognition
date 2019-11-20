/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     AddDao.cpp                                                      *
*  @brief    Add对话框的Dao层实现                                              *
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
#include "AddDao.h"
#include "StringUtils.h"
#include <QDebug>
#include <QVariant>

AddDao::AddDao()
{
    //获取数据库连接
    db=MySqlUtils::getConnection("addDB");
}

AddDao::~AddDao()
{
    //释放数据库连接
    MySqlUtils::release(db,"addDB");
}

/**
 * @brief 添加学生
 * @param stuInfo 学生信息
 */
void AddDao::add(StudentInfo stuInfo)
{

    //执行sql语句插入accounts表
    QString sql="insert into accounts values('"+stuInfo.getStudentId()+"','"+StringUtils::toMd5(stuInfo.getPassword())+"',0,null,'student')";
    QSqlQuery addAccountQuery(sql,db);


    //执行sql语句插入information表
    sql="insert into information values('"+stuInfo.getStudentId()+"','"+stuInfo.getEmail()+"','"+stuInfo.getTelephone()+"')";
    QSqlQuery addInformationQuery(sql,db);

    //执行sql语句插入学生表
    sql="insert into students values(?,?,?,?,?,?,?,?,?,?)";
    QSqlQuery addStudentQuery;
    addStudentQuery=QSqlQuery(db);
    addStudentQuery.prepare(sql);
    addStudentQuery.bindValue(0,stuInfo.getStudentId());
    addStudentQuery.bindValue(1,stuInfo.getName());
    addStudentQuery.bindValue(2,stuInfo.getSex());
    addStudentQuery.bindValue(3,stuInfo.getGrade());
    addStudentQuery.bindValue(4,stuInfo.getDepartment());
    addStudentQuery.bindValue(5,stuInfo.getMajor());
    addStudentQuery.bindValue(6,stuInfo.getClasses());
    addStudentQuery.bindValue(7,QString::number(stuInfo.getLab()));
    QVariant var(stuInfo.getFaceImage());
    addStudentQuery.bindValue(8,var);
    addStudentQuery.bindValue(9,stuInfo.getFaceFeature());
    addStudentQuery.exec();
}
