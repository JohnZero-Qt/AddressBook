#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createnew.h"
#include"ui_createnew.h"
#include"call.h"
#include"ui_call.h"
#include"email.h"
#include"ui_email.h"
#include"search.h"
#include"ui_search.h"
#include"birthday.h"
#include"ui_birthday.h"
#include"register.h"
#include"ui_register.h"
#include"asr.h"
#include"inputemailpassword.h"
#include"messdemo.h"
#include"ui_messdemo.h"
#include"headpath.h"
#include<QDebug>
#include<QFile>
#include<QTextCodec>
#include<QMessageBox>
#include<QPushButton>
#include<QDate>
#include<QListWidget>
#include<QListWidgetItem>
#include<QPaintEvent>
#include<QPainter>
#include<QLabel>
#include<QSound>
#include<QLineEdit>
#include<QTextEdit>
#include<QPlainTextEdit>
#include<QSpinBox>
#include<QString>
#include<QStringList>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //初始化界面
    ui->setupUi(this);
    this->setFixedSize(467,729);
    this->setWindowIcon(QPixmap(":/resource/3.jpg"));
    this->setWindowTitle("通讯录");
    //初始锁定在亲戚界面
    ui->tabWidget_2->setCurrentIndex(1);
    ui->tabWidget->setCurrentIndex(0);
    ui->frame->setStyleSheet("QFrame{background-color:#dfcaf3;}");
    ui->textEdit->setStyleSheet("QTextEdit{background-color:#ffffff;font:25px;}");
    ui->label_3->setStyleSheet("QLabel{font:16px;}");
    ui->label_4->setStyleSheet("QLabel{font:16px;}");
    ui->label_5->setStyleSheet("QLabel{font:25px;}");
    ui->lineEdit_2->setStyleSheet("QLineEdit{font:25px;}");
    ui->pushButton_16->setStyleSheet("QPushButton{"
                                     "background-color:#3cf37d;"
                                     "border-style:outset;"
                                     "border-width:2px;"
                                     "border-radius:10px;"
                                     "border-color:beige;"
                                     "font:bold 18px;"
                                     "min-width: 5em;"
                                     "min-height: 2.5em;"
                                     "max-width: 5em;"
                                     "max-height: 2.5em;"
                                 "}");
    ui->label_5->setText(userEmail);

    QPixmap pixmap;
    pixmap.load(":/resource/4.png");
    ui->label->setGeometry(0,150,ui->tabWidget_2->width(),ui->tabWidget_2->height()-180);
    pixmap=pixmap.scaled(ui->label->width(),ui->label->height());   //图片与标签相适应，调整图片大小
    ui->label->setPixmap(pixmap);
    ui->lineEdit->setStyleSheet("QLineEdit{font:bold 45px;background-color: rgba(255, 255, 255, 0%);border:0px solid #b9babb;}");
    ui->lineEdit->setAlignment(Qt::AlignHCenter);
    ui->label_2->setGeometry(83.5,0,300,80);
    ui->label_2->setStyleSheet("QLabel{/*background-color:#89AFDE;*/font:bold 45px;}");    
    ui->label_2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->label_2->setText("");
    ui->tabWidget->setStyleSheet("QTabBar::tab{width:95.2}\nQTabBar::tab{height:40}");

    //设置15个拨号按钮的属性    
    ui->pushButton->setStyleSheet("QPushButton{border:0px;}");//将按钮的点击效果隐藏
    ui->pushButton->setFlat(true);//将按钮设为透明
    ui->pushButton_2->setStyleSheet("QPushButton{border:0px;}");//将按钮的点击效果隐藏
    ui->pushButton_2->setFlat(true);//将按钮设为透明
    ui->pushButton_3->setStyleSheet("QPushButton{border:0px;}");//将按钮的点击效果隐藏
    ui->pushButton_3->setFlat(true);//将按钮设为透明
    ui->pushButton_4->setStyleSheet("QPushButton{border:0px;}");//将按钮的点击效果隐藏
    ui->pushButton_4->setFlat(true);//将按钮设为透明
    ui->pushButton_5->setStyleSheet("QPushButton{border:0px;}");//将按钮的点击效果隐藏
    ui->pushButton_5->setFlat(true);//将按钮设为透明
    ui->pushButton_6->setStyleSheet("QPushButton{border:0px;}");//将按钮的点击效果隐藏
    ui->pushButton_6->setFlat(true);//将按钮设为透明
    ui->pushButton_7->setStyleSheet("QPushButton{border:0px;}");//将按钮的点击效果隐藏
    ui->pushButton_7->setFlat(true);//将按钮设为透明
    ui->pushButton_8->setStyleSheet("QPushButton{border:0px;}");//将按钮的点击效果隐藏
    ui->pushButton_8->setFlat(true);//将按钮设为透明
    ui->pushButton_9->setStyleSheet("QPushButton{border:0px;}");//将按钮的点击效果隐藏
    ui->pushButton_9->setFlat(true);//将按钮设为透明
    ui->pushButton_10->setStyleSheet("QPushButton{border:0px;}");//将按钮的点击效果隐藏
    ui->pushButton_10->setFlat(true);//将按钮设为透明
    ui->pushButton_11->setStyleSheet("QPushButton{border:0px;}");//将按钮的点击效果隐藏
    ui->pushButton_11->setFlat(true);//将按钮设为透明
    ui->pushButton_12->setStyleSheet("QPushButton{border:0px;}");//将按钮的点击效果隐藏
    ui->pushButton_12->setFlat(true);//将按钮设为透明
    ui->pushButton_13->setStyleSheet("QPushButton{border:0px;}");//将按钮的点击效果隐藏
    ui->pushButton_13->setFlat(true);//将按钮设为透明
    ui->pushButton_14->setStyleSheet("QPushButton{border:0px;}");//将按钮的点击效果隐藏
    ui->pushButton_14->setFlat(true);//将按钮设为透明
    ui->pushButton_15->setStyleSheet("QPushButton{border:0px;}");//将按钮的点击效果隐藏
    ui->pushButton_15->setFlat(true);//将按钮设为透明


    //设置15个按钮的信号和槽连接
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        qDebug()<<1;
        ui->lineEdit->setText(ui->lineEdit->text()+"1");
    });
    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        qDebug()<<2;
        ui->lineEdit->setText(ui->lineEdit->text()+"2");
    });
    connect(ui->pushButton_3,&QPushButton::clicked,[=](){
        qDebug()<<3;
        ui->lineEdit->setText(ui->lineEdit->text()+"3");
    });
    connect(ui->pushButton_4,&QPushButton::clicked,[=](){
        qDebug()<<4;
        ui->lineEdit->setText(ui->lineEdit->text()+"4");
    });
    connect(ui->pushButton_5,&QPushButton::clicked,[=](){
        qDebug()<<5;
        ui->lineEdit->setText(ui->lineEdit->text()+"5");
    });
    connect(ui->pushButton_6,&QPushButton::clicked,[=](){
        qDebug()<<6;
        ui->lineEdit->setText(ui->lineEdit->text()+"6");
    });
    connect(ui->pushButton_7,&QPushButton::clicked,[=](){
        qDebug()<<7;
        ui->lineEdit->setText(ui->lineEdit->text()+"7");
    });
    connect(ui->pushButton_8,&QPushButton::clicked,[=](){
        qDebug()<<8;
        ui->lineEdit->setText(ui->lineEdit->text()+"8");
    });
    connect(ui->pushButton_9,&QPushButton::clicked,[=](){
        qDebug()<<9;
        ui->lineEdit->setText(ui->lineEdit->text()+"9");
    });
    connect(ui->pushButton_10,&QPushButton::clicked,[=](){
        qDebug()<<'*';
        ui->lineEdit->setText(ui->lineEdit->text()+"*");
    });
    connect(ui->pushButton_11,&QPushButton::clicked,[=](){
        qDebug()<<0;
        ui->lineEdit->setText(ui->lineEdit->text()+"0");
    });
    connect(ui->pushButton_12,&QPushButton::clicked,[=](){
        qDebug()<<'#';
        ui->lineEdit->setText(ui->lineEdit->text()+"#");
    });
    connect(ui->pushButton_13,&QPushButton::clicked,[=](){
        qDebug()<<"返回通讯录";
        ui->tabWidget_2->setCurrentIndex(1);
        clickSound->play();
    });
    connect(ui->pushButton_14,&QPushButton::clicked,[=](){
        emit this->phoneBtnClicked();
    });
    connect(ui->pushButton_15,&QPushButton::clicked,[=](){
        qDebug()<<"删除";
        ui->lineEdit->setText(ui->lineEdit->text().remove(ui->lineEdit->text().length()-1,1));
        clickSound->play();
    });

    connect(this,&MainWindow::phoneBtnClicked,[=](){
        qDebug()<<"拨打电话";
        clickSound->play();
        if(ui->lineEdit->text()!="")
        {
            this->hide();
            call->newCall(ui->label_2->text(),ui->lineEdit->text());
        }
    });

    //文本框电话号码改变触发声音，并查询姓名
    connect(ui->lineEdit,&QLineEdit::textChanged,[=](QString callNumber){
        clickSound->play();
        ui->label_2->clear();

        int isFind=0;
        QString strName;
        QString strPhoneNumber;

        int i=0;
        qDebug()<<"正在搜索AddressBook1的电话";
        QFile file("AddressBook1.txt");
        file.open(QFile::ReadOnly);
        while(!file.atEnd()&&isFind==0)
        {
            i++;
            QString str=QTextCodec::codecForName("GBK")->toUnicode(file.readLine());

            if(i%8==1) strName=str;
            if(i%8==5) strPhoneNumber=str;
            if(strPhoneNumber==callNumber+"\n")
            {
                qDebug()<<"在AddressBook1中找到了相匹配的名字";
                ui->label_2->setText(strName.remove(strName.length()-1,1));
                qDebug()<<strName.toUtf8().data();
                isFind=1;
            }
        }
        file.close();

        i=0;
        qDebug()<<"正在搜索AddressBook2的电话";
        QFile file1("AddressBook2.txt");
        file1.open(QFile::ReadOnly);
        while(!file1.atEnd()&&isFind==0)
        {
            i++;
            QString str=QTextCodec::codecForName("GBK")->toUnicode(file1.readLine());

            if(i%8==1) strName=str;
            if(i%8==5) strPhoneNumber=str;
            if(strPhoneNumber==callNumber+"\n")
            {
                qDebug()<<"在AddressBook2中找到了相匹配的名字";
                ui->label_2->setText(strName.remove(strName.length()-1,1));
                qDebug()<<strName.toUtf8().data();
                isFind=1;
            }
        }
        file1.close();

        i=0;
        qDebug()<<"正在搜索AddressBook3的电话";
        QFile file2("AddressBook3.txt");
        file2.open(QFile::ReadOnly);
        while(!file2.atEnd()&&isFind==0)
        {
            i++;
            QString str=QTextCodec::codecForName("GBK")->toUnicode(file2.readLine());

            if(i%8==1) strName=str;
            if(i%8==5) strPhoneNumber=str;
            if(strPhoneNumber==callNumber+"\n")
            {
                qDebug()<<"在AddressBook3中找到了相匹配的名字";
                ui->label_2->setText(strName.remove(strName.length()-1,1));
                qDebug()<<strName.toUtf8().data();
                isFind=1;
            }
        }
        file2.close();

        i=0;
        qDebug()<<"正在搜索AddressBook4的电话";
        QFile file3("AddressBook4.txt");
        file3.open(QFile::ReadOnly);
        while(!file3.atEnd()&&isFind==0)
        {
            i++;
            QString str=QTextCodec::codecForName("GBK")->toUnicode(file3.readLine());

            if(i%8==1) strName=str;
            if(i%8==5) strPhoneNumber=str;
            if(strPhoneNumber==callNumber+"\n")
            {
                qDebug()<<"在AddressBook4中找到了相匹配的名字";
                ui->label_2->setText(strName.remove(strName.length()-1,1));
                qDebug()<<strName.toUtf8().data();
                isFind=1;
            }
        }
        file3.close();
    });

    //菜单栏的信号和槽
    //退出
    connect(ui->actionQuit,&QAction::triggered,[=](){this->close();});
    //新建
    connect(ui->actionNew,&QAction::triggered,[=](){
        //调整下拉框
        switch (ui->tabWidget->currentIndex()) {
        case 0:person->ui->comboBox->setCurrentIndex(0);
            person->ui->label_6->setText("称呼：");
            break;
        case 1:person->ui->comboBox->setCurrentIndex(1);
            break;
        case 2:person->ui->comboBox->setCurrentIndex(2);
            break;
        case 3:person->ui->comboBox->setCurrentIndex(3);
            break;
        default:
            break;
        }
        person->newPerson();
    });
    //排序
    connect(ui->actionSort,&QAction::triggered,[=](){
        this->sortOrder=(this->sortOrder>0)?0:1;
        updateRelative();
        updateFriend();
        updateClassmate();
        updateColleague();
    });
    //查找
    connect(ui->actionSearch,&QAction::triggered,[=](){
        this->hide();
        search->newSearch();
    });
    //生日提醒
    connect(ui->actionBirthdayReminder,&QAction::triggered,[=](){
        updateBirthdayListWidget(birthday->ui->spinBox_2->value());
        this->hide();
        birthday->newBirthday();
    });
    //注销
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
    //修改密码
    connect(ui->actionEditPassword,&QAction::triggered,[=](){

        QFile file("Password.txt");
        file.open(QFile::ReadOnly);
        QStringList strList=QTextCodec::codecForName("GBK")->toUnicode(file.readAll()).split("\n");
        file.close();
        register0->isOnEdit=1;
        QDate date(strList[1].toInt(),strList[2].toInt(),strList[3].toInt());
        register0->ui->lineEdit->setText(strList[0]);
        register0->ui->dateEdit->setDate(date);
        register0->ui->lineEdit_2->setText(strList[4]);
        register0->ui->lineEdit_3->setText(strList[5]);
        register0->ui->lineEdit_4->setText(strList[6]);
        register0->ui->lineEdit_5->setText(strList[6]);
        //令密码栏和再次确认密码栏为空
//        register0->ui->lineEdit_4->setText("");
//        register0->ui->lineEdit_5->setText("");
        register0->show();      
    });

    //生日提醒窗口关闭触发
    connect(birthday,&Birthday::birthdayClose,[=](){       
        this->show();
    });
    //生日界面月份框改变
    connect(birthday->ui->spinBox,static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int value){
        QString str;
        str.setNum(value);
        if(value<=9) str.prepend("0");
        search->ui->lineEdit->setText("."+str+".");
        str.setNum(search->ui->listWidget->count());
        birthday->ui->label_2->setText(str+"人");
        search->ui->lineEdit->clear();
        search->ui->listWidget->clear();
    });
    //生日界面天数范围框改变
    connect(birthday->ui->spinBox_2,static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int value){
        updateBirthdayListWidget(value);
    });

    //点击生日界面listWidgetItem触发
    connect(birthday,&Birthday::itemClicked,[=](QListWidgetItem *item){
        if(item->text().contains("称呼",Qt::CaseInsensitive))
        msgBoxUnit("AddressBook1.txt",item);
        if(item->text().contains("地点",Qt::CaseInsensitive))
        msgBoxUnit("AddressBook2.txt",item);
        if(item->text().contains("学校",Qt::CaseInsensitive))
        msgBoxUnit("AddressBook3.txt",item);
        if(item->text().contains("单位",Qt::CaseInsensitive))
        msgBoxUnit("AddressBook4.txt",item);       
    });


    //搜索窗口关闭触发
    connect(search,&Search::searchClose,[=](){
        this->show();
    });

    //搜索内容发生变化触发
    connect(search->ui->lineEdit,&QLineEdit::textChanged,[=](QString searchText){
        search->ui->listWidget->clear();
        if(searchText!="")
        {
            QStringList strList;
            for(int i=0;i<ui->listWidget_5->count();i++)
            {
                if(ui->listWidget_5->item(i)->text().contains(searchText,Qt::CaseInsensitive))
                {
                    strList<<ui->listWidget_5->item(i)->text();
                }
            }
            search->ui->listWidget->setIconSize(QSize(110,110));

            for(int i=0;i<strList.size();i++)
            {              
                QString content=strList[i];
                QStringList strList0=content.split("\n");
                QString itemName=strList0[0];
                itemName=itemName.remove(0,3);
                QListWidgetItem * item = new QListWidgetItem(QIcon(headPath->searchHeadPath(itemName)),content);
                item->setFont(QFont("华文宋体",10));
                search->ui->listWidget->addItem(item);
            }
        }
    });

    connect(search,&Search::itemClicked,[=](QListWidgetItem *item){
        if(item->text().contains("称呼",Qt::CaseInsensitive))
        msgBoxUnit("AddressBook1.txt",item);
        if(item->text().contains("地点",Qt::CaseInsensitive))
        msgBoxUnit("AddressBook2.txt",item);
        if(item->text().contains("学校",Qt::CaseInsensitive))
        msgBoxUnit("AddressBook3.txt",item);
        if(item->text().contains("单位",Qt::CaseInsensitive))
        msgBoxUnit("AddressBook4.txt",item);
    });


    //person类中的信号触发listWidget更新列表
    connect(person,&CreateNew::updateRelativeList,[=](){
        this->ui->listWidget->clear();
        this->updateRelative();
    });
    connect(person,&CreateNew::updateFriendList,[=](){
        this->ui->listWidget_2->clear();
        this->updateFriend();
    });
    connect(person,&CreateNew::updateClassmateList,[=](){
        this->ui->listWidget_3->clear();
        this->updateClassmate();
    });
    connect(person,&CreateNew::updateColleagueList,[=](){
        this->ui->listWidget_4->clear();
        this->updateColleague();
    });


    connect(person->ui->newConfirmBtn,&QPushButton::clicked,[=](){
        if(this->globalPath!="")
        {
            discardPerson(globalPath,globalItemName);

            if(globalPath=="AddressBook1.txt")
            {
                updateRelative();
            }
            if(globalPath=="AddressBook2.txt")
            {
                updateFriend();
            }
            if(globalPath=="AddressBook3.txt")
            {
                updateClassmate();
            }
            if(globalPath=="AddressBook4.txt")
            {
                updateColleague();
            }
            globalPath="";
            globalItemName="";
        }
    });

    connect(call,&Call::hangUpBtnClicked,[=](){
        this->show();
    });

    //发送邮件按钮
    connect(ui->pushButton_16,&QPushButton::clicked,[=](){
        if(ui->lineEdit_2->text()==""||ui->textEdit->toPlainText()=="")
        {
            QMessageBox msgBox;
            msgBox.setText(tr("收件邮箱和邮件内容不能为空！"));
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setStandardButtons(QMessageBox::Ok);
            int ret = msgBox.exec();
            qDebug()<<"点击了ok"<<ret;

        }
        else
        {
            email->senderEmail=ui->label_5->text();
            email->receiverEmail=ui->lineEdit_2->text();
            email->emailMessage=ui->textEdit->toPlainText();
            inputEP->show();           
        }
    });

    ui->lineEdit->installEventFilter(this);
    ui->lineEdit_2->installEventFilter(this);
    ui->textEdit->viewport()->installEventFilter(this);

    connect(asrMainWindow,&ASR::outputASR,[=](QString ASRtext){
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
            if(onTextEdit==1)
            {
                QTextCursor cursor0=ui->textEdit->textCursor();
                cursor0.insertText(ASRtext);
                ui->textEdit->setFocus();
            }
        });
    
    connect(inputEP,&InputEmailPassword::emailPasswordBtnClicked,[=](QString emailPassword){
        QFile file("EmailPassword.txt");
        file.open(QFile::WriteOnly|QIODevice::Truncate);
        QTextStream out(&file);
        out<<emailPassword;
        file.close();
        
        qDebug()<<ui->textEdit->placeholderText();
        //打开发送邮件界面
        email->newEmail(ui->lineEdit_2->text(),userEmail);
    });

    //搜索窗口关闭触发
    connect(mess,&Messdemo::messdemoClose,[=](){
        this->show();
    });

    updateRelative();
    updateFriend();
    updateClassmate();
    updateColleague();
    updateAll();

}

