#include "email.h"
#include "ui_email.h"
#include"sendemail/smtpmime.h"
#include"sendemail/smtpclient.h"
#include "sms.h"
#include<QDebug>
#include<QTimer>
#include<QTime>
#include<QDate>
#include<QFile>

Email::Email(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Email)
{
    ui->setupUi(this);
    this->setFixedSize(282,248);
    this->setWindowIcon(QPixmap(":/resource/7.jpg"));
    this->setWindowTitle("邮件");
    this->setStyleSheet("QWidget{background-color:#575155;}");
    //模态窗口
    this->setAttribute(Qt::WA_ShowModal, true);

    ui->label->setStyleSheet("QLabel{font:16px;}");
    ui->label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    connect(timer,&QTimer::timeout,[=](){
        num++;
        int add;
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        if(num<6)
        {
            add=ui->progressBar->value()+qrand()%20;
        }
        else if(num<16)
        {
            add=ui->progressBar->value()+qrand()%10;
        }
        else
        {
            add=ui->progressBar->value()+qrand()%30;
        }
        ui->progressBar->setValue(add>100?100:add);
        if(add>=100)
        {
            this->setStyleSheet("QWidget{background-color:#d4d38e;}");
            ui->label_2->setText("  发送成功");
            ui->pushButton->setText("关闭");
            QDate date=QDate::currentDate();
            QTime time=QTime::currentTime();
            QString day;
            QString day0=date.toString("dddd");
            qDebug()<<day0;
            if(day0=="星期一")day="周一";
            if(day0=="星期二")day="周二";
            if(day0=="星期三")day="周三";
            if(day0=="星期四")day="周四";
            if(day0=="星期五")day="周五";
            if(day0=="星期六")day="周六";
            if(day0=="星期日")day="周日";
            ui->label->setText(ui->label->text()+"\n"+date.toString("yyyy.MM.dd")+" "+time.toString("H:m:s a")+" "+day);
            timer->stop();

            if(senderEmail.contains(".com"))
            {
                //实例化发送邮件对象
                SmtpClient smtp("smtp.163.com",25,SmtpClient::TcpConnection);
                if(senderEmail.contains("@163.com"))
                {
                    qDebug()<<"邮件类型1";

                }
                if(senderEmail.contains("@qq.com"))
                {
                    qDebug()<<"邮件类型2";
                    smtp.host="smtp.qq.com";
                    smtp.port=465;
                    smtp.setConnectionType(SmtpClient::SslConnection);
                }
                smtp.setUser(senderEmail);
                QFile file("EmailPassword.txt");
                file.open(QFile::ReadOnly);
                QString str=file.readLine();
                file.close();
                smtp.setPassword(str);
                //构建邮件主题,包含发件人收件人附件等.
                MimeMessage message;
                message.setSender(new EmailAddress(senderEmail));
                //逐个添加收件人
                message.addRecipient(new EmailAddress(receiverEmail));
                //构建邮件标题
                message.setSubject(QStringLiteral("你的一位联系人发来的信息"));
                //构建邮件正文
                MimeText text;
                text.setText(emailMessage);
                message.addPart(&text);

                if (!smtp.connectToHost()){
                    ui->label_2->setText("发送失败");
                    QMessageBox::critical(this,"错误","服务器连接失败!");
                    return;
                }
                if (!smtp.login()){
                    ui->label_2->setText("发送失败");
                    QMessageBox::critical(this,"错误","用户登录失败!");
                    return;
                }
                if (!smtp.sendMail(message)){
                    ui->label_2->setText("发送失败");
                    QMessageBox::critical(this,"错误","邮件发送失败!");
                    return;
                }else{
                    QMessageBox::information(this,"提示","邮件发送成功!");
                }
                smtp.quit();
            }
            else
            {
                QMetaObject::invokeMethod(pSms, "singleMessage", Q_ARG(QString, receiverEmail), Q_ARG(QString, emailMessage));
                qDebug()<<receiverEmail;
                qDebug()<<emailMessage;
                QMessageBox::information(this,"提示","短信发送成功!");
            }

        }
    });

    connect(ui->pushButton,&QPushButton::clicked,[=](){
        timer->stop();
        this->close();
    });
}

Email::~Email()
{
    delete ui;
}

//弹出并初始化发送邮件/短信界面，并设定进度条给予用户临时取消发送邮件/短信的时间
void Email::newEmail(QString receiverEmail,QString senderEmail)
{
    num=1;
    this->setStyleSheet("QWidget{background-color:#575155;}");
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(0);
    ui->label_2->setText("正在发送……");
    ui->pushButton->setText("取消");
    if(receiverEmail.contains(".com"))
    {
        ui->label->setText("收件邮箱："+receiverEmail+"\n发件邮箱："+senderEmail);
        qDebug()<<"发送邮件窗口打开成功！";
    }
    else
    {
        ui->label->setText("接收号码："+receiverEmail+"\n发送号码："+senderEmail);
        qDebug()<<"发送短信窗口打开成功！";
    }
    this->show();
    timer->start(300);
}
