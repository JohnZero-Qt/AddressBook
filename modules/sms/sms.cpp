#include "sms.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QDebug>
#include <QUrlQuery>

QString Sms::_sdkAppId  = "johnzero514";
QString Sms::_sdkAppKey = "08fadb1460dd77cb2fe83bec0bab46ae";


Sms::Sms(QObject *parent) : QObject(parent),_random("0"), _type("0") {
    connect(&_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));
    connect(&_manager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT(sslErrors(QNetworkReply*,QList<QSslError>)));
}

void Sms::singleMessage(QString mobile, QString content){

    // 移动平台  http://sms.sms.cn/
    /*
     *  http://api.sms.cn/sms/?ac=send
        &uid=qq21497936&pwd=接口密码[获取密码]
        &template=100006&mobile=填写要发送的手机号
        &content={"code":"value"}
    */

    QString baseUrl = QString("http://api.sms.cn/sms/");
    QUrl url;
    url.setUrl(baseUrl);
    QUrlQuery urlQuery;

    urlQuery.addQueryItem("ac", "send");
    urlQuery.addQueryItem("uid", _sdkAppId);    //账户
    urlQuery.addQueryItem("pwd", _sdkAppKey);   //接口密码
    urlQuery.addQueryItem("template", "100006");//模板ID
    urlQuery.addQueryItem("mobile", mobile);    //手机号码
    urlQuery.addQueryItem("content", QString("{\"code\":\"%1\"}").arg(content));
    url.setQuery(urlQuery);
    _manager.get(QNetworkRequest(url));
}

void Sms::finished(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    qDebug() << __FILE__ << __LINE__ << data;
}


void Sms::sslErrors(QNetworkReply *reply, QList<QSslError> list)
{
    qDebug()<<reply;
    qDebug() << __FILE__ << __LINE__ << list;
}
