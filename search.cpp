#include "search.h"
#include "ui_search.h"
#include"asr.h"
#include<QDebug>
#include<QCloseEvent>

Search::Search(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);
    this->setFixedSize(467,729);
    this->setWindowIcon(QPixmap(":/resource/8.jpg"));
    this->setWindowTitle("查找");
    this->setStyleSheet("QWidget{background-color:#575155;}");
    //模态窗口
    this->setAttribute(Qt::WA_ShowModal, true);

    this->ui->lineEdit->setStyleSheet("QLineEdit{font:24px;color:#edf439;}");

    connect(asrSearch,&ASR::outputASR,[=](QString ASRtext){
        QString str=ui->lineEdit->text();
        int pos=ui->lineEdit->cursorPosition();
        int len=str.length();
        ui->lineEdit->setText(str.left(pos)+ASRtext+str.right(len-pos));
        });
}

Search::~Search()
{
    delete ui;
}

//打开搜索界面
void Search::newSearch()
{
    this->show();
    qDebug()<<"搜索界面打开成功！";
}

//当搜索界面被关闭时，发射searchClose信号，令mainwindow界面出现
void Search::closeEvent(QCloseEvent *event)
{
    qDebug()<<event<<"搜索界面窗口关闭";
    emit this->searchClose();
}

//搜索界面的联系人列表控件点击函数
void Search::on_listWidget_clicked(const QModelIndex &index)
{
    int currentRow = ui->listWidget->currentRow();//当前单击选中ListWidget控件的行号（第几行）
    qDebug()<<currentRow;//将这个行号显示
    qDebug()<<index;
    QListWidgetItem *item=ui->listWidget->item(currentRow);
    this->close();
    emit this->itemClicked(item);
    ui->lineEdit->clear();
    ui->listWidget->clear();
}

//键盘按键事件，Esc：退出程序，F2：语音输入
void Search::keyPressEvent(QKeyEvent *event)
{
    //响应Esc键退出程序
    if(event->key()==Qt::Key_Escape)
    {
        qDebug()<<"退出当前界面";
        this->close();
    }
    if(event->key()==Qt::Key_F2)
    {
        if(asrSearch->isStop==1)
        {
            asrSearch->startASR();
        }
        else
        {
            asrSearch->stopASR();
        }
    }
}
