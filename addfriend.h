//功能：添加朋友联系人；继承了CreatNew类
#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include"createnew.h"

class AddFriend:public CreateNew
{
public:
    AddFriend(QString name1,QString phoneNumber1,QString email1,QString fifth1,QString year1,QString month1,QString day1,QString head1);
};
#endif // ADDFRIEND_H