MainWindow::~MainWindow()
{
    delete ui;
}

//当用户添加/删除/编辑联系人后，将会根据txt文件内容更新联系人列表
void MainWindow::updateUnit(QString path,int index)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    int i=0;
    QString str;
    QString strName;
    QString content;

    while(!file.atEnd())
    {
        QString str0=QTextCodec::codecForName("GBK")->toUnicode(file.readLine());
        i++;
        if(i%8==1)
        {
            strName=str0;
            if(sortOrder==0)
                str+="姓名："+strName;
        }
        if(i%8==2)
        {
            str+="日期：";
            str+=str0;
            str.remove(str.length()-1,1);
            str+=".";
        }
        if(i%8==3)
        {
            str+=str0;
            str.remove(str.length()-1,1);
            str+=".";
        }
        if(i%8==4)
        {
            str+=str0;
            if(sortOrder==1) str+="姓名："+strName;
        }
        if(i%8==5)
        {
            str+="电话：";
            str+=str0;
        }
        if(i%8==6)
        {
            str+="邮件：";
            str+=str0;
        }
        if(i%8==7)
        {
            if(path=="AddressBook1.txt") str+="称呼：";
            if(path=="AddressBook2.txt") str+="地点：";
            if(path=="AddressBook3.txt") str+="学校：";
            if(path=="AddressBook4.txt") str+="单位：";
            str+=str0;
            str+="_______________________________________";
            content=str;
        }
        if(i%8==0)
        {
            QListWidgetItem * item = new QListWidgetItem(QIcon(str0.remove(str0.length()-1,1)),content);
            item->setFont(QFont("华文宋体",10));
            if(index==0)
            {
                if(path=="AddressBook1.txt")
                {
                    ui->listWidget->addItem(item);
                }
                if(path=="AddressBook2.txt")
                {
                    ui->listWidget_2->addItem(item);
                }
                if(path=="AddressBook3.txt")
                {
                    ui->listWidget_3->addItem(item);
                }
                if(path=="AddressBook4.txt")
                {
                    ui->listWidget_4->addItem(item);
                }
            }
            else
            {
                ui->listWidget_5->addItem(item);
            }

            str.clear();
            content.clear();
            strName.clear();
        }
    }
    file.close();

}
//当用户添加/删除/编辑亲戚联系人后，将会根据AddressBook1.txt文件内容更新亲戚列表
void MainWindow::updateRelative()
{
    ui->listWidget->setIconSize(QSize(110,110));
    ui->listWidget->clear();
    updateUnit("AddressBook1.txt");

    //姓名或时间排序
    ui->listWidget->sortItems(Qt::AscendingOrder);
    qDebug()<<"亲戚列表更新成功！";

    updateAll();
}

