#include "addcolleague.h"

#include "createnew.h"
#include<QFile>
#include<QDebug>

AddColleague::AddColleague(QString name1,QString phoneNumber1,QString email1,QString fifth1,QString year1,QString month1,QString day1,QString head1):CreateNew()
{
    name=name1;
    phoneNumber=phoneNumber1;
    email=email1;
    fifth=fifth1;
    year=year1;
    month=month1;
    day=day1;
    head=head1;

    QFile file("AddressBook4.txt");
    if(file.open(QFile::WriteOnly|QIODevice::Append))
    {
        QTextStream out(&file);
        out<<name.toUtf8()<<"\n";
        out<<year<<"\n";
        out<<month<<"\n";
        out<<day<<"\n";
        out<<phoneNumber.toUtf8()<<"\n";
        out<<email.toUtf8()<<"\n";
        out<<fifth.toUtf8()<<"\n";
        if(head=="") out<<":/resource/1.jpg"<<"\n";
        else out<<head.toUtf8()<<"\n";
        file.close();
        qDebug()<<"打开文本4成功";
    }
}

