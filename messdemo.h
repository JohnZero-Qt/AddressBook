#ifndef MESSDEMO_H
#define MESSDEMO_H

#include <QMainWindow>
#include"email.h"
#include"sms.h"
#include<QCloseEvent>

//class Sms;
namespace Ui {
class Messdemo;
}

class Messdemo : public QMainWindow
{
    Q_OBJECT

public:
    explicit Messdemo(QWidget *parent = 0);
    ~Messdemo();
    Ui::Messdemo *ui;
    Email *messageEmail=new Email;

    void closeEvent(QCloseEvent *event);
signals:
    void messdemoClose();
};

#endif // MAINWINDOW_H
