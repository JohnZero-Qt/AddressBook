//功能：其UI文件对应于生日提醒界面，告知用户每月有多少人过生日，并将最近过生日的联系人列表显示，并显示他们过生日那天是星期几
#ifndef BIRTHDAY_H
#define BIRTHDAY_H

#include <QWidget>
#include<QCloseEvent>
#include<QListWidget>
#include<QListWidgetItem>

namespace Ui {
class Birthday;
}

class Birthday : public QWidget
{
    Q_OBJECT

public:
    Ui::Birthday *ui;

    explicit Birthday(QWidget *parent = 0);
    ~Birthday();

    void newBirthday();
    void closeEvent(QCloseEvent *event);

signals:
    void birthdayClose();
    void itemClicked(QListWidgetItem *item);

private slots:
    void on_listWidget_clicked(const QModelIndex &index);
};

#endif // BIRTHDAY_H
