/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao.Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     MainService.cpp                                                 *
*  @brief    Main面板的Service层实现                                           *
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

#include "MainService.h"

MainService::MainService()
{
    //初始化Main面板的DAO层
    mainDao=new MainDao();
}

MainService::~MainService()
{
    delete mainDao;
}

/**
 * @brief 获取与当前主机关联的实验室id
 * @return 与当前主机关联的实验室id
 * @retval -1 未绑定的主机
 */
int MainService::isApproveHost()
{
    return mainDao->isApproveHost();
}
