/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *signin;
    QLineEdit *user_text;
    QLineEdit *password_text;
    QPushButton *pushButton_signup;
    QPushButton *icon_button;
    QPushButton *exit_pushButton;
    QPushButton *logo_Button;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(280, 400);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 246, 246);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        signin = new QPushButton(centralwidget);
        signin->setObjectName(QString::fromUtf8("signin"));
        signin->setGeometry(QRect(50, 290, 181, 40));
        QFont font;
        font.setPointSize(11);
        signin->setFont(font);
        signin->setCursor(QCursor(Qt::PointingHandCursor));
        signin->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 180, 0);\n"
"color: rgb(245, 245, 245);"));
        user_text = new QLineEdit(centralwidget);
        user_text->setObjectName(QString::fromUtf8("user_text"));
        user_text->setGeometry(QRect(70, 200, 140, 25));
        QFont font1;
        font1.setPointSize(10);
        user_text->setFont(font1);
        password_text = new QLineEdit(centralwidget);
        password_text->setObjectName(QString::fromUtf8("password_text"));
        password_text->setGeometry(QRect(70, 235, 140, 25));
        password_text->setFont(font1);
        password_text->setEchoMode(QLineEdit::Password);
        pushButton_signup = new QPushButton(centralwidget);
        pushButton_signup->setObjectName(QString::fromUtf8("pushButton_signup"));
        pushButton_signup->setGeometry(QRect(100, 350, 75, 23));
        QFont font2;
        font2.setPointSize(11);
        font2.setBold(false);
        font2.setWeight(50);
        pushButton_signup->setFont(font2);
        pushButton_signup->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_signup->setMouseTracking(false);
        pushButton_signup->setStyleSheet(QString::fromUtf8("color: rgb(78, 96, 255);\n"
"border-style:none;\n"
"background:transparent;\n"
""));
        icon_button = new QPushButton(centralwidget);
        icon_button->setObjectName(QString::fromUtf8("icon_button"));
        icon_button->setGeometry(QRect(95, 70, 90, 90));
        icon_button->setStyleSheet(QString::fromUtf8(""));
        QIcon icon;
        icon.addFile(QString::fromUtf8("chat.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        icon_button->setIcon(icon);
        icon_button->setIconSize(QSize(120, 120));
        exit_pushButton = new QPushButton(centralwidget);
        exit_pushButton->setObjectName(QString::fromUtf8("exit_pushButton"));
        exit_pushButton->setGeometry(QRect(246, 0, 35, 30));
        exit_pushButton->setFont(font);
        logo_Button = new QPushButton(centralwidget);
        logo_Button->setObjectName(QString::fromUtf8("logo_Button"));
        logo_Button->setGeometry(QRect(6, 6, 75, 23));
        QFont font3;
        font3.setPointSize(12);
        logo_Button->setFont(font3);
        logo_Button->setStyleSheet(QString::fromUtf8("border-style:none;\n"
"background:transparent;\n"
"color: rgb(140, 140, 140);"));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "OurChat", nullptr));
        signin->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
#if QT_CONFIG(shortcut)
        signin->setShortcut(QCoreApplication::translate("MainWindow", "Return, Enter", nullptr));
#endif // QT_CONFIG(shortcut)
        user_text->setPlaceholderText(QCoreApplication::translate("MainWindow", "\345\270\220\345\217\267", nullptr));
        password_text->setPlaceholderText(QCoreApplication::translate("MainWindow", "\345\257\206\347\240\201", nullptr));
        pushButton_signup->setText(QCoreApplication::translate("MainWindow", "\346\263\250\345\206\214", nullptr));
        icon_button->setText(QString());
        exit_pushButton->setText(QCoreApplication::translate("MainWindow", "\303\227", nullptr));
        logo_Button->setText(QCoreApplication::translate("MainWindow", "OurChat", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
