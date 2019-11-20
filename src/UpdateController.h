/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao.Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     UpdateController.h                                              *
*  @brief    Update对话框的Controller层实现                                    *
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
#ifndef UPDATECONTROLLER_H
#define UPDATECONTROLLER_H

#include "UpdateDialog.h"
#include "UpdateService.h"
#include "AdminController.h"
#include "TeacherInfo.h"
#include <QWidget>

/**
 * @brief UpdateController类
 * 属于Update对话框的Controller层，继承自UpdateDialog
 */
class UpdateController : public UpdateDialog
{
public:
    UpdateController(QMap<int,QString> labMap,StudentInfo oldStuInfo,QWidget *parent = nullptr);
    ~UpdateController();

protected:
    /**
     * @brief 弹出FileDialog
     */
    void showFileDialog();
    /**
     * @brief 弹出CameraDialog
     */
    void showCameraDialog();
    /**
     * @brief 执行修改操作
     */
    void update();

private:
    UpdateService* updateService;       ///< updateService层
    QPixmap pixmap;                     ///< photoView显示的图片
    QString oldStudentId;               ///< 待修改学生的原学号
    QMap<int,QString> labMap;           ///< 可供选择的实验室
    AdminController *parent;            ///< 刷新父窗体
};

#endif // UPDATECONTROLLER_H
