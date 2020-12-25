//功能：启动录音设备，对数据编码上传网络，调用百度语音识别ASR，获取识别文本
#ifndef ASR_H
#define ASR_H

#include <QMainWindow>
#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>
#include<QAudioInput>
#include<QMediaPlayer>
#include<QMessageBox>
#include<QTime>
#include<QSettings>
#include<QKeyEvent>
#include<QString>
#include<QUrl>

class ASR : public QMainWindow
{
    Q_OBJECT

public:
    int isStop=1;
    //请勿将此处的API_KEY和Secret_Key用于其他地方
    const QString API_KEY="uHHqzHHmgQvDnsPB8N9lchUh";
    const QString Secret_Key="VGwawk0hDtzxlZfeT6XQ8Pv5gVxubUB8";
    QString Access_Token="25.94f9865af085f7c1c78c93ea0841a10b.315360000.1908864799.282335-20666592";
    //vedio to text
    const QString VOP_URL="http://vop.baidu.com/server_api";
    //Text to vedio
    const QString TSN_URL="http://tsn.baidu.com/text2audio";
    QString Get_Token_URL="https://aip.baidubce.com/oauth/2.0/token";
    QString MAC_cuid="00:E0:4C:82:4C:B4";
    //语音识别的结果
    QString voice_get_ans;
    explicit ASR(QWidget *parent = 0);
    ~ASR();
    QAudioDeviceInfo SpeechCurrentDevice;
    QAudioInput* audio_input=NULL;
    QBuffer* JsonBuffer=NULL;

    void AudioInit();
    void TokenInit();
    void getMacAddress();
    //更改voice_get_ans
    void changeBaiduAudioAns(QString str);
    bool JudgeTokenTime();
    void startASR();
    void stopASR();

signals:
    void outputASR(QString ASRtext);

public slots:
    //识别声音获得文字
    void Baidu_VoiceToText_replyFinish(QNetworkReply* reply);
    void get_Token_slot(QNetworkReply* reply);
};
#endif // ASR_H
