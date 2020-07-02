#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMessageBox>//消息提示框头文件
#include <iostream>
#include <QListWidget>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QWidget>
#include <chattable.h>
#include <global.h>
#include <sign_up.h>
#include <QMouseEvent>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <cstring>
#include <fstream>
#include <WinSock2.h>
#include <windows.h>   //windows.h要写在WinSock2.h的后面
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll

#define BUF_SIZE 100

struct Alldata
{
    char type = '0';
    char type_ = '0';
    char signup_type = '0';
    char Username[20] = { 0 };
    char UserID[20] = { 0 };
    char UserPassword[20] = { 0 };
    char judge = 'N';
    char toname[20] = { 0 };
    char fromname[20] = { 0 };
    int clnt_sock;
    char information[1000] = { 0 };
    long long length;
    char fileData[50000] = { 0 };
};

SOCKET socketconnect();

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    bool nativeEvent_(const QByteArray &eventType, void *message, long *result);

    void mouseMoveEvent(QMouseEvent *event);//窗口移动

    void mousePressEvent(QMouseEvent *event);//窗口移动

    ~MainWindow();

private slots:
    void on_signin_clicked();

    void on_pushButton_signup_clicked();

    void on_exit_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QPoint coordinate;//窗口移动
};
#endif // MAINWINDOW_H
