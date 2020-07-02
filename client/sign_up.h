#ifndef SIGN_UP_H
#define SIGN_UP_H

#include <QWidget>
#include <mainwindow.h>
#include <iostream>
#include <global.h>

#define BUF_SIZE 100

struct SIGNUP_UserData
{
    char Name[20] = { 0 };
    char UserID[20] = { 0 };
    char UserPassword[20] = { 0 };
};

namespace Ui {
class Sign_up;
}

class Sign_up : public QWidget
{
    Q_OBJECT

public:
    explicit Sign_up(QWidget *parent = nullptr);

    void mouseMoveEvent(QMouseEvent *event);//窗口移动

    void mousePressEvent(QMouseEvent *event);//窗口移动

    ~Sign_up();

private slots:
    void on_Button_finishsignup_clicked();

    void on_pushButton_clicked();

private:
    Ui::Sign_up *ui;
    QPoint coordinate;//窗口移动
};

#endif // SIGN_UP_H

