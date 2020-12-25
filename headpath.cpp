#include "headpath.h"
#include<QDebug>
#include<QFile>
#include<QTextCodec>

HeadPath::HeadPath()
{

}

QString HeadPath::searchHeadPath(QString itemName)
{
    int isFind=0;
    int wait=0;
    QString strHead;
    int i=0;
    qDebug()<<"正在搜索AddressBook1的电话";
    QFile file("AddressBook1.txt");
    file.open(QFile::ReadOnly);
    while(!file.atEnd()&&isFind==0)
    {
        i++;
        QString str=QTextCodec::codecForName("GBK")->toUnicode(file.readLine());

        if(i%8==1&&str==itemName+"\n")
        {
            wait=1;
        }
        if(i%8==0&&wait==1)
        {
            strHead=str;
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

        if(i%8==1&&str==itemName+"\n")
        {
            wait=1;
        }
        if(i%8==0&&wait==1)
        {
            strHead=str;
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

        if(i%8==1&&str==itemName+"\n")
        {
            wait=1;
        }
        if(i%8==0&&wait==1)
        {
            strHead=str;
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

        if(i%8==1&&str==itemName+"\n")
        {
            wait=1;
        }
        if(i%8==0&&wait==1)
        {
            strHead=str;
            isFind=1;
        }
    }
    file3.close();

//    itemHeadPath=strHead.remove(strHead.length()-1,1);
    return strHead.remove(strHead.length()-1,1);
}
