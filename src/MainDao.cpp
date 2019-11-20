/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao.Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     MainDao.cpp                                                     *
*  @brief    Main面板的DAO层实现                                               *
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

#include "MainDao.h"
#include "NetUtils.h"
#include <QVariant>

MainDao::MainDao()
{
    //初始化数据库引擎
    db=MySqlUtils::getConnection("MainDB");
}

MainDao::~MainDao()
{
    //释放数据库引擎
    MySqlUtils::release(db,"MainDB");
}

/**
 * @brief 获取与当前主机关联的实验室id
 * @return 与当前主机关联的实验室id
 * @retval -1 未绑定的主机
 */
int MainDao::isApproveHost()
{
    //默认未认证
    int labid=-1;
    //获取本地主机的所有mac地址
    QVector<QString> macAddress=NetUtils::getAllMac();
    //查询与本机mac地址关联的实验室id
    for(QString mac:macAddress)
    {
        QSqlQuery macQuery("select labid from mac where macaddress='"+mac+"'",db);
        if(macQuery.next())
        {
            labid=macQuery.value(0).toInt();
            break;
        }
    }
    return labid;
}
