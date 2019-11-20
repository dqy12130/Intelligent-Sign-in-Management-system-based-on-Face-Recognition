#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<lib/HostActiveSystem/include/ActiveMainWindow.h>
#include<QMessageBox>
#include<FaceLoginController.h>
#include<QtConcurrent>
#include<QMutex>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static  bool  FaceLoginResult(FaceLoginController*);
signals:

public slots:
    void onFaceLoginButtonClicked();

private:
    Ui::MainWindow *ui;
    FaceLoginController *m_sigin;
};




class Q_DECL_EXPORT  FaceLogin : public QObject
{
    Q_OBJECT

public:
    explicit FaceLogin(QWidget *parent = nullptr);
    ~FaceLogin();
    static  bool  FaceLoginResult(FaceLoginController*);
   signals:
     void Finished(bool);
};




#endif // MAINWINDOW_H
