/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     AddController.h                                                 *
*  @brief    Add对话框的Controller层实现                                       *
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

#ifndef ADDCONTROLLER_H
#define ADDCONTROLLER_H

#include "AddDialog.h"
#include "AddService.h"
#include "AdminController.h"
#include "TeacherInfo.h"
#include <QWidget>

/**
 * @brief AddController类
 * 属于Add对话框的Controller层，继承自AddDialog
 */
class AddController : public AddDialog
{
public:
    AddController(int currentLabId,QWidget *parent = nullptr);
    ~AddController();

protected:
    /**
     * @brief 弹出fileDialog
     */
    void showFileDialog();
    /**
     * @brief 弹出CameraDialog
     */
    void showCameraDialog();
    /**
     * @brief 添加
     */
    void add();
private:
    AddService* addService;        ///< Service层
    QPixmap pixmap;                ///< photoView显示的图片
    int currentLabId;              ///< 默认所属实验室
    AdminController *parent;       ///< 成功后刷新父窗体
};

#endif // ADDCONTROLLER_H
