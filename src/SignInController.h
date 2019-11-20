/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     SignInContorller.h                                              *
*  @brief    SignIn面板的Controller层实现                                      *
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

#ifndef SIGNINCONTROLLER_H
#define SIGNINCONTROLLER_H

#include "SignInWidget.h"
#include "SignInService.h"
#include <QThread>
#include <QMessageBox>
/**
 * @brief SignInController类
 * 继承自SignInWidget，属于SignIn面板的Controller层，用于初始化新线程进行人脸识别和匹配的工作，通过信号和槽与新线程
 * 通信，并即时返回签到状态信息
 */
class SignInController : public SignInWidget
{
    Q_OBJECT
public:
    SignInController(int labId, QWidget *parent=nullptr);
    ~SignInController();
protected:
    /**
     * @brief 跳转到Main面板
     */
    void showMainWidget();
    /**
     * @brief 对捕获的每一张图片进行后续处理
     * @param[in] image 捕获的图片
     */
    void doWork(QImage image);
private:
    SignInService *signInService;       ///< SignIn面板Service层
    QThread* signInServiceThread;       ///< Service层所在的新线程
signals:
    /**
     * @brief 开始进行后续处理的信号
     * @param[in] image 处理的照片
     */
    void sendImage(QImage image);
public slots:
    /**
     * @brief 用于显示图片后续处理过程的状态信息
     * @param text 状态信息
     */
    void receiveResult(QString text);
};

#endif // SIGNINCONTROLLER_H
