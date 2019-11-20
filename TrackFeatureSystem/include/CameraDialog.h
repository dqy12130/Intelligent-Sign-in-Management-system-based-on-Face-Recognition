#ifndef CAMERADIALOG_H
#define CAMERADIALOG_H

#include <QDialog>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include<QMessageBox>
namespace Ui {
class  CameraDialog;
}


class  Q_DECL_EXPORT CameraDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CameraDialog(QWidget *parent = nullptr);
    ~CameraDialog();

signals:
    void CaptureFinished( QMap<QString,QImage> );
     void SendStatusMessage(QString message);//向主界面发送状态信息
public:
    //打开取像框
    static QImage openCameraDialog();
    void StartCapture();//开始拍照
private:
    Ui::CameraDialog *ui;
    //系统摄像头
    QCamera *camera;
    //摄像头取景部件
    QCameraViewfinder *cameraViewfinder;
    //截图部件
    QCameraImageCapture *cameraImageCapture;
    //初始化
    void init();
    //存储图片
    QMap<QString,QImage> m_IdImageMap;
    static QImage image;


private slots:
    //确定按钮的单击事件
    void onOkClick(bool);
    //取消按钮的单击使劲
    void onCancelClick(bool);
    //存储图片
    void onCameraCaptured(int id,QImage image);
private:

};

#endif // CAMERADIALOG_H
