#include "call.h"
#include "ui_call.h"

#include<QDebug>
#include<QPaintEvent>
#include<QPainter>
#include<QPushButton>
#include<QLabel>
#include<QPalette>
#include<QTimer>
#include<QSound>

Call::Call(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Call)
{
    ui->setupUi(this);
    this->setFixedSize(467,729);
    this->setWindowIcon(QPixmap(":/resource/6.jpg"));
    this->setWindowTitle("拨号");
    this->setStyleSheet("QMainWindow{background-color:#575155;}");
    //模态窗口
    this->setAttribute(Qt::WA_ShowModal, true);

    connect(timer,&QTimer::timeout,[=](){
        QString str=QString::number(num++);
        label3->setText("00:"+(num>10?str:"0"+str));
    });

    connect(timer1,&QTimer::timeout,[=](){
        callSound->play();
    });

    hangUpBtn->setFixedSize(140,60);
    hangUpBtn->move(164.25,645);
    hangUpBtn->setStyleSheet("QPushButton{/*background-color:#89AFDE;*/border:0px;}");
    hangUpBtn->setFlat(true);
    hangUpBtn->setParent(this);

    label->setFixedSize(300,80);
    label->move(83.5,20);
    label->setStyleSheet("QLabel{/*background-color:#89AFDE;border:0px;*/font:bold 36px;color:#ffffff}");
    label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    label->setText("15387831766");
    label->setParent(this);

    label1->setFixedSize(300,30);
    label1->move(83.5,80);
    label1->setStyleSheet("QLabel{/*background-color:#89AFDE;border:0px;*/font:24px;color:#ffffff}");
    label1->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    label1->setText("潘江湖");
    label1->setParent(this);

    label2->setFixedSize(300,30);
    label2->move(83.5,110);
    label2->setStyleSheet("QLabel{/*background-color:#89AFDE;border:0px;*/font:20px;color:#ffffff}");
    label2->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    label2->setText("正在振铃");
    label2->setParent(this);

    label3->setFixedSize(300,30);
    label3->move(83.5,135);
    label3->setStyleSheet("QLabel{/*background-color:#89AFDE;border:0px;*/font:20px;color:#ffffff}");
    label3->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    label3->setText("00:00");
    label3->setParent(this);

    connect(hangUpBtn,&QPushButton::clicked,[=](){
        emit this->btnClicked();
    });

    connect(this,&Call::btnClicked,[=](){
        label2->setStyleSheet("QLabel{/*background-color:#89AFDE;border:0px;*/font:20px;color:red;}");
        label2->setText("通话结束");
        timer->stop();
        timer1->stop();
        QTimer::singleShot(1000,this,[=](){
            this->close();
            num=1;
            label3->setText("00:00");
            emit this->hangUpBtnClicked();
        });
    });
}

Call::~Call()
{
    delete ui;
}

//打开打电话界面，初始化，开始拨号
void Call::newCall(QString callName,QString callPhoneNumber)
{
    num=1;
    label2->setStyleSheet("QLabel{/*background-color:#89AFDE;border:0px;*/font:20px;color:#ffffff}");
    label2->setText("正在振铃");
    label->setText(callPhoneNumber);
    label1->setText(callName);
    this->show();
    qDebug()<<"电话界面打开成功！";
    timer->start(1000);
    timer1->start(4000);
    callSound->play();
}

//绘制拨号界面的背景图片
void Call::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/resource/5.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

//键盘按键事件，Esc：挂断电话
void Call::keyPressEvent(QKeyEvent *event)
{
    //响应Esc键挂断电话
    if(event->key()==Qt::Key_Escape)
    {
        emit this->btnClicked();
    }
}
