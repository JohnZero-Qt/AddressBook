#include "register.h"
#include "ui_register.h"
#include"asr.h"
#include<QMenuBar>
#include<QFile>
#include<QMessageBox>
#include<QPushButton>
#include<QDebug>

Register::Register(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->setWindowIcon(QPixmap(":/resource/3.jpg"));
    this->setWindowTitle("注册");
    this->resize(282,382);
    QMenuBar *bar=menuBar();
    setMenuBar(bar);
    //创建菜单
    QMenu *mainMenu=bar->addMenu("菜单");
    //创建菜单项
    QAction *quitAction=mainMenu->addAction("退出");
    //添加分割线
//    mainMenu->addSeparator();
    this->setAttribute(Qt::WA_ShowModal, true);	//设置模态

    ui->lineEdit_4->setEchoMode(QLineEdit::Password);
    ui->lineEdit_5->setEchoMode(QLineEdit::Password);
    ui->pushButton->setStyleSheet("QPushButton{"
                                     "background-color:#e54c4c;"
                                     "border-style:outset;"
                                     "border-width:2px;"
                                     "border-radius:10px;"
                                     "border-color:beige;"
                                     "font:bold 18px;"
                                     "min-width: 5em;"
                                     "min-height: 2em;"
                                     "max-width: 5em;"
                                     "max-height: 2em;"
                                 "}");

    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    connect(ui->pushButton,&QPushButton::clicked,[=](){
        if(ui->lineEdit->text()==""||ui->lineEdit_2->text()==""||ui->lineEdit_3->text()==""||ui->lineEdit_4->text()==""||ui->lineEdit_5->text()=="")
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText("内容不能为空！");
            msgBox.setWindowTitle("警告");
            QPushButton *confirmBtn=msgBox.addButton(tr("确认"),QMessageBox::ActionRole);
            msgBox.exec();
            if(msgBox.clickedButton()==confirmBtn)
            {
                qDebug()<<"点击了confirmBtn";
            }
        }
        else if(ui->lineEdit_4->text()!=ui->lineEdit_5->text())
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText("两次输入的密码不同！");
            msgBox.setWindowTitle("警告");
            QPushButton *confirmBtn=msgBox.addButton(tr("确认"),QMessageBox::ActionRole);
            msgBox.exec();
            if(msgBox.clickedButton()==confirmBtn)
            {
                qDebug()<<"点击了confirmBtn";
            }
        }
        else
        {
            //清空Password文本
            QFile file1("Password.txt");
            file1.open(QFile::WriteOnly|QFile::Truncate);
            file1.close();

            QFile file("Password.txt");
            if(file.open(QFile::WriteOnly|QIODevice::Append))
            {
                QTextStream out(&file);
                out<<ui->lineEdit->text().toUtf8()<<"\n";
                QString str;
                str.setNum(ui->dateEdit->date().year());
                out<<str<<"\n";
                str.setNum(ui->dateEdit->date().month());
                if(ui->dateEdit->date().month()<=9) str.prepend("0");
                out<<str<<"\n";
                str.setNum(ui->dateEdit->date().day());
                if(ui->dateEdit->date().day()<=9) str.prepend("0");
                out<<str<<"\n";

                out<<ui->lineEdit_2->text().toUtf8()<<"\n";
                out<<ui->lineEdit_3->text().toUtf8()<<"\n";
                out<<ui->lineEdit_4->text().toUtf8();

                file.close();
                qDebug()<<"用户信息保存成功！";

                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Information);
                if(isOnEdit==0) msgBox.setText("注册成功！\n提示：F2可开启/结束语音输入");
                else msgBox.setText("修改成功！");
                msgBox.setWindowTitle("提示");
                QPushButton *confirmBtn=msgBox.addButton(tr("关闭"),QMessageBox::ActionRole);
                msgBox.exec();
                if(msgBox.clickedButton()==confirmBtn)
                {
                    qDebug()<<"点击了confirmBtn";
                    this->close();
                    emit this->newRegister(ui->lineEdit->text(),ui->lineEdit_4->text());
                }
            }
        }
    });

    ui->lineEdit->installEventFilter(this);
    ui->lineEdit_2->installEventFilter(this);
    ui->lineEdit_3->installEventFilter(this);
    ui->lineEdit_4->installEventFilter(this);
    ui->lineEdit_5->installEventFilter(this);

    connect(asrRegister,&ASR::outputASR,[=](QString ASRtext){
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

Register::~Register()
{
    delete ui;
}

//键盘按键事件，Esc：退出程序，F2：语音输入
void Register::keyPressEvent(QKeyEvent *event)
{
    //响应Esc键退出程序
    if(event->key()==Qt::Key_Escape)
    {
        qDebug()<<"退出当前界面";
        this->close();
    }
    if(event->key()==Qt::Key_F2)
    {
        if(asrRegister->isStop==1)
        {
            asrRegister->startASR();
        }
        else
        {
            asrRegister->stopASR();
        }
    }
}

//事件过滤器，若当前触发鼠标点击事件且对象为某一文本框，则令该文本框成为语音输入对象
bool Register::eventFilter(QObject *obj, QEvent *e)
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
