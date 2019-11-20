#ifndef INITTRACK_H
#define INITTRACK_H

#include <QDialog>
#include<QMessageBox>
#include<facerecognitionservice.h>
#include<QFileDialog>
#include<QFile>
#include<QByteArray>

namespace Ui {
class InitTrack;
}

class Q_DECL_EXPORT InitTrack : public QDialog
{
    Q_OBJECT

public:
    bool ExeStatus();
    explicit InitTrack(QWidget *parent=nullptr);
    ~InitTrack();

    static bool AcviteSystem();
private slots:
    void on_OkButton_clicked();

    void on_pushButton_2_clicked();
    void LoadActiveFile();
    void SaveActiveFile();
private:
    void Init();
private:
    Ui::InitTrack *ui;
    bool m_exeStatus;
    QByteArray *m_fileArray;
    static bool ActiveStatus;
};

#endif // INITTRACK_H
