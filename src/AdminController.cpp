/*****************************************************************************
*  Intelligent Sign-in management system based on face recognition sourse    *
*  file.                                                                     *
*                                                                            *
*  Copyright (C) 2019       Qiyao.Dai     2650822367@qq.com                  *
*                           Zixuan.Zhao   zxZhao1998@gmail.com               *
*                                                                            *
*  This file is part of Face.                                                *
*                                                                            *
*  @file     AdminController.cpp                                             *
*  @brief    Admin面板的Controller层实现                                       *
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
*  2019/11/12 | 1.0.0.1   | Zixuan.Zhao    | Update function                 *
*             |           |                | 'AdminController'               *
*             |           |                | Add function 'selectDeviceInfo' *
*----------------------------------------------------------------------------*
*  2019/11/13 | 1.0.0.1   | Zixuan.Zhao    | Update function                 *
*             |           |                | 'AdminController'               *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#include "AdminController.h"
#include "ui_AdminWidget.h"
#include "StudentInfo.h"
#include "TeacherInfo.h"
#include "LogInController.h"
#include "AddController.h"
#include "UpdateController.h"
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>

AdminController::AdminController(TeacherInfo teacherInfo, QVector<LabInfo> labs,QWidget* parent):AdminWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);

    //保存教师信息
    this->teacherInfo=teacherInfo;
    //保存管辖的实验室信息
    this->labs=labs;
    //初始化Service层
    adminService=new AdminService();

    //Admin面板初始化
    //设置窗口标题
    setWindowTitle("欢迎, "+teacherInfo.getName()+" 老师!");

    //填充LabCmb
    for(LabInfo labInfo:labs)
    {
        ui->labCmb->addItem(labInfo.getName());
        ui->todayLabComboBox->addItem(labInfo.getName());
        ui->historyComboBox->addItem(labInfo.getName());
        ui->deviceLabComboBox->addItem(labInfo.getName());
    }

}
AdminController::AdminController(TeacherInfo teacherInfo)//保证接口稳定
{
    setAttribute(Qt::WA_DeleteOnClose);

    //保存教师信息
    this->teacherInfo=teacherInfo;
    //开启管理员服务
    adminService=new AdminService();

    //管理员面板初始化
    //设置窗口标题
    setWindowTitle("欢迎, "+teacherInfo.getName()+" 老师!");

    //填充管理页面的LabCmb
    ui->labCmb->addItems(teacherInfo.getLabs().values());

    for(LabInfo labInfo:labs)
    {
        ui->labCmb->addItem(labInfo.getName());
        ui->todayLabComboBox->addItem(labInfo.getName());
        ui->historyComboBox->addItem(labInfo.getName());
        ui->deviceLabComboBox->addItem(labInfo.getName());
    }
}
AdminController::~AdminController()
{
    delete adminService;
}

/**
 * @brief 显示学生的照片在photoView
 */
void AdminController::showPhoto()
{
    ui->pictureView->clear();
    //获取当前选中行
    int row=ui->infoTableWidget->currentRow();
    //如果行未越界
    if(row>=0&&row<currentStuInfo.length())
    {
        //获取当前行对应的学生信息
        StudentInfo stuInfo=currentStuInfo.at(row);
        if(stuInfo.getFaceImage().isEmpty()==false)
        {
            QPixmap pixmap;
            pixmap.loadFromData(stuInfo.getFaceImage());
            pixmap.scaled(ui->pictureView->size(),Qt::KeepAspectRatio);
            ui->pictureView->setPixmap(pixmap);
        }
    }
}

/**
 * @brief 注销（跳转到LogIn面板）
 */
void AdminController::showLogInWidget()
{
    this->close();
    LogInController* logInController=new LogInController();
    logInController->show();
}
/**
 * @brief 弹出用来添加学生的Dialog
 */
void AdminController::showAddDialog()
{
    AddController* addController=new AddController(currentUserManagePageLabId,this);
    addController->show();
}
/**
 * @brief 删除已选学生，支持多选
 */
