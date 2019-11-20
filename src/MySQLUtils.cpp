/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao.Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     MySqlUtils.cpp                                                  *
*  @brief    MySql数据库处理中心                                               *
*                                                                            *
*  @author   Zixuan Zhao ,Qiyao Dai                                          *
*  @email    zxZhao1998@gmail.com,2650822367@qq.com                          *
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
*  2019/11/19 | 1.0.0.1   | Qiyao Dai      | update function'getConnection'  *
*----------------------------------------------------------------------------*                                                                        *
*****************************************************************************/

#include "MySqlUtils.h"
#include <QDebug>
#include <QTextCodec>
#include<QMessageBox>
/**
 * @brief 获取数据库连接
 * @param connectName 连接命名
 * @return 数据库连接
 */
//获取连接
QSqlDatabase MySqlUtils::getConnection(QString d)
{
    if(QSqlDatabase::contains("mysql")==true)
    {
        qDebug()<<"获取到已连接数据库";
        return QSqlDatabase::database("mysql");
    }
    QSqlDatabase db;

    //数据库配置读取
    QMap<QString,QString>settingmap=SystemConf::GetConf();
    QString sqlDriveName=settingmap.find("SqlDriveName").value();//数据库驱动
    QString sqlHostIp=settingmap.find("SqlHostIp").value();//主机
    QString sqlHostPort=settingmap.find("SqlHostPort").value();//端口
    QString dataBaseName=settingmap.find("DataBaseName").value();//数据库
    QString sqlUserName=settingmap.find("SqlUserName").value();//用户名
    QString sqlUserPassword=settingmap.find("SqlUserPassword").value();//密码
    QString sqlCodec=settingmap.find("SqlCodec").value();
    QString cryptionLevel=settingmap.find("CryptionLevel").value();//加密等级
    db=QSqlDatabase::addDatabase(sqlDriveName);
    db.setHostName(sqlHostIp);
    db.setPort(sqlHostPort.toInt());
    db.setDatabaseName(dataBaseName);
    db.setUserName(SystemConf::Decryption(sqlUserName,cryptionLevel.toInt()));//解密
    db.setPassword(SystemConf::Decryption(sqlUserPassword,cryptionLevel.toInt()));//解密
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);

    //数据库配置写入文件
    //    QMap<QString,QString>setMap;
    //    setMap.insert("SqlDriveName","QMYSQL");
    //    setMap.insert("SqlHostIp","service host IP");
    //    setMap.insert("SqlHostPort","service host Port");
    //    setMap.insert("DataBaseName","sql  Database");
    //    QString  CryptionLevel="5";
    //    setMap.insert("CryptionLevel",CryptionLevel);//加密次数
    //    setMap.insert("SqlUserName",SystemConf::Encryption(QString("user name"),CryptionLevel.toInt()));//用户名加密
    //    setMap.insert("SqlUserPassword",SystemConf::Encryption(QString("password"),CryptionLevel.toInt()));//用户密码加密
    //    setMap.insert("SqlCodec","utf-8");
    //    SystemConf::SetConf(setMap);


    //如果连接失败
    if(db.open()==false)
    {
        qDebug()<<"数据库连接失败";
    }
    else
    {
        qDebug()<<"数据库连接成功";
    }
    return db;
}

/**
 * @brief 释放数据库连接
 * @param db 释放的数据库
 * @param connectName 目标名
 */
//关闭连接，释放资源
void MySqlUtils::release(QSqlDatabase db,QString x)
{
    if(db.isValid()==true)
    {

        db.close();
        QSqlDatabase::removeDatabase("QMYSQL");
        qDebug()<<"数据库已关闭！";
    }
}




