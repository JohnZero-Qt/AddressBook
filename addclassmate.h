//功能：添加同学联系人；继承了CreatNew类
#ifndef ADDCLASSMATE_H
#define ADDCLASSMATE_H

#include"createnew.h"

class AddClassmate:public CreateNew
{
public:
    AddClassmate(QString name1,QString phoneNumber1,QString email1,QString fifth1,QString year1,QString month1,QString day1,QString head1);
};
#endif // ADDCLASSMATE_H
