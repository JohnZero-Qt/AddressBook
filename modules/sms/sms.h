#ifndef SMS_H
#define SMS_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSslError>


class Sms : public QObject
{
    Q_OBJECT
public:
    explicit Sms(QObject *parent = nullptr);

signals:
    void error(QString msg);

public slots:
    // 单发短信：给用户发短信验证码、短信通知，营销短息（内容长度不超过450字节）
    void singleMessage(QString number, QString content);

protected slots:
    void finished(QNetworkReply *);
    void sslErrors(QNetworkReply*,QList<QSslError>);

private:
    QNetworkAccessManager _manager;
    static QString _sdkAppId;
    static QString _sdkAppKey;
    QString _time;
    QString _random;
    QString _type;
};

#endif // SMS_H
