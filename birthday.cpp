#include "birthday.h"
#include "ui_birthday.h"

#include<QDebug>
#include<QDate>
#include<QStringList>
#include<QString>
#include<QListWidget>
#include<QListWidgetItem>

Birthday::Birthday(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Birthday)
{
    ui->setupUi(this);
    this->setFixedSize(467,729);
    this->setWindowIcon(QPixmap(":/resource/9.png"));
    this->setWindowTitle("生日提醒");
    this->setStyleSheet("QWidget{background-color:#fde8f9;}");
    //模态窗口
    this->setAttribute(Qt::WA_ShowModal, true);    
//    this->ui->lineEdit->setStyleSheet("QLineEdit{font:24px;color:#edf439;}");

    ui->spinBox->setMaximum(12);
    ui->spinBox->setMinimum(1);
    ui->spinBox_2->setMaximum(31);
    ui->spinBox_2->setMinimum(0);
    ui->listWidget->setIconSize(QSize(110,110));
}

Birthday::~Birthday()
{
    delete ui;
}

//打开生日界面，并进行初始化
void Birthday::newBirthday()
{
    qDebug()<<"生日界面打开成功！";
    QDate date=QDate::currentDate();
    ui->spinBox->setValue(date.month());
    ui->spinBox_2->setValue(5);
    this->show();
}

//当生日界面关闭时，发射birthdayClose()信号,令mianwindow界面出现
void Birthday::closeEvent(QCloseEvent *event)
{
    qDebug()<<event<<"生日提醒界面窗口关闭";
    emit this->birthdayClose();
}

//最近生日联系人列表控件点击函数
void Birthday::on_listWidget_clicked(const QModelIndex &index)
{
    int currentRow = ui->listWidget->currentRow();//当前单击选中ListWidget控件的行号（第几行）
    qDebug()<<currentRow;//将这个行号显示
    qDebug()<<index;

    QListWidgetItem *item=ui->listWidget->item(currentRow);
    QStringList strList=item->text().split("\n");
    strList[1]=strList[1].remove(strList[1].length()-5,5);
    qDebug()<<strList[1];
    item->setText(strList.join("\n"));
    qDebug()<<item->text();
    this->close();
    emit this->itemClicked(item);
}
