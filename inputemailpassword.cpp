#include "inputemailpassword.h"
#include "ui_inputemailpassword.h"
#include"asr.h"
#include<QFile>
#include<QMessageBox>


InputEmailPassword::InputEmailPassword(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InputEmailPassword)
{
    ui->setupUi(this);
    this->setWindowTitle("邮箱授权码");
    this->setFixedSize(292,123);
    //模态窗口
    this->setAttribute(Qt::WA_ShowModal, true);
    ui->lineEdit->setPlaceholderText("需开启邮箱SMTP服务");
    ui->lineEdit->setStyleSheet("QLineEdit{font:25px;}");
    ui->lineEdit->setEchoMode(QLineEdit::Password);

    QFile file("EmailPassword.txt");
    if(file.size()!=0)
    {
        file.open(QFile::ReadOnly);
        QString str=file.readLine();
        ui->lineEdit->setText(str);
        file.close();
    }
        
    connect(ui->pushButton,&QPushButton::clicked,[=](){
             emit this->btnClicked();
    });

    connect(this,&InputEmailPassword::btnClicked,[=](){
        if(ui->lineEdit->text()=="")
        {
           QMessageBox::information(NULL,tr("不能为空"),tr("请输入邮箱SMTP服务授权码！"));
        }
        else
        {
            emailPassword=ui->lineEdit->text();
            emit this->emailPasswordBtnClicked(emailPassword);
            this->close();
        }
    });

    connect(asrInputEP,&ASR::outputASR,[=](QString ASRtext){
        QString str=ui->lineEdit->text();
        int pos=ui->lineEdit->cursorPosition();
        int len=str.length();
        ui->lineEdit->setText(str.left(pos)+ASRtext+str.right(len-pos));
        });
}

InputEmailPassword::~InputEmailPassword()
{
    delete ui;
}

//键盘按键事件，Esc：退出程序，Enter：确认授权码，F2：语音输入
void InputEmailPassword::keyPressEvent(QKeyEvent *event)
{
    //响应Esc键退出程序
    if(event->key()==Qt::Key_Escape)
    {
        qDebug()<<"退出当前界面";
        this->close();
    }
    //按enter确认授权码
    if(event->key()==Qt::Key_Enter||event->key()==Qt::Key_Return)
    {
        qDebug()<<"按了enter键以确认授权码";
        emit this->btnClicked();
    }

    if(event->key()==Qt::Key_F2)
    {
        if(asrInputEP->isStop==1)
        {
            asrInputEP->startASR();
        }
        else
        {
            asrInputEP->stopASR();
        }
    }
}
