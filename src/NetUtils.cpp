/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao.Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     NetUtils.cpp                                                    *
*  @brief    Net处理中心                                                      *
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

#include "NetUtils.h"
#include <QNetworkInterface>
#include <QStringList>

/**
 * @brief 获取本地主机检测到的mac地址
 * @return mac地址
 */
QVector<QString> NetUtils::getAllMac()
{
    QStringList macList;
    QString strMac;
    QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
    for (int i=0; i<ifaces.count(); i++)
    {
        QNetworkInterface iface = ifaces.at(i);
        //过滤掉本地回环地址、没有开启的地址
        if (iface.flags().testFlag(QNetworkInterface::IsUp) && !iface.flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            //过滤掉虚拟地址
            if (!(iface.humanReadableName().contains("VMware",Qt::CaseInsensitive))&&!(iface.humanReadableName().contains("VirtualBox",Qt::CaseInsensitive)))
            {
                strMac = iface.hardwareAddress();
                macList.append(strMac);
            }
        }
    }
    return macList.toVector();
}
