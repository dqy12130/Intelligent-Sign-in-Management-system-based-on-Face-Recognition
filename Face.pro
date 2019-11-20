#-------------------------------------------------
#
# Project created by QtCreator 2019-09-27T16:26:21
#
#-------------------------------------------------

QT       += core gui sql  concurrent
QT       += multimedia
QT       += multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Face
TEMPLATE = app

win32{
#OpenCV相关库
INCLUDEPATH += $$PWD\lib\OpenCV3.3.1\include\
INCLUDEPATH += $$PWD\lib\OpenCV3.3.1\include\opencv
INCLUDEPATH += $$PWD\lib\OpenCV3.3.1\include\opencv2
LIBS += $$PWD\lib\OpenCV3.3.1\bin\libopencv_*.dll

#ArcSoft相关库
INCLUDEPATH +=$$PWD/lib/arc/inc
LIBS += $$PWD/lib/arc/lib\Win32/libarcsoft_face*.dll
LIBS += $$PWD/lib/arc/lib/Win32/libarcsoft_face*.lib
}


SOURCES += main.cpp\
    LogInDao.cpp \
    LogInService.cpp \
    AdminWidget.cpp \
    LogInWidget.cpp \
    MainWidget.cpp \
    SignInWidget.cpp \
    AdminController.cpp \
    LogInController.cpp \
    MainController.cpp \
    SignInController.cpp \
    MySqlUtils.cpp \
    StringUtils.cpp \
    AdminService.cpp \
    AdminDao.cpp \
    SignInService.cpp \
    SignInDao.cpp \
    StudentInfo.cpp \
    TeacherInfo.cpp \
    AddController.cpp \
    AddDao.cpp \
    AddDialog.cpp \
    AddService.cpp \
    UpdateDialog.cpp \
    UpdateController.cpp \
    UpdateService.cpp \
    UpdateDao.cpp \
    ArcSoftFaceUtils.cpp \
    MainService.cpp \
    MainDao.cpp \
    NetUtils.cpp \
    CameraDialog.cpp \
    TodaySignInfo.cpp \
    HistorySignInfo.cpp \
    DevicesInfo.cpp \
    LabInfo.cpp \
    LogInfo.cpp \
    verificationcodelabel.cpp \
    ImageFromat.cpp \
    SystemConf.cpp


HEADERS  += \
    LogInDao.h \
    LogInService.h \
    AdminWidget.h \
    LogInWidget.h \
    MainWidget.h \
    SignInWidget.h \
    AdminController.h \
    LogInController.h \
    MainController.h \
    SignInController.h \
    MySqlUtils.h \
    StringUtils.h \
    AdminService.h \
    AdminDao.h \
    SignInService.h \
    SignInDao.h \
    StudentInfo.h \
    TeacherInfo.h \
    AddController.h \
    AddDao.h \
    AddDialog.h \
    AddService.h \
    UpdateDialog.h \
    UpdateController.h \
    UpdateService.h \
    UpdateDao.h \
    ArcSoftFaceUtils.h \
    MainService.h \
    MainDao.h \
    NetUtils.h \
    CameraDialog.h \
    TodaySignInfo.h \
    HistorySignInfo.h \
    DevicesInfo.h \
    LabInfo.h \
    LogInfo.h \
    verificationcodelabel.h \
    ImageFromat.h \
    SystemConf.h


FORMS    += \
    AdminWidget.ui \
    MainWidget.ui \
    SignInWidget.ui \
    AddDialog.ui \
    UpdateDialog.ui \
    CameraDialog.ui \
    LogInWidget.ui




win32: LIBS += -L$$PWD/lib/TrackFeatureSystem/lib/ -lTrackFeatureSystem

INCLUDEPATH += $$PWD/lib/TrackFeatureSystem/include
DEPENDPATH += $$PWD/lib/TrackFeatureSystem/include


win32: LIBS += -L$$PWD/lib/HostActiveSystem/lib/ -lHostActiveSystem
INCLUDEPATH += $$PWD/lib/HostActiveSystem/include
DEPENDPATH += $$PWD/lib/HostActiveSystem/include


win32: LIBS += -L$$PWD/lib/FaceLogin/lib/ -lFaceLogin
INCLUDEPATH += $$PWD/lib/FaceLogin/include
DEPENDPATH += $$PWD/lib/FaceLogin/include












