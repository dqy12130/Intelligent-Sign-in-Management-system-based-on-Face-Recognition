
/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019  Qiyao Dai     2650822367@qq.com                       *
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
#ifndef SYSTEMCONF_H
#define SYSTEMCONF_H
#include<QSettings>
#include<QFile>
#include<QTextCodec>
#include<QByteArray>
class SystemConf//:public QSettings
{
public:
    SystemConf();
    SystemConf( QString confFile);
    void SetConfFile(QString confFile);

    /**
     * @brief 得到配置文件名称
     * @return  配置文件名称
     */
    QString  GetConfFileName();

    /**
     * @brief 得到配置文件的信息
     * @return 配置文件QMap
     */
    static QMap<QString,QString> GetConf();//得到配置文件的配置信息
    /*
     * @brief 设置配置信息
      * @param[in] infoMap 配置信息
     * @return
    */
    static void SetConf( QMap<QString,QString> infoMap);//设置配置信息
    /*
     * @brief 数据加密
      * @param[in] byte 待加密的数据
      * @param[in] enCryptionLevel 加密等级
     * @return 加密后的数据
    */
    static QByteArray Encryption(QByteArray byte,int enCryptionLevel=10);//加密,参数二是加密次数

    /*
     * @brief 数据解密
      * @param[in] byte 待解密的数据
      * @param[in] enCryptionLevel 加密等级
     * @return 解密后的数据
    */
    static QByteArray Decryption(QByteArray,int deCryptionLevel=10);//解密，参数二是解密次数

    /*
     * @brief 数据加密
      * @param[in] byte 待加密的数据
      * @param[in] enCryptionLevel 加密等级
     * @return 加密后的数据
    */
    static QString Encryption(QString,int enCryptionLevel=10);//加密,参数二是加密次数

    /*
     * @brief 数据解密
      * @param[in] byte 待解密的数据
      * @param[in] enCryptionLevel 加密等级
     * @return 解密后的数据
    */
    static QString Decryption(QString,int deCryptionLevel=10);//解密，参数二是解密次数

    /*
     * @brief 得到认证文件的信息(用于签到机）
     *
     * @return 得到认证文件QMap
    */
    static QMap<QString,QString> GetActiveFileConf();//得到认证文件的配置信息

private:
    QMap<QString,QString> SyncFile(QString fileName);
    QSettings m_systemSetting;
    QString m_confFile;
    QMap<QString,QString> m_settingMap;
};

#endif // SYSTEMCONF_H