void AdminController::deleteStuInfo()
{
    //存放所有待删除学生的学号
    QVector<QString> studentsId;
    //获取所有选中的item
    QList<QTableWidgetItem*> itemList=ui->infoTableWidget->selectedItems();
    //获取表格列数
    int columCount=ui->infoTableWidget->columnCount();
    //获取所有选中的学号
    for(int i=0;i<itemList.length();i+=columCount)
    {
        studentsId.push_back(itemList.at(i)->text());
    }
    //交付给service层
    adminService->deletStuInfo(studentsId);
    //刷新
    selectStuInfo();
    selectTodaySignInfo();
    selectHistorySignInfo();
}

/**
 * @brief 弹出用来修改学生信息的Dialog
 */
void AdminController::showUpdateDialog()
{
    //获取所管辖的所有实验室id-name
    QMap<int,QString> labMap;
    for(LabInfo labInfo:labs)
    {
        labMap.insert(labInfo.getId(),labInfo.getName());
    }
    //获取待修改的学生信息
    StudentInfo stuInfo=currentStuInfo[ui->infoTableWidget->currentRow()];
    UpdateController *updateController=new UpdateController(labMap,stuInfo,this);
    updateController->show();
}
/**
 * @brief 初始化checkbox
 */
void AdminController::initCheckBox()
{
    //如果当前老师未分配管理实验室，则退出
    if(ui->deviceLabComboBox->currentIndex()<0) return;

    if(adminService->initCheckBox(currentDevicesManagePageLabId)==true)
    {
        ui->boundCheckBox->setCheckState(Qt::Checked);
    }
    else
    {
        ui->boundCheckBox->setCheckState(Qt::Unchecked);
    }
}

void AdminController::updateApproveState()
{
    int state=ui->boundCheckBox->checkState();
    adminService->updateApproveState(currentDevicesManagePageLabId,state);
}

/**
 * @brief 刷新userManagePage中infoTableWidget的内容,用于展示当前所选实验室中
 * 所有学生的信息，便于进一步增删改查
 */