//当用户添加/删除/编辑朋友联系人后，将会根据AddressBook2.txt文件内容更新朋友列表
void MainWindow::updateFriend()
{
    ui->listWidget_2->setIconSize(QSize(110,110));
    ui->listWidget_2->clear();
    updateUnit("AddressBook2.txt");

    //姓名或时间排序
    ui->listWidget_2->sortItems(Qt::AscendingOrder);
    qDebug()<<"朋友列表更新成功！";

    updateAll();
}

//当用户添加/删除/编辑同学联系人后，将会根据AddressBook3.txt文件内容更新同学列表
void MainWindow::updateClassmate()
{
    ui->listWidget_3->setIconSize(QSize(110,110));
    ui->listWidget_3->clear();
    updateUnit("AddressBook3.txt");

    //姓名或时间排序
    ui->listWidget_3->sortItems(Qt::AscendingOrder);
    qDebug()<<"同学列表更新成功！";

    updateAll();
}

//当用户添加/删除/编辑同事联系人后，将会根据AddressBook4.txt文件内容更新同事列表
void MainWindow::updateColleague()
{
    ui->listWidget_4->setIconSize(QSize(110,110));
    ui->listWidget_4->clear();
    updateUnit("AddressBook4.txt");

    //姓名或时间排序
    ui->listWidget_4->sortItems(Qt::AscendingOrder);
    qDebug()<<"同事列表更新成功！";

    updateAll();
}

