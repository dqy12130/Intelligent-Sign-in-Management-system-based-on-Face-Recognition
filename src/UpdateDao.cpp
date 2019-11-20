/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao.Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     UpdateDao.cpp                                                   *
*  @brief    Update对话框的DAO层实现                                           *
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

#include "UpdateDao.h"
#include "StringUtils.h"
#include <QVariant>
UpdateDao::UpdateDao()
{
    db=MySqlUtils::getConnection("UpdataDB");
}

UpdateDao::~UpdateDao()
{
    MySqlUtils::release(db,"UpdataDB");
}

/**
 * @brief 修改学生的信息
 * @param oldStudentId 学生的原学号
 * @param newStuInfo 修改后的所有信息
 */
void UpdateDao::update(QString oldStudentId, StudentInfo newStuInfo)
{

    //执行sql语句更新学生表
    QString sql="update students set studentId=?,name=?,sex=?,grade=?,department=?,major=?,classes=?,labId=?,faceImage=?,faceFeature=? where studentId=?";
    QSqlQuery updateStudentQuery(db);
    updateStudentQuery.prepare(sql);
    updateStudentQuery.bindValue(0,newStuInfo.getStudentId());
    updateStudentQuery.bindValue(1,newStuInfo.getName());
    updateStudentQuery.bindValue(2,newStuInfo.getSex());
    updateStudentQuery.bindValue(3,newStuInfo.getGrade());
    updateStudentQuery.bindValue(4,newStuInfo.getDepartment());
    updateStudentQuery.bindValue(5,newStuInfo.getMajor());
    updateStudentQuery.bindValue(6,newStuInfo.getClasses());
    updateStudentQuery.bindValue(7,QString::number(newStuInfo.getLab()));
    QVariant var(newStuInfo.getFaceImage());
    updateStudentQuery.bindValue(8,var);
    updateStudentQuery.bindValue(9,newStuInfo.getFaceFeature());
    updateStudentQuery.bindValue(10,oldStudentId);
    updateStudentQuery.exec();

    //执行sql语句更新账户表
    if(newStuInfo.getPassword().isEmpty()==false)
    {
        sql="update accounts set password='"+StringUtils::toMd5(newStuInfo.getPassword())+"' where accountId='"+oldStudentId+"'";
        QSqlQuery updateAccountQuery(sql,db);
    }
    //执行sql语句更新附加信息表
    sql="update information set email='"+newStuInfo.getEmail()+"',telephone='"+newStuInfo.getTelephone()+"' where accountId='"+oldStudentId+"'";
    QSqlQuery updateInformationQuery(sql,db);

    //更新账户表的学号并级联更新附加信息表的学号
    sql="update accounts set accountId='"+newStuInfo.getStudentId()+"' where accountId='"+oldStudentId+"'";
    QSqlQuery updateAccountIdQuery(sql,db);
}
