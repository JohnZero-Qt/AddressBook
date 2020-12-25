#include "messdemo.h"
#include "ui_messdemo.h"
#include "sms.h"
#include <QTimer>
#include <QDebug>
#include<QMessageBox>
#include<QCloseEvent>

Messdemo::Messdemo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Messdemo)
{
    ui->setupUi(this);
    this->setFixedSize(467,729);
    this->setWindowIcon(QPixmap(":/resource/11.jpg"));
    this->setWindowTitle("短信");
    this->setStyleSheet("QWidget{background-color:#FFFFFF;}");
    //模态窗口
    this->setAttribute(Qt::WA_ShowModal, true);
//    this->setStyleSheet("QWidget{background-color:#dfcaf3;}");
    ui->frame->setStyleSheet("QFrame{background-color:#dfcaf3;}");
    ui->textEdit->setStyleSheet("QTextEdit{background-color:#ffffff;font:25px;}");
    ui->label->setStyleSheet("QLabel{font:16px;}");
    ui->label_2->setStyleSheet("QLabel{font:16px;}");
    ui->label_3->setStyleSheet("QLabel{font:25px;}");
    ui->lineEdit->setStyleSheet("QLineEdit{font:25px;}");
    ui->pushButton->setStyleSheet("QPushButton{"
                                     "background-color:#3cf37d;"
                                     "border-style:outset;"
                                     "border-width:2px;"
                                     "border-radius:10px;"
                                     "border-color:beige;"
                                     "font:bold 18px;"
                                     "min-width: 5em;"
                                     "min-height: 2.5em;"
                                     "max-width: 5em;"
                                     "max-height: 2.5em;"
                                 "}");
    ui->label->setText("接受号码：");
    ui->label_2->setText("发送号码：");



    //发送短信按钮
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        if(ui->lineEdit->text()==""||ui->textEdit->toPlainText()=="")
        {
            QMessageBox msgBox;
            msgBox.setText(tr("接收号码和短信内容不能为空！"));
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setStandardButtons(QMessageBox::Ok);
            int ret = msgBox.exec();
            qDebug()<<"点击了ok"<<ret;
        }
        else
        {
            messageEmail->setWindowIcon(QPixmap(":/resource/11.jpg"));
            messageEmail->senderEmail=ui->label_3->text();
            messageEmail->receiverEmail=ui->lineEdit->text();
            messageEmail->emailMessage=ui->textEdit->toPlainText();
            messageEmail->newEmail(messageEmail->receiverEmail,messageEmail->senderEmail);
        }
    });
}

Messdemo::~Messdemo()
{
    delete ui;
}

//当编辑短信界面被关闭时，发射messdemoClose信号，令mainwindow界面出现
void Messdemo::closeEvent(QCloseEvent *event)
{
    qDebug()<<event<<"编辑短信界面窗口关闭";
    emit this->messdemoClose();
}
