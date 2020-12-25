//功能：其UI文件显示主窗口，该通讯录大部分的功能
//1.新建/编辑/删除联系人；2.按姓名/出生日期对联系人进行排序；3.按照关键字来查找联系人；4.给联系人打电话；5.给联系人发邮件并自动生成贺信;6.修改登录密码或其他用户信息；7.注销账号
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include"createnew.h"
#include"call.h"
#include"email.h"
#include"search.h"
#include"birthday.h"
#include"register.h"
#include"inputemailpassword.h"
#include"asr.h"
#include "messdemo.h"
#include"headpath.h"
#include <QMainWindow>
#include<QPaintEvent>
#include<QPainter>
#include<QSound>
#include<QListWidgetItem>
#include<QKeyEvent>
#include<QEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     Ui::MainWindow *ui;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

     ASR *asrMainWindow=new ASR;
     int onLineEdit1=1;
     int onLineEdit2=0;
     int onTextEdit=0;

    CreateNew *person=new CreateNew;
    Call *call=new Call;
    Email *email=new Email;
    Search *search=new Search;
    Birthday *birthday=new Birthday;
    Register *register0=new Register;
    InputEmailPassword *inputEP=new InputEmailPassword;
    Messdemo *mess = new Messdemo;
    HeadPath *headPath=new HeadPath;

    int sortOrder=0;    //默认按名字排序
    QString globalPath="";
    QString globalItemName="";
    QString userName="潘江湖";
    QString userPhoneNumber="15387831766";
    QString userEmail="1834066776@qq.com";
    QString password;
    //点击数字按键的音效
    QSound *clickSound=new QSound(":/resource/click.wav");

    void updateRelative();
    void updateFriend();
    void updateClassmate();
    void updateColleague();
    void updateAll();
    void updateUnit(QString path,int index=0);
    void updateBirthdayListWidget(int value=5);
    void msgBoxUnit(QString path,QListWidgetItem *item);
    void discardPerson(QString path,QString itemName);
    void keyPressEvent(QKeyEvent *);
    bool eventFilter(QObject *obj, QEvent *e);

signals:
    void phoneBtnClicked();

private slots:
    void on_listWidget_clicked(const QModelIndex &index);
    void on_listWidget_2_clicked(const QModelIndex &index);
    void on_listWidget_3_clicked(const QModelIndex &index);
    void on_listWidget_4_clicked(const QModelIndex &index);
    void on_listWidget_5_clicked(const QModelIndex &index);
};

#endif // MAINWINDOW_H
