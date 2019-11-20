/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     AddDialog.h                                                     *
*  @brief    Add对话框的Dialog层实现                                           *
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

#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

namespace Ui {
class AddDialog;
}

/**
 * @brief AddDialog类
 * 属于Add对话框的Dialog层，继承自QDialog,用以添加学生信息
 */
class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();
protected:
    Ui::AddDialog *ui;
    /**
     * @brief 弹出FileDialog
     */
    virtual void showFileDialog()=0;
    /**
     * @brief 弹出CameraDialog
     */
    virtual void showCameraDialog()=0;
    /**
     * @brief 执行添加操作
     */
    virtual void add()=0;
private:
    /**
     * @brief 初始化
     */
    void init();
private slots:
    /**
     * @brief OpenFileDialogButton的单击响应事件
     */
    void onOpenFileClick(bool);
    /**
     * @brief OpenCameraDialogButton的单击响应事件
     */
    void onOpenCameraClick(bool);
    /**
     * @brief okButton的单击响应事件
     */
    void onOkClick(bool);
    /**
     * @brief cancelButon的单击响应事件
     */
    void onCancelClick(bool);

};

#endif // ADDDIALOG_H
