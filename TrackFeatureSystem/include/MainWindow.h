#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include<QFileDialog>
#include<QStringList>
#include<QFileInfo>
#include<QDateTime>
#include<InitTrack.h>
#include<QDateTime>
#include<QIcon>
#include<TrackFile.h>
#include<CameraDialog.h>

namespace Ui {
class MainWindow;
}

class Q_DECL_EXPORT MainWindow : public QWidget
{
    Q_OBJECT

public:
    bool InitSystem();
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void ChooesFilesFinished(QStringList);
    void LoadFeatures(QStringList);
public slots:

    void OpenCamera();//打开摄像头进行拍照
    void SetFileTree();//设置训练文件
    void ExFeaturesss();//计算特征值
    void  LoadFeature();//加载特征值
    void SetMessageToUi(QString);
    void SaveLogFile();//保存日志文件
private:
    Ui::MainWindow *ui;
    QStringList m_fileList;
    // QFileInfoList m_AllFileList;
    TrackFile *m_Trck;
    CameraDialog *m_camerDialog;

};

#endif // MAINWINDOW_H