//调用updateUnit函数更新5个联系人列表
void MainWindow::updateAll()
{
    ui->listWidget_5->setIconSize(QSize(110,110));
    ui->listWidget_5->clear();

    updateUnit("AddressBook1.txt",1);
    updateUnit("AddressBook2.txt",1);
    updateUnit("AddressBook3.txt",1);
    updateUnit("AddressBook4.txt",1);

    //姓名或时间排序
    ui->listWidget_5->sortItems(Qt::AscendingOrder);
    qDebug()<<"所有联系人列表更新成功！";
}

//亲戚联系人列表控件点击函数
void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{
    int currentRow = ui->listWidget->currentRow();//当前单击选中ListWidget控件的行号（第几行）
    qDebug()<<currentRow;//将这个行号显示
    qDebug()<<index;
    QListWidgetItem *item=ui->listWidget->item(currentRow);
    msgBoxUnit("AddressBook1.txt",item);


}

//朋友联系人列表控件点击函数
void MainWindow::on_listWidget_2_clicked(const QModelIndex &index)
{
    int currentRow = ui->listWidget_2->currentRow();//当前单击选中ListWidget2控件的行号（第几行）
    qDebug()<<currentRow;//将这个行号显示
    qDebug()<<index;
    QListWidgetItem *item=ui->listWidget_2->item(currentRow);
    msgBoxUnit("AddressBook2.txt",item);

}

