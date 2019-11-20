/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019 Zixuan.Zhao   zxZhao1998@gmail.com                     *
*                     Qiyao.Dai     2650822367@qq.com                        *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     UpdateDialog.h                                                  *
*  @brief    Update对话框的Dialog层实现                                        *
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

#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H
#include <QDialog>

namespace Ui {
class UpdateDialog;
}

/**
 * @brief UpdateDialog类
 * 属于Update对话框的Dialog层，继承自QDialog
 */
class UpdateDialog : public QDialog
{
    Q_OBJECT
public:
    explicit UpdateDialog(QWidget *parent = nullptr);
    ~UpdateDialog();

protected:
    Ui::UpdateDialog *ui;
    /**
     * @brief 弹出FileDialog
     */
    virtual void showFileDialog()=0;
    /**
     * @brief 弹出CameraDialog
     */
    virtual void showCameraDialog()=0;
    /**
     * @brief 执行修改操作
     */
    virtual void update()=0;

private:
    /**
     * @brief 初始化操作
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

#endif // UPDATEDIALOG_H
