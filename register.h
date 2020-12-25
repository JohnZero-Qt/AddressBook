//功能：其UI文件显示注册窗口（此窗口会在注册和修改密码时提出），保存用户的姓名、出生日期、电话、邮箱、登录密码
#ifndef REGISTER_H
#define REGISTER_H

#include <QMainWindow>
#include<QKeyEvent>
#include<QEvent>
#include"asr.h"

namespace Ui {
class Register;
}

class Register : public QMainWindow
{
    Q_OBJECT

public:
    int isOnEdit=0;
    Ui::Register *ui;
    ASR *asrRegister=new ASR;
    int onLineEdit1=1;
    int onLineEdit2=0;
    int onLineEdit3=0;
    int onLineEdit4=0;
    int onLineEdit5=0;

    explicit Register(QWidget *parent = 0);
    ~Register();
    void keyPressEvent(QKeyEvent *);
    bool eventFilter(QObject *obj, QEvent *e);

signals:
    void newRegister(QString name,QString password);
};
#endif // REGISTER_H