//同学联系人列表控件点击函数
void MainWindow::on_listWidget_3_clicked(const QModelIndex &index)
{
    int currentRow = ui->listWidget_3->currentRow();//当前单击选中ListWidget3控件的行号（第几行）
    qDebug()<<currentRow;//将这个行号显示
    qDebug()<<index;
    QListWidgetItem *item=ui->listWidget_3->item(currentRow);
    msgBoxUnit("AddressBook3.txt",item);
}

//同事联系人列表控件点击函数
void MainWindow::on_listWidget_4_clicked(const QModelIndex &index)
{
    int currentRow = ui->listWidget_4->currentRow();//当前单击选中ListWidget4控件的行号（第几行）
    qDebug()<<currentRow;//将这个行号显示
    qDebug()<<index;
    QListWidgetItem *item=ui->listWidget_4->item(currentRow);
    msgBoxUnit("AddressBook4.txt",item);
}

//所有联系人列表控件点击函数
void MainWindow::on_listWidget_5_clicked(const QModelIndex &index)
{
    int currentRow = ui->listWidget_5->currentRow();//当前单击选中ListWidget5控件的行号（第几行）
    qDebug()<<currentRow;//将这个行号显示
    qDebug()<<index;

    int isFind=0;
    for(int i=0;i<ui->listWidget->count()&&isFind==0;i++)
        {
            QListWidgetItem *item=ui->listWidget->item(i);
            if(item->text()==ui->listWidget_5->currentItem()->text())
            {
                isFind=1;
                qDebug()<<"列表5在列表1中找到了匹配";
                msgBoxUnit("AddressBook1.txt",item);
            }
        }

    for(int i=0;i<ui->listWidget_2->count()&&isFind==0;i++)
    {
        QListWidgetItem *item=ui->listWidget_2->item(i);
        if(item->text()==ui->listWidget_5->currentItem()->text())
        {
            isFind=1;
            qDebug()<<"列表5在列表2中找到了匹配";
            msgBoxUnit("AddressBook2.txt",item);
        }
    }

    for(int i=0;i<ui->listWidget_3->count()&&isFind==0;i++)
    {
        QListWidgetItem *item=ui->listWidget_3->item(i);
        if(item->text()==ui->listWidget_5->currentItem()->text())
        {
            isFind=1;
            qDebug()<<"列表5在列表3中找到了匹配";
            msgBoxUnit("AddressBook3.txt",item);
        }
    }

    for(int i=0;i<ui->listWidget_4->count()&&isFind==0;i++)
    {
        QListWidgetItem *item=ui->listWidget_4->item(i);
        if(item->text()==ui->listWidget_5->currentItem()->text())
        {
            isFind=1;
            qDebug()<<"列表5在列表4中找到了匹配";
            msgBoxUnit("AddressBook4.txt",item);
        }
    }
}

