
/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019  Qiyao.Dai     2650822367@qq.com                       *
*                      Zixuan.Zhao   zxZhao1998@gmail.com                    *
*                                                                            *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     SystemConf.h                                                    *
*  @brief    系统配置信息                                                      *
*  @author   Qiyao Dai                                                       *
*  @email    2650822367@qq.com                                               *
*  @version  1.0.0.1                                                         *
*  @date    2019.11.19                                                       *
*  @license  GNU General Public License (GPL)                                *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2019/09/10 | 1.0.0.1   |  Qiyao Dai    | Create file                      *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#include "SystemConf.h"
#include<QDebug>
SystemConf::SystemConf()
{
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    m_systemSetting.setIniCodec(codec);//设置编码格式
}

SystemConf::SystemConf( QString confFile)
{
    this->m_confFile=confFile;
}
QMap<QString,QString>  SystemConf::SyncFile(QString fileName)
{
    m_settingMap.clear();
    QSettings Setting(fileName,QSettings::IniFormat);
    if(m_confFile.isEmpty()==true)
        return m_settingMap;
    QString sqlDriveName= Setting.value("SqlDriveName").toString();
    m_settingMap.insert("SqlDriveName",sqlDriveName);
    QString sqlHostIp= Setting.value("SqlHostIp").toString();
    m_settingMap.insert("SqlHostIp",sqlHostIp);

    QString sqlHosPort= Setting.value("SqlHostPort").toString();
    m_settingMap.insert("SqlHostPort",sqlHosPort);

    QString dataBaseName= Setting.value("DataBaseName").toString();
    m_settingMap.insert("DataBaseName",dataBaseName);

    QString sqlUserName= Setting.value("SqlUserName").toString();
    m_settingMap.insert("SqlUserName",sqlUserName);

    QString sqlUserPassword= Setting.value("SqlUserPassword").toString();
    m_settingMap.insert("SqlUserPassword",sqlUserPassword);

    QString sqlCodec= Setting.value("SqlCodec").toString();

    m_settingMap.insert("SqlCodec",sqlCodec);
    QString cryptionLevel= Setting.value("CryptionLevel").toString();
    m_settingMap.insert("CryptionLevel",cryptionLevel);
    return  m_settingMap;
}


void SystemConf::SetConfFile(QString confFile)
{
    this->m_confFile=confFile;
}
QString  SystemConf::GetConfFileName()
{
    return this->m_confFile;
}

void SystemConf::SetConf(QMap<QString,QString>settingMap)
{
    QMap<QString,QString> conf;
    QString fileName="./Conf/sqlconf.conf";
    conf.clear();
    QSettings setting(fileName,QSettings::IniFormat);
    auto begin=settingMap.begin();
    auto end=settingMap.end();
    for(;begin!=end;begin++)
    {
        setting.setValue(begin.key(),begin.value());
    }
}
QMap<QString,QString>SystemConf::GetConf()//得到数据库配置文件信息
{
    QMap<QString,QString> conf;
    QString fileName="./Conf/sqlconf.conf";//数据库配置文件路径
    SystemConf syn;
    syn.SetConfFile(fileName);
    conf= syn.SyncFile(fileName);
    return  conf;
}

QMap<QString,QString> SystemConf::GetActiveFileConf()//得到激活配置文件的配置信息
{
    QString fileName="./Conf/ActiveFile.conf";//认证文件路径
    QMap<QString,QString> settingMap;
    settingMap.clear();
    QSettings Setting(fileName,QSettings::IniFormat);
    QString activeFileName= Setting.value("ActiveFile").toString();
    settingMap.insert("ActiveFile",activeFileName);
    qDebug()<<settingMap.find("ActiveFile").value();
    return  settingMap;
}


QByteArray SystemConf::Encryption(QByteArray src,int enCryptionLevel)//加密
{
    QByteArray dst=src;
    for(int i=0;i<enCryptionLevel;i++)
    {
        dst=dst.toBase64();
    }
    return  dst;
}
QString SystemConf::Encryption(QString src,int enCryptionLevel)
{

    QByteArray dst=src.toLatin1();
    for(int i=0;i<enCryptionLevel;i++)
    {
        dst=dst.toBase64();
    }
    QString str=dst;
    return  str;
}


QByteArray SystemConf::Decryption(QByteArray src,int deCryptionLevel)//解密
{
    QByteArray dst=src;
    for(int i=0;i<deCryptionLevel;i++)
    {
        dst=dst.fromBase64(dst);
    }
    return  dst;
}


QString SystemConf::Decryption(QString src,int deCryptionLevel)
{

    QByteArray dst=src.toLatin1();
    for(int i=0;i<deCryptionLevel;i++)
    {
        dst=dst.fromBase64(dst);
    }
    QString str=dst;
    return  str;
}



