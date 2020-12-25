//功能：其UI文件显示新建联系人窗口（会在新建或编辑联系人时弹出），作为基类被addrelative、addfriend、addclassmate、addcolleague类继承，以实现分别添加亲戚、朋友、同学、同事联系人
#ifndef CREATENEW_H
#define CREATENEW_H

#include <QMainWindow>
#include<QDialog>
#include<asr.h>

namespace Ui {
class CreateNew;
}

class CreateNew : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateNew(QWidget *parent = 0);
    ~CreateNew();

    Ui::CreateNew *ui;

    QString name;
    QString year;
    QString month;
    QString day;
    QString phoneNumber;
    QString email;
    QString fifth;
    QString head;
    ASR *asrCreatNew=new ASR;
    int onLineEdit1=1;
    int onLineEdit2=0;
    int onLineEdit3=0;
    int onLineEdit4=0;
    int onLineEdit5=0;

    void keyPressEvent(QKeyEvent *);
    bool eventFilter(QObject *obj, QEvent *e);

signals:
   void updateRelativeList();
   void updateFriendList();
   void updateClassmateList();
   void updateColleagueList();

public slots:
    void newPerson();
private slots:
    void on_pushButton_pressed();
    void on_pushButton_released();
};

#endif // CREATENEW_H
