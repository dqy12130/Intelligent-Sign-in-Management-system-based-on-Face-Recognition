#ifndef FACERECOGNITIONSERVICE_H
#define FACERECOGNITIONSERVICE_H
#include <QObject>
#include<faceincludefile.h>
#include<facedefine.h>
#include<QList>
#include<QThread>
#include<QThreadPool>
#include<QRunnable>
#include<QPixmap>
#include<ImageFromat.h>
class ImageFromat;//图片格式转换类

namespace  Face{
class FaceInitInterface;//初始化引擎接口
class InitFaceEngine;//人脸检测引擎
class  FaceDection;//人脸检测
class FaceCompere;
class FaceRecognitionService;//人脸识别服务
};

//using namespace FaceRecognition;

/*
 * 引擎接口初始化，不仅仅可用于人脸识别，还可用于年龄检测，性别检测，活体检测等
*/
class Q_DECL_EXPORT InitInterface
{
public:
    virtual MRESULT InitEngine(QString appId,QString appKey)=0;//初始化引擎接口
    virtual bool IsActivationEngineSucess()=0;
    InitInterface(){};
    virtual ~InitInterface(){};//虚析构函数
};

class Q_DECL_EXPORT InitFaceEngine:public InitInterface
{

public:

    static MRESULT  CreatActivationFile(QString appId, QString appKey);
    static MHandle GetFaceEngineInstance(QString appId, QString appKey, MInt32 mask);//引擎单例
    static MRESULT ReleseFaceEngine(MHandle);//释放引擎
    static MHandle InitEngine(MHandle handle,MInt32 mask);//初始引擎

    MRESULT InitByObject(InitFaceEngine&);
    MRESULT InitByObject(InitFaceEngine&,QString appId,QString appKey);
    MRESULT InitByIdKey(QString,QString,MInt32,MHandle&,ASF_ActiveFileInfo,FaceDetectMode);//静态函数
    MRESULT ActivationEngine(QString appId,QString appKey);//返回激活状态,实际调用了Activation函数
    virtual MRESULT InitEngine(QString appId,QString appKey)override;
    virtual bool IsActivationEngineSucess()override
    {
        return Enginesucess();
    }
    InitFaceEngine();
    InitFaceEngine(QString AppID,QString AppKey);
    ~InitFaceEngine();
public:
    QString GetCurrentAppID() const;
    QString GetCurrentAppKey() const;
    void setAppID(const QString &AppID);
    void setAppKey(const QString &AppKey);
    MRECT SetMask(MInt32 mask);
    MInt32 GetMask();
private:
    MRESULT Activation();//激活引擎
    bool Enginesucess() const;
    MHandle m_Handle;//句柄

private:

    QString m_AppID;
    QString m_AppKey;
    MRESULT m_EngineStatus;//当前引擎状态码

    MInt32 m_mask;//功能集
    bool m_enginesucess;//激活是否成功
};

class Q_DECL_EXPORT FaceDection : public QObject
{
    Q_OBJECT
public:

    FaceDection();
    FaceDection(InitFaceEngine);
    void run();
    void FaceDectionTest();
    void setFaceDectionObject(const cv::Mat &faceDectionObject);//人脸检测结构
    void setFaceDectionObject(const IplImage &faceDectionObject);//人脸检测结构
    MRESULT DectionResult();//返回人脸检测结果
    void CutIplImage(IplImage* src, IplImage* dst, int x, int y);//图片剪切
    QByteArray FaceFeatureToQByteArray(FaceFeature);
    FaceFeature QByteArrayToFaceFeature(QByteArray);
    void SaveFaceFeature(QString filename,QByteArray buffer,QIODevice::OpenMode);
    void SaveFaceFeature(QString filename,FaceFeature feature,QIODevice::OpenMode);
    bool FreeFeature(FaceFeature);//释放Feature的内存区域
    ~FaceDection();
signals:
    void SendMat2CamerThread(cv::Mat);
public slots:
    void Dection(cv::Mat);

public:
    /* 计算特征值 */
    FaceFeature ExFeature(QPixmap&);
    FaceFeature ExFeature(cv::Mat&);
    FaceFeature ExFeature(IplImage&);
    FaceFeature ExFeatureBase(IplImage&);
private:


