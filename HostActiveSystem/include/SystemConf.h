#ifndef SYSTEMCONF_H
#define SYSTEMCONF_H
#include<QSettings>
#include<QFile>
#include<QTextCodec>
#include<QByteArray>
class SystemConf//:public QSettings
{
public:
    SystemConf();
    SystemConf( QString confFile);
    void SetConfFile(QString confFile);
    QString  GetConfFileName();
    static QMap<QString,QString> GetConf();//得到配置文件的配置信息
    static QMap<QString,QString> GetActiveFileConf();//得到激活配置文件的配置信息
    static void SetConf( QMap<QString,QString>);//设置配置信息
    static QByteArray Encryption(QByteArray,int enCryptionLevel=10);//加密,参数二是加密次数
    static QByteArray Decryption(QByteArray,int deCryptionLevel=10);//解密，参数二是解密次数
    static QString Encryption(QString,int enCryptionLevel=10);//加密,参数二是加密次数
    static QString Decryption(QString,int deCryptionLevel=10);//解密，参数二是解密次数
private:
    QMap<QString,QString> SyncFile(  QString fileName);
    QSettings m_systemSetting;
    QString m_confFile;
    QMap<QString,QString> m_settingMap;
};

#endif // SYSTEMCONF_H
