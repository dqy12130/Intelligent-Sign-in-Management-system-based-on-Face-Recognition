#ifndef GETTRACKFILE_H
#define GETTRACKFILE_H

#include <QObject>
#include<QThread>
#include<QDir>
#include<QFileDialog>
#include<QFile>
#include<QFileInfoList>
#include<faceincludefile.h>
#include<facerecognitionservice.h>
#include<QTime>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<QtConcurrent>
#include"MySqlUtils.h"

class Q_DECL_EXPORT TrackFile : public QObject
{
    Q_OBJECT
public:
    explicit TrackFile();
     ~TrackFile();
signals:
    void SendStatusMessage(QString message);
public slots:
    void GetAllFilesInfo(QStringList);
    void TrackFeature();
    void SaveFiles();
    void LoadFeatures(QStringList);
    void SetFeatureToDb();
    void LoadFeatureFromDB();

    void SetTrackWork(QMap<QString,QImage> IdImageMap);
    void SetSaceImaheFlag(bool);
private:
    void SaveFeatureToDb(QSqlDatabase,QString ,FaceFeature&);
    FaceFeature QByteArrayToFaceFeature(QByteArray &featureBuffer);

    void DoWork();
    FaceCompere m_faceTrack;
    FaceDection *m_faceDection;
    QStringList m_TrackFiles;
    QMap<QString,FaceFeature> m_features;
    QSqlDatabase m_db;

    bool SaveImageFlag;
};

#endif // GETTRACKFILE_H
