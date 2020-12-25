//功能：添加同事联系人；继承了CreatNew类
#ifndef ADDCOLLEAGUE_H
#define ADDCOLLEAGUE_H

#include"createnew.h"

class AddColleague:public CreateNew
{
public:
    AddColleague(QString name1,QString phoneNumber1,QString email1,QString fifth1,QString year1,QString month1,QString day1,QString head1);
};
#endif // ADDCOLLEAGUE_H
