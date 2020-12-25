//功能：其UI文件显示通讯录的登录界面（登录时会显示进度条，并启动音效），一开始会先判断是否注册过，若为注册则弹出注册窗口
#ifndef LOGIN_H
#define LOGIN_H

#include"mainwindow.h"
#include"asr.h"
#include <QMainWindow>
#include<QPaintEvent>
#include<QKeyEvent>
#include<QTimer>
#include<QSound>
#include<QEvent>

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow *mainwindow=new MainWindow;
    int num=1;
    QTimer *timer=new QTimer;
    QSound *startSound=new QSound(":/resource/start.wav");
    ASR *asrLogin=new ASR;
    int onLineEdit1=1;
    int onLineEdit2=0;

    explicit Login(QWidget *parent = 0);
    ~Login();

    void newLogin();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    bool eventFilter(QObject *obj, QEvent *e);
    void readUserMessage();

signals:
    void closeMainWindow();
    void startProcessBar();
    void btnClicked();

private:
    Ui::Login *ui;
};
#endif // LOGIN_H
