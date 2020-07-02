#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

#include <QVBoxLayout>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll

//调用WIN API需要用到的头文件与库 [实现缩放]
#ifdef Q_OS_WIN
#include <qt_windows.h>
#include <windows.h>
#include <Windowsx.h>
#endif

#define BUFFER_SIZE 1024
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(280,400);
    setWindowFlags(Qt::FramelessWindowHint);//Qt::FramelessWindowHint设置窗口标志为无边框
    ui->exit_pushButton->setStyleSheet(tr("QPushButton{background:transparent}QPushButton{border-style:none}QPushButton:hover{background-color:red;}"));
    ui->user_text->setAttribute(Qt::WA_InputMethodEnabled, false);//屏蔽输入法
    ui->password_text->setAttribute(Qt::WA_InputMethodEnabled, false);
    ui->signin->setShortcut(Qt::Key_Return);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_signin_clicked()
{

    if((ui->user_text->text().isEmpty() & ui->password_text->text().isEmpty() || ui->user_text->text().isEmpty() || ui->password_text->text().isEmpty())){
        QMessageBox::warning(this,"警告","账号或密码不可为空！");
    }
    else{
        SOCKET sock=socketconnect();
        QString user,password;
        user=ui->user_text->text();//获取账号框里面的内容
        password=ui->password_text->text();//获取密码框里面的内容

        Alldata alldata;
        alldata.type='2';
        memcpy(alldata.UserID,user.toStdString().c_str(),user.length());
        memcpy(alldata.UserPassword,password.toStdString().c_str(),password.length());
        send(sock,(char*)&alldata,sizeof(Alldata),0);

        int needRecv=sizeof(Alldata);
        char *recvMsg = (char*)malloc(needRecv);
        int pos=0;
        int len;
        while(pos<needRecv){
            len=recv(sock,recvMsg+pos,needRecv,0);
            if(len<0){
                cout<<"Recieve Data Failed!"<<endl;
                break;
            }
            pos+=len;
        }
        memcpy(&alldata,recvMsg,sizeof(Alldata));
        free(recvMsg);
        thisname=alldata.Username;
        thisID=alldata.UserID;
        /*fstream file;
        file.open("useronline.txt",ios::binary|ios::out);
        file.write(alldata.fileData,alldata.length);
        cout<<"Receive File Successful!"<<endl;*/


        if(alldata.judge=='Y'){
            QMessageBox::information(this,"提示","Login successfully!");
            this->close();//关闭当前登录界面
            chattable *chat_table = new chattable();
            chat_table->show();//打开子界面_聊天界面
        }
        else if(alldata.judge=='N'){
            QMessageBox::information(this,"提示","Please try again.");
        }
    }


}


void MainWindow::on_pushButton_signup_clicked()
{
    Sign_up *signuptable=new Sign_up();
    signuptable->setWindowModality(Qt::ApplicationModal);
    signuptable->show();
}



SOCKET socketconnect(){
    //初始化DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);     //一样的

    //创建套接字
    SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    cout << "Try to connect to the server : xxx.xxx.xxx.xxx ...\n" << endl;
    //向服务器发起请求
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("xxx.xxx.xxx.xxx");
    sockAddr.sin_port = htons(xxx);
    int out=0;
    while (::connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
        cout<<"Connection Error! Now re-try to get connected ... "<<endl;
        out++;
        if(out==1){
            QMessageBox::information(NULL,"提示","对不起，我好像走丢了QAQ");
            cout<<"Can't to connect."<<endl;
            return 0;
        }
    }
    cout<<"Connected!"<<endl;
    cout<<sock<<endl;
    return sock;
}

void MainWindow::on_exit_pushButton_clicked()
{
    this->close();

}


// 鼠标左键触发
void MainWindow::mousePressEvent(QMouseEvent *event){

    // 判断鼠标左键
    if(event->button() == Qt::LeftButton){

        // 求坐标差值, 具体分析放后面
        coordinate = event->globalPos() - this->frameGeometry().topLeft();
    }

}

// 鼠标移动触发
void MainWindow::mouseMoveEvent(QMouseEvent *event){

    // 判断左键(Qt::LeftButton)是否被按下, 只有按下了才返回1(true)
    if(event->buttons() & Qt::LeftButton){

        // 移动窗口
        move(event->globalPos() - coordinate);

    }

}
