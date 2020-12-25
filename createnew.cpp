#include "createnew.h"
#include "ui_createnew.h"
#include"mainwindow.h"
#include"addrelative.h"
#include"addfriend.h"
#include"addclassmate.h"
#include"addcolleague.h"
#include"asr.h"
#include<QDebug>
#include <QApplication>
#include<QDialog>
#include<QPushButton>
#include<QComboBox>
#include<windows.h>
#include<QDate>
#include<QFileDialog>

CreateNew::CreateNew(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateNew)
{
    ui->setupUi(this);

    this->setFixedSize(292,425);
    this->setWindowIcon(QPixmap(":/resource/1.jpg"));
    this->setWindowTitle("新建");
    //模态窗口
    this->setAttribute(Qt::WA_ShowModal, true);
    ui->newConfirmBtn->setParent(this);

    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        //添加头文件#include <QFileDialog>
        //文件对话框  参数 1  父亲  参数2  标题   参数3  默认打开路径  参数4  过滤文件格式
        //返回值是 选取的路径
        QString str = QFileDialog::getOpenFileName(this,"打开文件");
        ui->lineEdit_5->setText(str);
        qDebug() << str;

//        ui->listWidget->setIconSize(QSize(500,500));
//        QListWidgetItem * item = new QListWidgetItem(QIcon(str),"潘江湖");
//        item->setFont(QFont("华文宋体",10));
//        ui->listWidget->addItem(item);
    });

    connect(ui->newConfirmBtn,&QPushButton::clicked,[=](){

        qDebug()<<"点击了确定";

        name=ui->lineEdit->text();
        phoneNumber=ui->lineEdit_2->text();
        email=ui->lineEdit_3->text();
        fifth=ui->lineEdit_4->text();
        QString str;
        str.setNum(ui->dateEdit->date().year());
        year=str;
        str.setNum(ui->dateEdit->date().month());
        if(ui->dateEdit->date().month()<=9) str.prepend("0");
        month=str;
        str.setNum(ui->dateEdit->date().day());
        if(ui->dateEdit->date().day()<=9) str.prepend("0");
        day=str;
        head=ui->lineEdit_5->text();

        if(ui->comboBox->currentIndex()==0)
        {
            AddRelative *newRelative=new AddRelative(name,phoneNumber,email,fifth,year,month,day,head);
            qDebug()<<newRelative->name.toUtf8().data();
            emit this->updateRelativeList();
        }
        if(ui->comboBox->currentIndex()==1)
        {
            AddFriend *newFriend=new AddFriend(name,phoneNumber,email,fifth,year,month,day,head);
            qDebug()<<newFriend->name.toUtf8().data();
            emit this->updateFriendList();
        }
        if(ui->comboBox->currentIndex()==2)
        {
            AddClassmate *newClassmate=new AddClassmate(name,phoneNumber,email,fifth,year,month,day,head);
            qDebug()<<newClassmate->name.toUtf8().data();
            emit this->updateClassmateList();
        }
        if(ui->comboBox->currentIndex()==3)
        {
            AddColleague *newColleague=new AddColleague(name,phoneNumber,email,fifth,year,month,day,head);
            qDebug()<<newColleague->name.toUtf8().data();
            emit this->updateColleagueList();
        }

        this->close();
        //改变了下拉框的索引值，qDebug()<<0;
        ui->comboBox->setCurrentIndex(0);
        ui->dateEdit->setDate(QDate::fromString("20000101", "yyyyMMdd"));
        ui->label_6->setText("称呼：");
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
    });

    //随着下拉框内容的变化而修改label6的文本
    connect(ui->comboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),[=](int index){
        //输出当前下拉框的索引值
        qDebug()<<index;
        if(index==0)
        {
            ui->label_6->setText("称呼：");

        }
        if(index==1)
        {

            ui->label_6->setText("地点：");
        }
        if(index==2)
        {
            ui->label_6->setText("学校：");

        }
        if(index==3)
        {

            ui->label_6->setText("单位：");
        }
    });

    ui->lineEdit->installEventFilter(this);
    ui->lineEdit_2->installEventFilter(this);
    ui->lineEdit_3->installEventFilter(this);
    ui->lineEdit_4->installEventFilter(this);

    connect(asrCreatNew,&ASR::outputASR,[=](QString ASRtext){
            if(onLineEdit1==1)
            {
                QString str=ui->lineEdit->text();
                int pos=ui->lineEdit->cursorPosition();
                int len=str.length();
                ui->lineEdit->setText(str.left(pos)+ASRtext+str.right(len-pos));
            }
            if(onLineEdit2==1)
            {
                QString str=ui->lineEdit_2->text();
                int pos=ui->lineEdit_2->cursorPosition();
                int len=str.length();
                ui->lineEdit_2->setText(str.left(pos)+ASRtext+str.right(len-pos));
            }
            if(onLineEdit3==1)
            {
                QString str=ui->lineEdit_3->text();
                int pos=ui->lineEdit_3->cursorPosition();
                int len=str.length();
                ui->lineEdit_3->setText(str.left(pos)+ASRtext+str.right(len-pos));
            }
            if(onLineEdit4==1)
            {
                QString str=ui->lineEdit_4->text();
                int pos=ui->lineEdit_4->cursorPosition();
                int len=str.length();
                ui->lineEdit_4->setText(str.left(pos)+ASRtext+str.right(len-pos));
            }
            if(onLineEdit5==1)
            {
                QString str=ui->lineEdit_5->text();
                int pos=ui->lineEdit_5->cursorPosition();
                int len=str.length();
                ui->lineEdit_5->setText(str.left(pos)+ASRtext+str.right(len-pos));
            }
        });
}

