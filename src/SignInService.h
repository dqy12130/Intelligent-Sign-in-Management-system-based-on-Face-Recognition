/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao.Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     SignInService.h                                                 *
*  @brief    SignIn面板的Service层实现                                         *
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

#ifndef SIGNINSERVICE_H
#define SIGNINSERVICE_H

#include "SignInDao.h"
#include "ArcSoftFaceUtils.h"
#include <QObject>
#include <QTime>

/**
 * @brief SignInService类
 * 属于SignIn面板的Service层，继承自QObject，运行在GUI线程外，用以初始化人脸识别引擎并进行人脸识别和
 * 匹配等耗时操作
 */
class SignInService:public QObject
{
    Q_OBJECT
public:
    SignInService(int labId);
    ~SignInService();
private:
    SignInDao* signDao;                     ///< SignIn面板DAO层
    MHandle handle;                         ///< 人脸识别引擎句柄
    QVector<StudentInfo> studentsInfo;      ///< 人脸信息库
signals:
    /**
     * @brief 当前图片处理的状态信号
     * @param text 状态信息
     */
    void sendResult(QString text);
public slots:
    /**
     * @brief 图片的处理Slot
     * @param image 处理的图片
     */
    void receiveImage(QImage image);

};

#endif // SIGNINSERVICE_H
