#include "login.h"
#include "ui_login.h"

#include"mainwindow.h"
#include"ui_mainwindow.h"
#include"register.h"
#include"ui_register.h"
#include"asr.h"
#include<QPaintEvent>
#include<QPainter>
#include<QDebug>
#include<QMainWindow>
#include<QKeyEvent>
#include<QPushButton>
#include<QFile>
#include<QTextCodec>
#include<QMessageBox>
#include<QSound>
#include<QTimer>
#include<QTime>

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowIcon(QPixmap(":/resource/3.jpg"));
    this->setWindowTitle("个人通讯录管理系统");
    //登录界面全屏显示
    this->setWindowFlags (Qt::Window);
    this->showFullScreen ();

    ui->lineEdit->installEventFilter(this);
    ui->lineEdit_2->installEventFilter(this);

    ui->lineEdit->setGeometry(770,360,420,75);
    ui->lineEdit_2->setGeometry(770,485,420,75);
    ui->pushButton->setGeometry(710,660,500,75);
    ui->lineEdit->setStyleSheet("QLineEdit{background-color: rgba(255, 255, 255, 0%);border:0px solid #b9babb;font:bold 40px;}");
    ui->lineEdit_2->setStyleSheet("QLineEdit{background-color: rgba(255, 255, 255, 0%);border:0px solid #b9babb;font:bold 40px;}");
    ui->pushButton->setStyleSheet("QPushButton{border:0px;}");//将按钮的点击效果隐藏
    ui->pushButton->setFlat(true);//将按钮设为透明
    ui->pushButton->setText("");//令文本为空
    //设置提示
    ui->lineEdit->setPlaceholderText("Username");
    ui->lineEdit_2->setPlaceholderText("Password");
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->progressBar->setGeometry(500,640,920,115);
    ui->progressBar->setStyleSheet("QProgressBar{border:1px solid #FFFFFF;height:300;background:red;text-align: center;color:rgb(255,255,0);font:30px;border-radius:50px;}"
                                   "QProgressBar::chunk{background:rgb(0,0,255);border-radius:50px;}");

    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(15);
    ui->progressBar->setVisible(false);

    //进度条计时器
    connect(timer,&QTimer::timeout,[=](){
        num++;
        int add;
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        if(num<6)
        {
            add=ui->progressBar->value()+qrand()%20;
        }
        else if(num<16)
        {
            if(num==7) startSound->play();
            add=ui->progressBar->value()+qrand()%10;
        }
        else
        {
            add=ui->progressBar->value()+qrand()%30;          
        }
        ui->progressBar->setValue(add>100?100:add);
        if(add>=100)
        {           
            timer->stop();
            this->hide();
            //进度条到达100%,延迟弹出注册窗口
            QTimer::singleShot(500,this,[=](){
                mainwindow->show();
            });
        }
    });

    //点击注销
    connect(ui->actionLogout,&QAction::triggered,[=](){
        qDebug()<<"注销账号";
        //清空AddressBook1文本
        QFile file1("AddressBook1.txt");
        file1.open(QFile::WriteOnly|QFile::Truncate);
        file1.close();
        //清空AddressBook2文本
        QFile file2("AddressBook2.txt");
        file2.open(QFile::WriteOnly|QFile::Truncate);
        file2.close();
        //清空AddressBook3文本
        QFile file3("AddressBook3.txt");
        file3.open(QFile::WriteOnly|QFile::Truncate);
        file3.close();
        //清空AddressBook4文本
        QFile file4("AddressBook4.txt");
        file4.open(QFile::WriteOnly|QFile::Truncate);
        file4.close();
        //清空Password文本
        QFile file5("Password.txt");
        file5.open(QFile::WriteOnly|QFile::Truncate);
        file5.close();
        //清空EmailPassword文本
        QFile file6("EmailPassword.txt");
        file6.open(QFile::WriteOnly|QFile::Truncate);
        file6.close();

        this->close();        
    });
    //点击退出
    connect(ui->actionQuit,&QAction::triggered,[=](){
        qDebug()<<"退出登录界面";
        this->close();
    });
    //点击登录按钮
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        qDebug()<<"点击了sign in";       
        emit this->btnClicked();
    });

    connect(this,&Login::btnClicked,[=](){
        qDebug()<<"接收到btnClicked信号";
        if(ui->lineEdit->text()=="")
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText("用户名不能为空！");
            msgBox.setWindowTitle("警告");
            QPushButton *confirmBtn=msgBox.addButton(tr("确认"),QMessageBox::ActionRole);
            msgBox.exec();
            if(msgBox.clickedButton()==confirmBtn)
            {
                qDebug()<<"点击了confirmBtn";
            }
        }
        else if(ui->lineEdit->text()!=mainwindow->userName)
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText("用户名错误！");
            msgBox.setWindowTitle("警告");
            QPushButton *confirmBtn=msgBox.addButton(tr("确认"),QMessageBox::ActionRole);
            msgBox.exec();
            if(msgBox.clickedButton()==confirmBtn)
            {
                qDebug()<<"点击了confirmBtn";
            }
        }
        else if(ui->lineEdit_2->text()!=mainwindow->password)
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText("密码错误！");
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
            emit this->startProcessBar();
        }
    });

    connect(mainwindow->register0,&Register::newRegister,[=](QString name,QString password){
        ui->lineEdit->setText(name);
        ui->lineEdit_2->setText(password);
        readUserMessage();
        emit this->startProcessBar();
    });

    connect(this,&Login::startProcessBar,[=](){       
        ui->progressBar->setVisible(true);
        timer->start(300);
    });

    QFile file("Password.txt");
    if(file.size()==0)
    {
        //延迟弹出注册窗口
        QTimer::singleShot(2500,this,[=](){
            mainwindow->register0->show();
        });
    }
    else readUserMessage();

    connect(asrLogin,&ASR::outputASR,[=](QString ASRtext){
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
    });
}

