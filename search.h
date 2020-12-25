//功能：其UI文件显示搜索窗口，能按姓名、出生日期、电话号码、邮箱地址、称呼、地点、学习、单位查询相应的联系人并列表显示
#ifndef SEARCH_H
#define SEARCH_H

#include <QWidget>
#include<QCloseEvent>
#include<QListWidgetItem>
#include<QKeyEvent>
#include<QEvent>
#include"asr.h"

namespace Ui {
class Search;
}

class Search : public QWidget
{
    Q_OBJECT

public:
    Ui::Search *ui;
    ASR *asrSearch=new ASR;

    explicit Search(QWidget *parent = 0);
    ~Search();

    void newSearch();
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *);

signals:
    void searchClose();
    void itemClicked(QListWidgetItem *item);

private slots:
    void on_listWidget_clicked(const QModelIndex &index);
};

#endif // SEARCH_H
