//功能：UI文件显示授权码输入窗口，输入邮箱SMTP服务授权码（不是邮箱密码），方能在第三方客户端发送邮件
//开通QQ邮箱的SMTP服务教程：https://jingyan.baidu.com/article/5225f26b017159e6fa0908ff.html
#ifndef INPUTEMAILPASSWORD_H
#define INPUTEMAILPASSWORD_H

#include <QMainWindow>
#include<QKeyEvent>
#include<QEvent>
#include"asr.h"

namespace Ui {
class InputEmailPassword;
}

class InputEmailPassword : public QMainWindow
{
    Q_OBJECT

public:
    ASR *asrInputEP=new ASR;
    explicit InputEmailPassword(QWidget *parent = 0);
    ~InputEmailPassword();
    QString emailPassword;

    void keyPressEvent(QKeyEvent *event);
signals:
    void emailPasswordBtnClicked(QString emailPassword0);
    void btnClicked();

private:
    Ui::InputEmailPassword *ui;
};

#endif // INPUTEMAILPASSWORD_H
