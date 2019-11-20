#ifndef FaceLoginController_H
#define FaceLoginController_H

#include "FaceLoginWidget.h"
#include "FaceLoginService.h"
#include <QThread>
#include<TeacherInfo.h>
#include<StudentInfo.h>
class Q_DECL_EXPORT FaceLoginController : public FaceLoginWidget
{
    Q_OBJECT
public:
    //FaceLoginController(QWidget *parent=nullptr);
    //重写
     FaceLoginController(QWidget *parent= nullptr,QString currentActiveLab="0");
    ~FaceLoginController();
     QString currentActiveLab() const;

protected:
     //跳转到主界面
     void showMainWidget();
    //处理捕获的图片
    void doFaceWork(QImage image);
private:
    //签到服务
    FaceLoginService *m_faceLoginService;
    //签到服务运行在的线程
    QThread* m_faceLoginServiceThread;
    QString m_currentActiveLab;
signals:
    //做图片处理的信号
    void doWork(QImage image);
    void ReginistFinished(QString teacherName);
    void FaceLoginSuccess(QString teacherName);//登陆成功
    void FaceLoginFinished(bool);
public slots:
    //显示比对结果的槽
    //void showResult(float result,StudentInfo stuInfo);

    void showResult(float result,TeacherInfo stuInfo);
     void StartFaceLoginServiceThread();

};

#endif // FaceLoginController_H
