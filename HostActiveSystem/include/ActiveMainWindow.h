
/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019  Qiyao.Dai     2650822367@qq.com                       *
*                                                                            *
*                                                                            *                                                                          *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     ActiveMainWindow.h                                              *
*  @brief   签到机认证                                                        *
*                                                                            *
*  @author   Qiyao.Dai                                                       *
*  @email    2650822367@qq.com                                               *
*  @version  1.0.0.1                                                         *
*  @date     2019.11.10                                                      *
*  @license  GNU General Public License (GPL)                                *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2019/09/10 | 1.0.0.1   | Qiyao.Dai,Zixuan.Zhao    | Create file           *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/


#ifndef ACTIVEMAINWINDOW_H
#define ACTIVEMAINWINDOW_H

#include <QMainWindow>
#include<QFileDialog>
#include<QFile>
#include<QMessageBox>
#include<QDebug>
#include<QSqlDatabase>
#include"MySqlUtils.h"
#include<StringUtils.h>
#include<QSqlError>
#include<TeacherInfo.h>
#include<asvloffscreen.h>
#include<amcomdef.h>
#include<arcsoft_face_sdk.h>
#include<merror.h>
#include<SystemConf.h>
namespace Ui {
class ActiveMainWindow;
}


class Q_DECL_EXPORT ActiveMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ActiveMainWindow(TeacherInfo teacher,QWidget *parent=nullptr);
    static bool HostIsActive();//验证本机是否认证
    static QMap<bool,QString> HostIsActiveLab();//验证本机是否认证
    ~ActiveMainWindow();
    void  selectLabInfo();
signals:
    void GetActiveInfoFinished(QString activeFileMd5);
    //void static  CurrentActiveHostMapLabId(QString);
public slots:
    bool activeFileIsExict();//认证文件是否存在
    void ActiveDevice();//认证本机
    void onComboBoxChanged();//实验室索引改变
    bool hostIsActive();//本机是否验证过
    void calcHostActive();//取消本机
private:
    bool InitSystemConf();//初始化系统配置
    void InitSql();//初始化数据库
    bool IsEditInfoEmpty();
private:
    Ui::ActiveMainWindow *ui;
    QString m_activeFileMd5;//计算认证文件Md5码
    TeacherInfo m_teacherInfo;
    int currentLabId;//当前实验室ID
    QSqlDatabase m_db;
    QString m_AvticeFileName;//认证文件名称
};

#endif // ACTIVEMAINWINDOW_H
