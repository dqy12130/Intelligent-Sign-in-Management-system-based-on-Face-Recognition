#ifndef FaceLoginWidget_H
#define FaceLoginWidget_H

#include <QWidget>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QTimer>

namespace Ui {
class FaceLoginWidget;
}

class FaceLoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FaceLoginWidget(QWidget *parent = nullptr);
    ~FaceLoginWidget();
     Ui::FaceLoginWidget *ui;
protected:

    //跳转到主界面
    virtual void showMainWidget()=0;
    //处理捕获的图片
    virtual void doFaceWork(QImage image)=0;
private:
    //系统摄像头
    QCamera *camera;
    //摄像头取景部件
    QCameraViewfinder *cameraViewfinder;
    //截图部件
    QCameraImageCapture *cameraImageCapture;
    //定时器
    QTimer* timer;

    //初始化
    void init();

private slots:
    //返回主界面
    void onBackClick(bool);
    //摄像头捕获
    void onCameraCaptured(int id,QImage image);
    //定时器
    void onTimerOuted();
};

#endif // FaceLoginWidget_H
