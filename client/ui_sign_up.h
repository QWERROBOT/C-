/********************************************************************************
** Form generated from reading UI file 'sign_up.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGN_UP_H
#define UI_SIGN_UP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Sign_up
{
public:
    QPushButton *Button_finishsignup;
    QLineEdit *user_id;
    QLineEdit *user_password;
    QLineEdit *name;
    QPushButton *pushButton;

    void setupUi(QWidget *Sign_up)
    {
        if (Sign_up->objectName().isEmpty())
            Sign_up->setObjectName(QString::fromUtf8("Sign_up"));
        Sign_up->resize(340, 290);
        Button_finishsignup = new QPushButton(Sign_up);
        Button_finishsignup->setObjectName(QString::fromUtf8("Button_finishsignup"));
        Button_finishsignup->setGeometry(QRect(125, 230, 91, 31));
        user_id = new QLineEdit(Sign_up);
        user_id->setObjectName(QString::fromUtf8("user_id"));
        user_id->setGeometry(QRect(95, 140, 150, 25));
        QFont font;
        font.setPointSize(11);
        user_id->setFont(font);
        user_password = new QLineEdit(Sign_up);
        user_password->setObjectName(QString::fromUtf8("user_password"));
        user_password->setGeometry(QRect(95, 190, 150, 25));
        user_password->setFont(font);
        name = new QLineEdit(Sign_up);
        name->setObjectName(QString::fromUtf8("name"));
        name->setGeometry(QRect(95, 90, 150, 25));
        name->setFont(font);
        pushButton = new QPushButton(Sign_up);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(304, 0, 38, 30));
        QFont font1;
        font1.setPointSize(12);
        pushButton->setFont(font1);
        pushButton->setStyleSheet(QString::fromUtf8("border-style:none;\n"
"background:transparent;"));

        retranslateUi(Sign_up);

        QMetaObject::connectSlotsByName(Sign_up);
    } // setupUi

    void retranslateUi(QWidget *Sign_up)
    {
        Sign_up->setWindowTitle(QCoreApplication::translate("Sign_up", "OurChat", nullptr));
        Button_finishsignup->setText(QCoreApplication::translate("Sign_up", "\347\202\271\345\207\273\345\256\214\346\210\220\346\263\250\345\206\214", nullptr));
        user_id->setPlaceholderText(QCoreApplication::translate("Sign_up", "\345\270\220\345\217\267", nullptr));
        user_password->setPlaceholderText(QCoreApplication::translate("Sign_up", "\345\257\206\347\240\201", nullptr));
        name->setPlaceholderText(QCoreApplication::translate("Sign_up", "\346\230\265\347\247\260(\350\257\267\344\275\277\347\224\250\350\213\261\346\226\207)", nullptr));
        pushButton->setText(QCoreApplication::translate("Sign_up", "\303\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Sign_up: public Ui_Sign_up {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGN_UP_H
