#ifndef CHATTABLE_H
#define CHATTABLE_H
#include <QWidget>
#include <mainwindow.h>
#include <iostream>
#include <QListWidget>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QFileDialog>
#include <global.h>
#include <file.h>
#include <QMouseEvent>
#include <QScrollBar>
#include <string>
#include <locale>
#include <codecvt>
#include <thread>//用于创建线程
#include <mutex>
#include <chrono>//用于时间延时 获取时间之类的
#include <QStyledItemDelegate>
#include <screen.h>

namespace Ui {
class chattable;
}

class chattable : public QWidget
{
    Q_OBJECT

public:
    explicit chattable(QWidget *parent = nullptr);

    void initContactTree();

    void initStrangerTree();

    void onItemExpanded(QTreeWidgetItem *pItem);

    void onItemCollapsed(QTreeWidgetItem *pItem);

    void addMyFriendInfo(QTreeWidgetItem* pRootGroupItem);

    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

    void online_userlist();

    void getlist();

    void sendMessage();

    void getchat();



    ~chattable();

private slots:
    void on_push_returnlogin_clicked();

    void on_sendButton_clicked();


    void on_search_pushButton_clicked();


    void on_exit_pushButton_clicked();

    void on_online_tableWidget_cellDoubleClicked(int row, int column);

    void on_check_pushButton_clicked();

    void on_save_message_button_clicked();

    void on_file_button_clicked();

    void on_cut_button_clicked();

    void on_picture_button_clicked();

private:
    Ui::chattable *ui;

    int findedCurRow;

    int m_nBorderWidth; //m_nBorder表示鼠标位于边框缩放范围的宽度

    void mouseMoveEvent(QMouseEvent *event);

    QPoint StartPos;

};


class NoFocusDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    NoFocusDelegate(){};
    ~NoFocusDelegate(){};

    void NoFocusDelegate::paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex &index) const;
};

#endif // CHATTABLE_H