CreateNew::~CreateNew()
{
    delete ui;
}

//打开新建联系人界面
void CreateNew::newPerson()
{
    this->show();
    qDebug()<<"新建联系人界面打开成功！";
}

//键盘按键事件，Esc：退出程序，F2：语音输入
void CreateNew::keyPressEvent(QKeyEvent *event)
{
    //响应Esc键退出程序
    if(event->key()==Qt::Key_Escape)
    {
        qDebug()<<"退出当前界面";
        this->close();
    }
    if(event->key()==Qt::Key_F2)
    {
        if(asrCreatNew->isStop==1)
        {
            asrCreatNew->startASR();
        }
        else
        {
            asrCreatNew->stopASR();
        }
    }
}

//事件过滤器，若当前触发鼠标点击事件且对象为某一文本框，则令该文本框成为语音输入对象
bool CreateNew::eventFilter(QObject *obj, QEvent *e)
{
    if(e->type()==QEvent::MouseButtonPress)
        {
            if(obj == ui->lineEdit)
            {
                onLineEdit1=1;
                onLineEdit2=0;
                onLineEdit3=0;
                onLineEdit4=0;
                onLineEdit5=0;
            }
            if(obj == ui->lineEdit_2)
            {
                onLineEdit1=0;
                onLineEdit2=1;
                onLineEdit3=0;
                onLineEdit4=0;
                onLineEdit5=0;
            }
            if(obj == ui->lineEdit_3)
            {
                onLineEdit1=0;
                onLineEdit2=0;
                onLineEdit3=1;
                onLineEdit4=0;
                onLineEdit5=0;
            }
            if(obj == ui->lineEdit_4)
            {
                onLineEdit1=0;
                onLineEdit2=0;
                onLineEdit3=0;
                onLineEdit4=1;
                onLineEdit5=0;
            }
            if(obj == ui->lineEdit_5)
            {
                onLineEdit1=0;
                onLineEdit2=0;
                onLineEdit3=0;
                onLineEdit4=0;
                onLineEdit5=1;
            }
        }
        return QMainWindow::eventFilter(obj,e);
}

//当语音按钮被按压时，startASR()语音输入
void CreateNew::on_pushButton_pressed()
{
    ui->pushButton->setText("松开识别");
        asrCreatNew->startASR();
}

//当语音按钮被松开时，stopASR()结束语音输入
void CreateNew::on_pushButton_released()
{
    ui->pushButton->setText("按住说话");
    asrCreatNew->stopASR();
}
