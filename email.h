//功能：其UI文件显示发送邮件界面，并显示进度条，用户在进度条达到100%之前可以取消发送邮件，否则会弹出邮箱SMTP服务授权码输入窗口，若授权码正确即可发送邮件
//核心代码为sendmail包，可实现发邮件功能（简单文本，富文本，附件，图片等），也可以群发邮件
//判断发件人邮箱为那种类型的邮箱
//若为163邮箱则设置服务器为smtp.163.com，端口为25，通讯协议为TcpConnection;若为qq邮箱则设置服务器为smtp.qq.com，端口为465，通讯协议为SslConnection;
//由于此应用为通讯录管理系统，所以我只是用它实现了发送简单文本给一位联系人的功能。
//发送成功后会显示当前邮件的发送时间yyyy.mm.dd H:M:S dddd年月日 时分秒 星期几
#ifndef EMAIL_H
#define EMAIL_H

#include <QWidget>
#include<QTimer>
#include"sms.h"

namespace Ui {
class Email;
}

class Email : public QWidget
{
    Q_OBJECT

public:
    explicit Email(QWidget *parent = 0);
    ~Email();

    int num=1;
    QTimer *timer=new QTimer;
    QString senderEmail;
    QString receiverEmail;
    QString emailMessage;
    Sms *pSms=new Sms;

    void newEmail(QString receiverEmail,QString senderEmail);

private:
    Ui::Email *ui;
};

#endif // EMAIL_H