    ASF_SingleFaceInfo GetSingleFaceInfo(ASF_SingleFaceInfo&);//得到单人脸信息
    cv::Mat GetFaceRectImage(cv::Mat &src,ASF_SingleFaceInfo singleFaceInfo);//人脸检测用
    cv::Mat GetFaceROI(cv::Mat &src,ASF_SingleFaceInfo singleFaceInfo);//得到人脸区域
    IplImage GetFaceROI(IplImage img,ASF_SingleFaceInfo singleFaceInfo);//得到人脸区域
private:

    InitFaceEngine *m_FaceEngine;//引擎
    cv::Mat m_faceDectionObject;//图片
    MRESULT m_DectionResult;//返回代码
    bool m_enginesucess;//引擎激活结果
    ASF_MultiFaceInfo m_detectedFaces;//多人脸
    ASF_SingleFaceInfo m_SingleDetectedFaces;//单人脸
    MHandle FaceDectionHandle;
    QMultiMap<QString,MHandle> FaceEngineMap;//引擎管理池,通过名称来进行引擎池的管理
    long long DectionSuccessNumber;
    QList<FaceFeature> m_faceFeatureList;//特征值列表

    QMultiMap<QString,FaceFeature> FaceFeatureNumberMap;//设定检测人和检测到的特征值相关联

    friend class FaceCompere;//友元
};

class Q_DECL_EXPORT  FaceCompere:public QObject//人脸比对
{
    Q_OBJECT
public:
    explicit  FaceCompere(QObject *parent);
    explicit  FaceCompere();
    ~FaceCompere();
    static bool FaceFeatureIsActive(const FaceFeature&);//判断特征值是否有效;
    double FaceCompereResult( FaceFeature &feature1, FaceFeature & feature2);//特征值比对
    double FaceCompereResult( const QByteArray &feature1, const QByteArray & feature2);//特征值比对
    QMap<QString,double> FindFaces( QMultiMap<QString,FaceFeature> features,FaceFeature testFeature);//人脸比对
    QString FindPerson( QMultiMap<QString,FaceFeature> features,FaceFeature testFeature);//人脸比对



    FaceFeature GetFaceFeatureFromQFile(QString fileName);//读取特征值文件
    void SaveFaceTeatureToFile(QString fileName,FaceFeature);

    MHandle GetFaceCompereHandle();

    void Test();
private:
    void JoinWorkQueue(QString,FaceFeature faceFeature);//加入工作队列
    void JoinWorkQueue(QMultiMap<QString,FaceFeature> features);//加入工作队列
    void RemoveWorkQueue(QString ID);//从工作队列中移除
    void RemoveWorkQueue(QMultiMap<QString,FaceFeature>  IdFeatureMap);//从工作队列中移除
private:
    void InitEngine();//初始化引擎

    FaceDection m_faceDection;//人脸检测类
    MHandle m_FaceCompereHandle;//人脸比对引擎

    QMultiMap<QString,FaceFeature> FaceFeatureNumberMap;//待检测的特征值
    QMap<QString,double>  faceSimlar;//相似度
    friend class FaceRecognitionService;//友元
};

//人脸识别服务类
class Q_DECL_EXPORT FaceRecognitionService : public QObject
{
    Q_OBJECT
public:

    explicit FaceRecognitionService();
    ~FaceRecognitionService();
    QMap<QString,double> DoWork( const QMultiMap<QString,FaceFeature> Features,const FaceFeature feature);
    QString DoWork(const FaceFeature);

    QList<InitFaceEngine>  GetFaceEngineList();
    void run();
    // void JoinFaceRecognitionQueue();
    void JoinFaceRecognitionQueue( const QString,const FaceFeature faceFeature);//加入工作队列
    void JoinFaceRecognitionQueue(const QMultiMap<QString,FaceFeature> features);//加入工作队列
    void RemoveFaceRecognitionQueue(QString ID);//从工作队列中移除
    void RemoveFaceRecognitionQueue(QMultiMap<QString,FaceFeature>  IdFeatureMap);//从工作队列中移除
signals:
    //void SearchFaceFinished(QMap<QString,double>);
    void SearchFaceFinished(QString ID);
    void SearchUserID(QString);//待检索的用户ID
public slots:
    void ComereFromFrame(const FaceFeature);
private:
    QList<InitFaceEngine> m_FaceEngineList;
    FaceCompere m_faceCompere;
    MHandle m_faceRecogintionHandle;//识别引擎,来源于FaceCompere类

};

#endif // FACERECOGNITIONSERVICE_H
