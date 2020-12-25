//功能：添加亲戚联系人；继承了CreatNew类
#ifndef ADDRELATIVE_H
#define ADDRELATIVE_H

#include"createnew.h"

class AddRelative:public CreateNew
{
public:
    AddRelative(QString name1,QString phoneNumber1,QString email1,QString fifth1,QString year1,QString month1,QString day1,QString head1);
};
#endif // ADDRELATIVE_H