Login::~Login()
{
    delete ui;
}

//弹出登录界面并令其全屏
void Login::newLogin()
{
    emit this->closeMainWindow();
    qDebug()<<"登录界面打开成功！";
    this->showFullScreen();
}

//绘制登录界面的背景图片
void Login::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/resource/10.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

//键盘按键事件，Esc：退出程序，Enter：登录，F2：语音输入
void Login::keyPressEvent(QKeyEvent *event)
{
    //响应Esc键退出程序
    if(event->key()==Qt::Key_Escape)
    {
        qDebug()<<"退出当前界面";
        this->close();
    }
    //按enter登录
    if(event->key()==Qt::Key_Enter||event->key()==Qt::Key_Return)
    {
        qDebug()<<"按了enter键以登录";
        emit this->btnClicked();
    }

    if(event->key()==Qt::Key_F2)
    {
        if(asrLogin->isStop==1)
        {
            asrLogin->startASR();
        }
        else
        {
            asrLogin->stopASR();           
        }
    }
}

//事件过滤器，若当前触发鼠标点击事件且对象为某一文本框，则令该文本框成为语音输入对象
bool Login::eventFilter(QObject *obj, QEvent *e)
{
    if(e->type()==QEvent::MouseButtonPress)
        {
            if(obj == ui->lineEdit)
            {
                onLineEdit1=1;
                onLineEdit2=0;
            }
            if(obj == ui->lineEdit_2)
            {
                onLineEdit1=0;
                onLineEdit2=1;
            }
        }    
        return QMainWindow::eventFilter(obj,e);
}

//首次注册后读取刚刚添加的用户信息，并自动填入姓名和登录密码
void Login::readUserMessage()
{
    QFile file("Password.txt");
    file.open(QFile::ReadOnly);
    int i=0;
    while(!file.atEnd())
    {
        i++;
        QString str=QTextCodec::codecForName("GBK")->toUnicode(file.readLine());
        if(i==1) mainwindow->userName=str.remove(str.length()-1,1);
        if(i==5) mainwindow->userPhoneNumber=str.remove(str.length()-1,1);
        if(i==6) mainwindow->userEmail=str.remove(str.length()-1,1);
        if(i==7) mainwindow->password=str;
    }
    file.close();
    mainwindow->ui->label_5->setText(mainwindow->userEmail);
    qDebug()<<mainwindow->userName;
    qDebug()<<mainwindow->userPhoneNumber;
    qDebug()<<mainwindow->userEmail;
    qDebug()<<mainwindow->password;
}