void AdminController::selectStuInfo()
{
    //初始化tablewidget
    ui->infoTableWidget->clearContents();
    ui->infoTableWidget->setRowCount(0);
    ui->pictureView->clear();

    //如果当前老师未分配管理实验室，则不初始化table
    if(ui->labCmb->currentIndex()<0) return;

    //获取当前选中的实验室id
    currentUserManagePageLabId=labs.at(ui->labCmb->currentIndex()).getId();
    //获取此实验室所有学生的信息
    currentStuInfo=adminService->selectStuInfo(currentUserManagePageLabId);

    //填充
    for(int i=0;i<currentStuInfo.length();i++)
    {
        //表格加一行
        ui->infoTableWidget->setRowCount(ui->infoTableWidget->rowCount()+1);

        ui->infoTableWidget->setItem(i,0,new QTableWidgetItem(currentStuInfo.at(i).getStudentId()));
        ui->infoTableWidget->setItem(i,1,new QTableWidgetItem(currentStuInfo.at(i).getName()));
        ui->infoTableWidget->setItem(i,2,new QTableWidgetItem(currentStuInfo.at(i).getSex()));
        ui->infoTableWidget->setItem(i,3,new QTableWidgetItem(currentStuInfo.at(i).getGrade()));
        ui->infoTableWidget->setItem(i,4,new QTableWidgetItem(currentStuInfo.at(i).getDepartment()));
        ui->infoTableWidget->setItem(i,5,new QTableWidgetItem(currentStuInfo.at(i).getMajor()));
        ui->infoTableWidget->setItem(i,6,new QTableWidgetItem(currentStuInfo.at(i).getClasses()));
        ui->infoTableWidget->setItem(i,7,new QTableWidgetItem(currentStuInfo.at(i).getEmail()));
        ui->infoTableWidget->setItem(i,8,new QTableWidgetItem(currentStuInfo.at(i).getTelephone()));

        //居中显示
        for(int j=0;j<ui->infoTableWidget->columnCount();j++)
        {
            ui->infoTableWidget->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
    }
}
/**
 * @brief 刷新attendancePage中todaySignInfoTableWidget的内容，显示当天签到
 * 情况排名
 */
void AdminController::selectTodaySignInfo()
{
    //初始化tableWidget
    ui->todayRankTableWidget->clearContents();
    ui->todayRankTableWidget->setRowCount(0);

    //如果当前老师未分配管理实验室，则退出
    if(ui->todayLabComboBox->currentIndex()<0) return;

    //获取要查看的今日签到情况的实验室id
    int labIdForToday=labs.at(ui->todayLabComboBox->currentIndex()).getId();
    //获取此实验室学生的今日的签到信息
    QVector<TodaySignInfo> todaySignInfoAll=adminService->selectTodaySignInfo(labIdForToday);
    //TODO:显示
    for(int i=0;i<todaySignInfoAll.length();i++)
    {
        //增加一行
        ui->todayRankTableWidget->setRowCount(ui->todayRankTableWidget->rowCount()+1);

        //如果时间为空，表示未签到
        if(todaySignInfoAll.at(i).getSignInDateTime().isNull())
        {
            ui->todayRankTableWidget->setItem(i,0,new QTableWidgetItem("-"));
            ui->todayRankTableWidget->setItem(i,1,new QTableWidgetItem("-"));
        }else
        {
            ui->todayRankTableWidget->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
            ui->todayRankTableWidget->setItem(i,1,new QTableWidgetItem(todaySignInfoAll.at(i).getSignInDateTime().toString("hh:mm:ss")));
        }
        ui->todayRankTableWidget->setItem(i,2,new QTableWidgetItem(todaySignInfoAll.at(i).getStuInfo().getStudentId()));
        ui->todayRankTableWidget->setItem(i,3,new QTableWidgetItem(todaySignInfoAll.at(i).getStuInfo().getName()));
        ui->todayRankTableWidget->setItem(i,4,new QTableWidgetItem(todaySignInfoAll.at(i).getStuInfo().getSex()));
        ui->todayRankTableWidget->setItem(i,5,new QTableWidgetItem(todaySignInfoAll.at(i).getStuInfo().getDepartment()));
        ui->todayRankTableWidget->setItem(i,6,new QTableWidgetItem(todaySignInfoAll.at(i).getStuInfo().getGrade()));
        ui->todayRankTableWidget->setItem(i,7,new QTableWidgetItem(todaySignInfoAll.at(i).getStuInfo().getMajor()));
        ui->todayRankTableWidget->setItem(i,8,new QTableWidgetItem(todaySignInfoAll.at(i).getStuInfo().getClasses()+"班"));

        //居中显示
        for(int j=0;j<ui->todayRankTableWidget->columnCount();j++)
        {
            ui->todayRankTableWidget->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
    }
}
/**
 * @brief 刷新attendancePage中historySignInfoTableWidget的内容，显示当前所选
 * 时间区间内的签到排名
 */
void AdminController::selectHistorySignInfo()
{
    //初始化tableWidget
    ui->historyRankTableWidget->clearContents();
    ui->historyRankTableWidget->setRowCount(0);

    //如果当前老师未分配管理实验室，则退出
    if(ui->historyComboBox->currentIndex()<0) return;
    //获取要查看的今日签到情况的实验室id
    int labIdForHistory=labs.at(ui->historyComboBox->currentIndex()).getId();
    //获取时间区间
    QDateTime beginDateTime=ui->beginDateEdit->dateTime();
    QDateTime endDateTime=ui->endDateEdit->dateTime();
    //swap
    if(beginDateTime>endDateTime)
    {
        QDateTime temp=beginDateTime;
        beginDateTime=endDateTime;
        endDateTime=temp;
    }
    QVector<HistorySignInfo> historySignInfoAll=adminService->selectHistorySignInfo(beginDateTime,endDateTime,labIdForHistory);
    //TODO:show
    //qDebug()<<historySignInfoAll.length();
    for(int i=0;i<historySignInfoAll.length();i++)
    {
        //增加一行
        ui->historyRankTableWidget->setRowCount(ui->historyRankTableWidget->rowCount()+1);

        //如果签到次数为0
        if(historySignInfoAll.at(i).getSignInTimes()==0)
        {
            ui->historyRankTableWidget->setItem(i,0,new QTableWidgetItem("-"));
        }
        else
        {
            ui->historyRankTableWidget->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        }
        QString text=QString::number(historySignInfoAll.at(i).getSignInTimes())+"/"+QString::number(historySignInfoAll.at(i).getUnSignInTimes())+"/"+QString::number(historySignInfoAll.at(i).getRate()*100,'f',2)+"%";
        ui->historyRankTableWidget->setItem(i,1,new QTableWidgetItem(text));
        ui->historyRankTableWidget->setItem(i,2,new QTableWidgetItem(historySignInfoAll.at(i).getStuInfo().getStudentId()));
        ui->historyRankTableWidget->setItem(i,3,new QTableWidgetItem(historySignInfoAll.at(i).getStuInfo().getName()));
        ui->historyRankTableWidget->setItem(i,4,new QTableWidgetItem(historySignInfoAll.at(i).getStuInfo().getSex()));
        ui->historyRankTableWidget->setItem(i,5,new QTableWidgetItem(historySignInfoAll.at(i).getStuInfo().getDepartment()));
        ui->historyRankTableWidget->setItem(i,6,new QTableWidgetItem(historySignInfoAll.at(i).getStuInfo().getGrade()));
        ui->historyRankTableWidget->setItem(i,7,new QTableWidgetItem(historySignInfoAll.at(i).getStuInfo().getMajor()+historySignInfoAll.at(i).getStuInfo().getClasses()+"班"));

        //居中显示
        for(int j=0;j<ui->historyRankTableWidget->columnCount();j++)
        {
            ui->historyRankTableWidget->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
    }
}

/**
 * @brief 刷新devicePage中deviceInfotableWidget的内容，显示当前实验室中的设备信息
 */
void AdminController::selectDeviceInfo()
{
    //初始化tableWidget
    ui->deviceInfoTableWidget->clearContents();
    ui->deviceInfoTableWidget->setRowCount(0);

    //如果当前老师未分配管理实验室，则退出
    if(ui->deviceLabComboBox->currentIndex()<0) return;
    //获取当前选中的实验室id
    currentDevicesManagePageLabId=labs.at(ui->deviceLabComboBox->currentIndex()).getId();
    //获取当前实验室的所有设备
    currentDevInfo=adminService->selectDevicesInfo(currentDevicesManagePageLabId);
    //show
    for(int i=0;i<currentDevInfo.length();i++)
    {
        //加一行
        ui->deviceInfoTableWidget->setRowCount(ui->deviceInfoTableWidget->rowCount()+1);
        //添加item
        ui->deviceInfoTableWidget->setItem(i,0,new QTableWidgetItem(currentDevInfo.at(i).getName()));
        ui->deviceInfoTableWidget->setItem(i,1,new QTableWidgetItem(currentDevInfo.at(i).getMax()));
        ui->deviceInfoTableWidget->setItem(i,2,new QTableWidgetItem(currentDevInfo.at(i).getLoan()));
        ui->deviceInfoTableWidget->setItem(i,3,new QTableWidgetItem(currentDevInfo.at(i).getDemage()));
        ui->deviceInfoTableWidget->setItem(i,4,new QTableWidgetItem(currentDevInfo.at(i).getRemain()));

        //居中显示
        for(int j=0;j<ui->deviceInfoTableWidget->columnCount();j++)
        {
            ui->deviceInfoTableWidget->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
    }
}
/**
 * @brief 刷新devicePage中deviceLogInfo的内容，根据实验室id和datetime显示当前实验室中的当天所有的设备日志
 */
void AdminController::selectAllDeviceLogInfo()
{
    //初始化listWidget
    ui->deviceLogListWidget->clear();
    //如果当前老师未分配管理实验室，则退出
    if(ui->deviceLabComboBox->currentIndex()<0) return;
    //获取当前选中的实验室id
    currentDevicesManagePageLabId=labs.at(ui->deviceLabComboBox->currentIndex()).getId();
    //获取当前日期
    QDateTime currentDateTime=ui->deviceLogDateEdit->dateTime();
    //获取当前选中的实验室当前日期的所有日志
    currentLogInfo=adminService->selectLogsInfo(currentDevicesManagePageLabId,currentDateTime);
    //填充logInfoListWidget
    for(int i=0;i<currentLogInfo.length();i++)
    {
        ui->deviceLogListWidget->addItem(currentLogInfo.at(i).getDate().toString("hh:mm:ss")+"\t"+currentLogInfo.at(i).getDeviceName()+currentLogInfo.at(i).getContent());
    }
}