//弹出联系人（删除/编辑/电话/邮件选择框）
void MainWindow::msgBoxUnit(QString path,QListWidgetItem *item)
{        
    QMessageBox msgBox;
    msgBox.setText(item->text());
    QString itemName;
    QString itemDate;
    QString itemPhoneNumber;
    QString itemEmail;
    QString itemFifth;
    QString itemHead;

    QStringList itemStr=item->text().split("\n");

    itemName=itemStr[0].remove(0,3);
    itemDate=itemStr[1].remove(0,3);
    itemPhoneNumber=itemStr[2].remove(0,3);
    itemEmail=itemStr[3].remove(0,3);
    itemFifth=itemStr[4].remove(0,3);
    if(sortOrder==1)
    {
        QString str0=itemName;
        itemName=itemDate;
        itemDate=str0;
    }
//    headPath->searchHeadPath(itemName);
//    itemHead=headPath->itemHeadPath;
    itemHead=headPath->searchHeadPath(itemName);

    msgBox.setStandardButtons(QMessageBox::Cancel);
    msgBox.button(QMessageBox::Cancel)->setText("取消");
    QPushButton *discardBtn=msgBox.addButton(tr("删除"),QMessageBox::ActionRole);
    QPushButton *editBtn=msgBox.addButton(tr("编辑"),QMessageBox::ActionRole);
    QPushButton *phoneBtn=msgBox.addButton(tr("电话"),QMessageBox::ActionRole);
    QPushButton *emailBtn=msgBox.addButton(tr("邮件"),QMessageBox::ActionRole);
    QPushButton *messageBtn=msgBox.addButton(tr("短信"),QMessageBox::ActionRole);

    //设置消息对话框按钮的标签的样式
    msgBox.setStyleSheet(
                "QPushButton{"
                    "background-color:#89AFDE;"
                    "border-style:outset;"
                    "border-width:2px;"
                    "border-radius:10px;"
                    "border-color:beige;"
                    "font:bold 18px;"
                    "min-width: 4em;"
                    "min-height: 3em;"
                    "max-width: 4em;"
                    "max-height: 3em;"
                "}"
                "QLabel{"
                    "font: 24px;"
                    "background-color:#ffffff;"
                "}"
            );

    int ret=msgBox.exec();
    if(msgBox.clickedButton()==discardBtn)
    {
        //删除联系人
        if(path=="AddressBook1.txt")
        {
            discardPerson("AddressBook1.txt",itemName);
            updateRelative();
        }
        if(path=="AddressBook2.txt")
        {
            discardPerson("AddressBook2.txt",itemName);
            updateFriend();
        }
        if(path=="AddressBook3.txt")
        {
            discardPerson("AddressBook3.txt",itemName);
            updateClassmate();
        }
        if(path=="AddressBook4.txt")
        {
            discardPerson("AddressBook4.txt",itemName);
            updateColleague();
        }

    }

    if(msgBox.clickedButton()==editBtn)
    {
        QStringList str0=itemDate.split(".");
        QString year1=str0[0];
        QString month1=str0[1];
        QString day1=str0[2];
        QDate date(year1.toInt(),month1.toInt(),day1.toInt());

        person->ui->lineEdit->setText(itemName);
        person->ui->dateEdit->setDate(date);
        person->ui->lineEdit_2->setText(itemPhoneNumber);
        person->ui->lineEdit_3->setText(itemEmail);
        person->ui->lineEdit_4->setText(itemFifth);
        person->ui->lineEdit_5->setText(itemHead);

        if(path=="AddressBook1.txt")
        {
            //下拉框调整为亲戚
            person->ui->comboBox->setCurrentIndex(0);
            person->ui->label_6->setText("称呼：");
        }
        if(path=="AddressBook2.txt")
        {
            //下拉框调整为朋友
            person->ui->comboBox->setCurrentIndex(1);
            person->ui->label_6->setText("地点：");
        }
        if(path=="AddressBook3.txt")
        {
            //下拉框调整为亲戚
            person->ui->comboBox->setCurrentIndex(2);
            person->ui->label_6->setText("学校：");
        }
        if(path=="AddressBook4.txt")
        {
            //下拉框调整为亲戚
            person->ui->comboBox->setCurrentIndex(3);
            person->ui->label_6->setText("单位：");
        }

        //先新建后删除旧联系人（原始联系信息）
        person->newPerson();
        //以名字为索引在globalpath文件中删除旧联系人（原始联系信息）
        globalPath=path;
        globalItemName=itemName;
    }

    if(msgBox.clickedButton()==phoneBtn)
    {
        qDebug()<<"电话";
        ui->tabWidget_2->setCurrentIndex(0);
        ui->lineEdit->setText(itemPhoneNumber);
    }

    if(msgBox.clickedButton()==emailBtn)
    {
        qDebug()<<"邮件";
        ui->tabWidget_2->setCurrentIndex(2);
        ui->lineEdit_2->setText(itemEmail);
        ui->textEdit->setText(itemName+":\n    祝生日快乐，健康幸福。"+"\n                       "+userName);
    }

    if(msgBox.clickedButton()==messageBtn)
    {
        qDebug()<<"短信";
        mess->ui->label_3->setText(userPhoneNumber);
        mess->ui->lineEdit->setText(itemPhoneNumber);
        mess->ui->textEdit->setText(itemName+":\n    祝生日快乐，健康幸福。\n                        "+userName+"\n                    "+userPhoneNumber);
        this->close();
        mess->show();
    }

    if(ret==QMessageBox::Cancel)
    {
        qDebug()<<"取消";
    }
}

