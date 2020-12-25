//功能：UI文件显示拨号界面，模仿手机拨号
#ifndef CALL_H
#define CALL_H

#include <QMainWindow>
#include<QPaintEvent>
#include<QPainter>
#include<QLabel>
#include<QPushButton>
#include<QTimerEvent>
#include<QTimer>
#include<QSound>
#include<QKeyEvent>

namespace Ui {
class Call;
}

class Call : public QMainWindow
{
    Q_OBJECT

public:
    int num=1;

    QPushButton *hangUpBtn=new QPushButton;
    QLabel *label=new QLabel;
    QLabel *label1=new QLabel;
    QLabel *label2=new QLabel;
    QLabel *label3=new QLabel;

    QSound *callSound=new QSound(":/resource/call.wav");


    QTimer *timer=new QTimer(this);
    QTimer *timer1=new QTimer(this);

    explicit Call(QWidget *parent = 0);
    ~Call();
    void newCall(QString callName,QString callPhoneNumber);
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);

signals:
    void hangUpBtnClicked();
    void btnClicked();

private:
    Ui::Call *ui;
};

#endif // CALL_H
