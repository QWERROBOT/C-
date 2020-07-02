/********************************************************************************
** Form generated from reading UI file 'chattable.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATTABLE_H
#define UI_CHATTABLE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chattable
{
public:
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QPushButton *push_returnlogin;
    QTextEdit *inputtext;
    QPushButton *sendButton;
    QLineEdit *search_user;
    QPushButton *search_pushButton;
    QPushButton *pushButton;
    QPushButton *exit_pushButton;
    QPushButton *background_button;
    QTableWidget *online_tableWidget;
    QLabel *label;
    QPushButton *pushButton_2;
    QPushButton *check_pushButton;
    QTextEdit *tonameshow_textEdit;
    QTextBrowser *chat_textBrowser;
    QPushButton *pushButton_chat;
    QPushButton *save_message_button;
    QPushButton *picture_button;
    QPushButton *file_button;
    QPushButton *cut_button;

    void setupUi(QWidget *chattable)
    {
        if (chattable->objectName().isEmpty())
            chattable->setObjectName(QString::fromUtf8("chattable"));
        chattable->resize(860, 688);
        line = new QFrame(chattable);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(50, -10, 20, 701));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(chattable);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(300, -10, 20, 701));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(chattable);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(60, 50, 841, 20));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(chattable);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(310, 530, 561, 20));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        push_returnlogin = new QPushButton(chattable);
        push_returnlogin->setObjectName(QString::fromUtf8("push_returnlogin"));
        push_returnlogin->setGeometry(QRect(0, 660, 61, 31));
        QFont font;
        font.setPointSize(8);
        push_returnlogin->setFont(font);
        push_returnlogin->setCursor(QCursor(Qt::PointingHandCursor));
        push_returnlogin->setStyleSheet(QString::fromUtf8("border-style:none;\n"
"background:transparent;\n"
"color: rgb(225, 225, 225);"));
        inputtext = new QTextEdit(chattable);
        inputtext->setObjectName(QString::fromUtf8("inputtext"));
        inputtext->setGeometry(QRect(335, 576, 501, 65));
        QFont font1;
        font1.setPointSize(15);
        inputtext->setFont(font1);
        inputtext->setStyleSheet(QString::fromUtf8("border-style:none;"));
        sendButton = new QPushButton(chattable);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setGeometry(QRect(770, 654, 69, 25));
        QFont font2;
        font2.setPointSize(10);
        sendButton->setFont(font2);
        sendButton->setStyleSheet(QString::fromUtf8("background-color: rgb(248, 248, 248);"));
        search_user = new QLineEdit(chattable);
        search_user->setObjectName(QString::fromUtf8("search_user"));
        search_user->setGeometry(QRect(70, 25, 181, 26));
        QFont font3;
        font3.setPointSize(11);
        search_user->setFont(font3);
        search_pushButton = new QPushButton(chattable);
        search_pushButton->setObjectName(QString::fromUtf8("search_pushButton"));
        search_pushButton->setGeometry(QRect(265, 25, 26, 26));
        QFont font4;
        font4.setPointSize(20);
        font4.setBold(false);
        font4.setWeight(50);
        search_pushButton->setFont(font4);
        pushButton = new QPushButton(chattable);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(12, 20, 36, 36));
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon;
        icon.addFile(QString::fromUtf8("qq.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(40, 40));
        exit_pushButton = new QPushButton(chattable);
        exit_pushButton->setObjectName(QString::fromUtf8("exit_pushButton"));
        exit_pushButton->setGeometry(QRect(820, 0, 41, 35));
        QFont font5;
        font5.setFamily(QString::fromUtf8("\346\226\260\345\256\213\344\275\223"));
        font5.setPointSize(15);
        font5.setBold(false);
        font5.setWeight(50);
        exit_pushButton->setFont(font5);
        exit_pushButton->setStyleSheet(QString::fromUtf8("border-style:none;\n"
"background:transparent;"));
        background_button = new QPushButton(chattable);
        background_button->setObjectName(QString::fromUtf8("background_button"));
        background_button->setEnabled(true);
        background_button->setGeometry(QRect(0, 0, 61, 691));
        background_button->setStyleSheet(QString::fromUtf8("background-color: rgb(42, 42, 42);"));
        online_tableWidget = new QTableWidget(chattable);
        online_tableWidget->setObjectName(QString::fromUtf8("online_tableWidget"));
        online_tableWidget->setGeometry(QRect(59, 88, 251, 600));
        online_tableWidget->setFont(font1);
        online_tableWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(231, 231, 231);"));
        label = new QLabel(chattable);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 60, 249, 30));
        QFont font6;
        font6.setPointSize(12);
        font6.setBold(false);
        font6.setWeight(50);
        label->setFont(font6);
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(231, 231, 231);"));
        pushButton_2 = new QPushButton(chattable);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(310, 530, 561, 161));
        pushButton_2->setStyleSheet(QString::fromUtf8("border-style:none;\n"
"background-color: rgb(255, 255, 255);\n"
""));
        check_pushButton = new QPushButton(chattable);
        check_pushButton->setObjectName(QString::fromUtf8("check_pushButton"));
        check_pushButton->setGeometry(QRect(220, 65, 81, 23));
        check_pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        tonameshow_textEdit = new QTextEdit(chattable);
        tonameshow_textEdit->setObjectName(QString::fromUtf8("tonameshow_textEdit"));
        tonameshow_textEdit->setGeometry(QRect(340, 25, 191, 41));
        QFont font7;
        font7.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font7.setPointSize(15);
        font7.setBold(true);
        font7.setWeight(75);
        tonameshow_textEdit->setFont(font7);
        tonameshow_textEdit->setStyleSheet(QString::fromUtf8("border-style:none;\n"
"background:transparent;"));
        chat_textBrowser = new QTextBrowser(chattable);
        chat_textBrowser->setObjectName(QString::fromUtf8("chat_textBrowser"));
        chat_textBrowser->setGeometry(QRect(310, 60, 550, 481));
        QFont font8;
        font8.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font8.setPointSize(11);
        chat_textBrowser->setFont(font8);
        chat_textBrowser->setStyleSheet(QString::fromUtf8("background-color: rgb(247, 247, 247);"));
        pushButton_chat = new QPushButton(chattable);
        pushButton_chat->setObjectName(QString::fromUtf8("pushButton_chat"));
        pushButton_chat->setGeometry(QRect(12, 80, 37, 37));
        pushButton_chat->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("select1.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_chat->setIcon(icon1);
        pushButton_chat->setIconSize(QSize(43, 43));
        save_message_button = new QPushButton(chattable);
        save_message_button->setObjectName(QString::fromUtf8("save_message_button"));
        save_message_button->setGeometry(QRect(435, 545, 30, 30));
        save_message_button->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("Message.png"), QSize(), QIcon::Normal, QIcon::Off);
        save_message_button->setIcon(icon2);
        save_message_button->setIconSize(QSize(30, 30));
        picture_button = new QPushButton(chattable);
        picture_button->setObjectName(QString::fromUtf8("picture_button"));
        picture_button->setGeometry(QRect(335, 545, 30, 30));
        picture_button->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("Picture.png"), QSize(), QIcon::Normal, QIcon::Off);
        picture_button->setIcon(icon3);
        picture_button->setIconSize(QSize(30, 30));
        file_button = new QPushButton(chattable);
        file_button->setObjectName(QString::fromUtf8("file_button"));
        file_button->setGeometry(QRect(368, 545, 30, 30));
        file_button->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("File.png"), QSize(), QIcon::Normal, QIcon::Off);
        file_button->setIcon(icon4);
        file_button->setIconSize(QSize(30, 30));
        cut_button = new QPushButton(chattable);
        cut_button->setObjectName(QString::fromUtf8("cut_button"));
        cut_button->setGeometry(QRect(402, 545, 30, 30));
        cut_button->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("Cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        cut_button->setIcon(icon5);
        cut_button->setIconSize(QSize(30, 30));
        pushButton_2->raise();
        background_button->raise();
        line->raise();
        line_2->raise();
        line_3->raise();
        line_4->raise();
        push_returnlogin->raise();
        inputtext->raise();
        sendButton->raise();
        search_user->raise();
        search_pushButton->raise();
        pushButton->raise();
        exit_pushButton->raise();
        online_tableWidget->raise();
        label->raise();
        check_pushButton->raise();
        tonameshow_textEdit->raise();
        chat_textBrowser->raise();
        pushButton_chat->raise();
        save_message_button->raise();
        picture_button->raise();
        file_button->raise();
        cut_button->raise();

        retranslateUi(chattable);

        QMetaObject::connectSlotsByName(chattable);
    } // setupUi

    void retranslateUi(QWidget *chattable)
    {
        chattable->setWindowTitle(QCoreApplication::translate("chattable", "OurChat", nullptr));
        push_returnlogin->setText(QCoreApplication::translate("chattable", "\347\202\271\345\207\273\350\277\224\345\233\236", nullptr));
        inputtext->setHtml(QCoreApplication::translate("chattable", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:15pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:13pt;\"><br /></p></body></html>", nullptr));
        sendButton->setText(QCoreApplication::translate("chattable", "\345\217\221\351\200\201(S)", nullptr));
#if QT_CONFIG(shortcut)
        sendButton->setShortcut(QCoreApplication::translate("chattable", "Ctrl+Return", nullptr));
#endif // QT_CONFIG(shortcut)
        search_user->setPlaceholderText(QCoreApplication::translate("chattable", "\350\257\245\345\212\237\350\203\275\346\232\202\346\234\252\345\256\236\347\216\260", nullptr));
        search_pushButton->setText(QCoreApplication::translate("chattable", "+", nullptr));
        pushButton->setText(QString());
        exit_pushButton->setText(QCoreApplication::translate("chattable", "\303\227", nullptr));
        background_button->setText(QString());
        label->setText(QCoreApplication::translate("chattable", " \345\234\250\347\272\277\347\224\250\346\210\267", nullptr));
        pushButton_2->setText(QString());
        check_pushButton->setText(QCoreApplication::translate("chattable", "\346\233\264\346\226\260\345\234\250\347\272\277\347\224\250\346\210\267", nullptr));
        pushButton_chat->setText(QString());
        save_message_button->setText(QString());
        picture_button->setText(QString());
        file_button->setText(QString());
        cut_button->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class chattable: public Ui_chattable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATTABLE_H