//删除path文件下名字为itemName的联系人
void MainWindow::discardPerson(QString path,QString itemName)
{
    QFile file(path);
    file.open(QFile::ReadOnly);
    QStringList strlist;
    int i=0;
    int isFirst=0;
    while(!file.atEnd())
    {
        QString str=QTextCodec::codecForName("GBK")->toUnicode(file.readLine());

        if(str==itemName+"\n")
        {
            i=1;
            isFirst++;
        }
        if(i<1||i>8||isFirst>1)  //（isFirst>1）解决了误删刚刚编辑的联系人信息的bug
        {
            strlist<<str;
        }
        else
        {
            i++;
        }

    }
    file.close();

    QFile file1(path);
    file1.open(QFile::WriteOnly|QIODevice::Truncate);
    QTextStream out(&file1);
    for(int j=0;j<strlist.size();j++)
    {
        out<<strlist[j].toUtf8();
    }
    file1.close();

}

//更新生日列表
void MainWindow::updateBirthdayListWidget(int value)
{
    birthday->ui->listWidget->clear();
    QDate date=QDate::currentDate();
    QString str;
    QString str1;
    for(int i=0;i<value;i++)
    {
        int month=date.month();
        int day=date.day();
        str1.setNum(month);
        if(month<=9) str1.prepend("0");
        str+="."+str1+".";
        str1.setNum(day);
        if(day<=9) str1.prepend("0");
        str+=str1;
        search->ui->lineEdit->setText(str);
        for(int j=0;j<search->ui->listWidget->count();j++)
        {
            QListWidgetItem *item=search->ui->listWidget->item(j);
            QStringList strList=item->text().split("\n");
            strList[1]+="("+date.toString("dddd")+")";
            QString itemName=strList[0];
            itemName=itemName.remove(0,3);
            QListWidgetItem * item1 = new QListWidgetItem(QIcon(headPath->searchHeadPath(itemName)),strList.join("\n"));
            item1->setFont(QFont("华文宋体",10));
            birthday->ui->listWidget->addItem(item1);
        }
        date=date.addDays(1);
        str.clear();
    }
    search->ui->lineEdit->clear();
    search->ui->listWidget->clear();
}

