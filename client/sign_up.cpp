#include "sign_up.h"
#include "ui_sign_up.h"
#include "iostream"
#include "mainwindow.h"

using namespace std;

Sign_up::Sign_up(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sign_up)
{
    ui->setupUi(this);
    setFixedSize(340,290);
    ui->name->setAttribute(Qt::WA_InputMethodEnabled, false);//不能输中文
    ui->user_id->setAttribute(Qt::WA_InputMethodEnabled, false);
    ui->user_password->setAttribute(Qt::WA_InputMethodEnabled, false);
    setWindowFlags(Qt::FramelessWindowHint);//Qt::FramelessWindowHint设置窗口标志为无边框
    ui->pushButton->setStyleSheet(tr("QPushButton{background:transparent}QPushButton{border-style:none}QPushButton:hover{background-color:red;}"));
}

Sign_up::~Sign_up()
{
    delete ui;
}

void Sign_up::on_Button_finishsignup_clicked()
{
    if(ui->user_id->text().isEmpty() & ui->user_password->text().isEmpty() || ui->user_id->text().isEmpty() || ui->user_password->text().isEmpty()){
        QMessageBox::warning(this,"警告","账号或密码不能为空！");
    }
    else{
        SOCKET sock_=socketconnect();
        if(sock_!=0){
            cout<<sock_<<endl;
            QString name,user,password;
            name=ui->name->text().toLatin1();
            user=ui->user_id->text();
            password=ui->user_password->text();

            Alldata alldata;
            alldata.type='1';
            memcpy(alldata.Username,name.toStdString().c_str(),name.length());
            memcpy(alldata.UserID,user.toStdString().c_str(),user.length());
            memcpy(alldata.UserPassword,password.toStdString().c_str(),password.length());
            cout<<alldata.Username<<"   "<<alldata.UserID<<"   "<<alldata.UserPassword<<endl;
            int needSend = sizeof(Alldata);
            char *sendMsg = (char*)malloc(needSend);
            memcpy(sendMsg, &alldata, needSend);
            int pos = 0;
            int len = 0;
            while (pos < needSend) {
                len = send(sock_, sendMsg + pos, needSend, 0);
                if (len <= 0) {
                    perror("ERRPR");
                    break;
                }
                pos += len;
            }
            free(sendMsg);

            int needRecv = sizeof(Alldata);
            char *recvMsg = (char*)malloc(needRecv);
            pos = 0;
            while (pos < needRecv) {
                len = recv(sock_, recvMsg + pos, needRecv, 0);
                if (len < 0) {
                    cout << "Recieve Data Failed!" << endl;
                    break;
                }
                pos += len;
            }
            memcpy(&alldata, recvMsg, sizeof(Alldata));
            free(recvMsg);
            //send(sock,(char*)&alldata,sizeof(Alldata),0);

            if(alldata.signup_type=='Y') {
                QMessageBox::information(this,"提示","注册成功，赶紧冲浪吧！！！！");
                closesocket(sock_);
                this->close();
            }
            if(alldata.signup_type=='N') {
                QMessageBox::information(this,"提示","对不起哦，这个昵称已经有人注册过了QAQ");
                closesocket(sock_);
            }
            if(alldata.signup_type=='I') {
                QMessageBox::information(this,"提示","对不起哦，这个帐号已经有人注册过了QAQ");
                closesocket(sock_);
            }
            if(alldata.signup_type=='A') {
                QMessageBox::information(this,"提示","对不起哦，帐号和密码都被别人注册了QAQ");
                closesocket(sock_);
            }
        }
        else{
            QMessageBox::information(this,"提示","Please try again.");
        }
    }

}

void Sign_up::on_pushButton_clicked()
{
    this->close();
}

// 鼠标左键触发
void Sign_up::mousePressEvent(QMouseEvent *event){

    // 判断鼠标左键
    if(event->button() == Qt::LeftButton){

        // 求坐标差值, 具体分析放后面
        coordinate = event->globalPos() - this->frameGeometry().topLeft();
    }

}

// 鼠标移动触发
void Sign_up::mouseMoveEvent(QMouseEvent *event){

    // 判断左键(Qt::LeftButton)是否被按下, 只有按下了才返回1(true)
    if(event->buttons() & Qt::LeftButton){

        // 移动窗口
        move(event->globalPos() - coordinate);

    }

}