//键盘按键事件，Esc：退出程序，F2：语音输入
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //响应Esc键退出程序
    if(event->key()==Qt::Key_Escape)
    {
        qDebug()<<"退出当前界面";
        this->close();
    }
    //按enter拨打电话
    if(event->key()==Qt::Key_Enter||event->key()==Qt::Key_Return)
    {
        qDebug()<<"按了enter键以拨打电话";
        emit this->phoneBtnClicked();
    }
    if(event->key()==Qt::Key_F2)
    {
        if(asrMainWindow->isStop==1)
        {
            asrMainWindow->startASR();
        }
        else
        {
            asrMainWindow->stopASR();
        }
    }
}

//事件过滤器，若当前触发鼠标点击事件且对象为某一文本框，则令该文本框成为语音输入对象
bool MainWindow::eventFilter(QObject *obj, QEvent *e)
{
    if(e->type()==QEvent::MouseButtonPress)
        {
            if(obj == ui->lineEdit)
            {
                onLineEdit1=1;
                onLineEdit2=0;
                onTextEdit=0;
            }
            if(obj == ui->lineEdit_2)
            {
                onLineEdit1=0;
                onLineEdit2=1;
                onTextEdit=0;
            }
            if(obj == ui->textEdit->viewport())
            {
                onLineEdit1=0;
                onLineEdit2=0;
                onTextEdit=1;
            }
        }
        return QMainWindow::eventFilter(obj,e);
}
