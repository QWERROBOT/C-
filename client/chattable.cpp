#include "chattable.h"
#include "ui_chattable.h"

#include <QListWidget>
#include <fstream>
#include <QString>
#include <QDebug>
#include <QTreeView>
#include <QVBoxLayout>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll

//调用WIN API需要用到的头文件与库 [实现缩放]
#ifdef Q_OS_WIN
#include <qt_windows.h>
#include <Windowsx.h>
#endif
#define BUFFER_SIZE 1024
#define MAX_INPUT 100

using namespace std;

int needRecv=sizeof(Alldata);
int needSend=sizeof(Alldata);


SOCKET sock;

SOCKET sockrecv;

std::mutex mutex_;//锁

chattable::chattable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chattable)
{
    ui->setupUi(this);
    setFixedSize(860,688);//设置ui尺寸
    ui->chat_textBrowser->setFixedSize(550,481);

    mutex_.lock();
    sock=socketconnect();//调用函数建立tcp连接

    Alldata alldata;//消息结构体
    alldata.type='3';
    memcpy(alldata.Username,thisname.c_str(),thisname.length());
    memcpy(alldata.UserID,thisID.c_str(),thisID.length());

    char *sendMsg = (char*)malloc(needSend);
    memcpy(sendMsg,&alldata,needSend);//把结构体转成char*
    int pos=0;
    int len=0;
    while(pos<needSend){
        len=send(sock, sendMsg+pos, sizeof(Alldata), 0);
        if(len<=0){
            perror("ERRPR");
            break;
        }
        pos+=len;
    }
    free(sendMsg);//释放动态数组
    cout << "Connecting......" << endl;
    mutex_.unlock();
    Sleep(500);//暂停0.5秒

    setWindowFlags(Qt::FramelessWindowHint);//Qt::FramelessWindowHint设置窗口标志为无边框，而Qt::WindowStaysOnTopHint使窗口位于所有界面之上
    ui->sendButton->setDefault(false);
    ui->sendButton->setStyleSheet(tr("QPushButton{border:none}QPushButton{background-color: rgb(238, 238, 238)}QPushButton:hover{background-color:rgb(0, 184, 0);}"));
    ui->exit_pushButton->setStyleSheet(tr("QPushButton{background:transparent}QPushButton{border-style:none}QPushButton:hover{background-color:red};"));
    ui->online_tableWidget->verticalScrollBar()->setStyleSheet(//设置table的滚动条
                "QScrollBar:vertical{width:8px;background:rgba(0,0,0,0%);}"
                "QScrollBar::handle:vertical{width:8px;background:rgba(0,0,0,25%);border-radius:4px;min-height:20;}"//上下设置为椭圆
                "QScrollBar::handle:vertical:hover{width:8px;background:rgba(0,0,0,50%);border-radius:4px;min-height:20;}"//鼠标悬浮颜色变深
                "QScrollBar::add-line:vertical{height:9px;width:8px;border-image:url(:/images/bottom.png);subcontrol-position:bottom;}"//下箭头
                "QScrollBar::sub-line:vertical{height:9px;width:8px;border-image:url(:/images/top.png);subcontrol-position:top;}"//上箭头
                "QScrollBar::add-line:vertical:hover{height:7px;width:6px;border-image:url(:/images/bottom.png);border:1px;subcontrol-position:bottom;}"//鼠标悬浮下箭头
                "QScrollBar::sub-line:vertical:hover{height:7px;width:6px;border-image:url(:/images/top.png);border:1px;subcontrol-position:top;}"//鼠标悬浮上箭头
                "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{background:rgba(0,0,0,10%);border-radius:4px;}");//滚动时部分
    ui->chat_textBrowser->verticalScrollBar()->setStyleSheet(//设置show的滚动条
                "QScrollBar:vertical{width:8px;background:rgba(0,0,0,0%);}"
                "QScrollBar::handle:vertical{width:8px;background:rgba(0,0,0,25%);border-radius:4px;min-height:20;}"//上下设置为椭圆
                "QScrollBar::handle:vertical:hover{width:8px;background:rgba(0,0,0,50%);border-radius:4px;min-height:20;}"//鼠标悬浮颜色变深
                "QScrollBar::add-line:vertical{height:9px;width:8px;border-image:url(:/images/bottom.png);subcontrol-position:bottom;}"//下箭头
                "QScrollBar::sub-line:vertical{height:9px;width:8px;border-image:url(:/images/top.png);subcontrol-position:top;}"//上箭头
                "QScrollBar::add-line:vertical:hover{height:7px;width:6px;border-image:url(:/images/bottom.png);border:1px;subcontrol-position:bottom;}"//鼠标悬浮下箭头
                "QScrollBar::sub-line:vertical:hover{height:7px;width:6px;border-image:url(:/images/top.png);border:1px;subcontrol-position:top;}"//鼠标悬浮上箭头
                "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{background:rgba(0,0,0,10%);border-radius:4px;}");//滚动时部分
    ui->inputtext->verticalScrollBar()->setStyleSheet(//设置输入框的滚动条
                "QScrollBar:vertical{width:8px;background:rgba(0,0,0,0%);}"
                "QScrollBar::handle:vertical{width:8px;background:rgba(0,0,0,25%);border-radius:4px;min-height:20;}"//上下设置为椭圆
                "QScrollBar::handle:vertical:hover{width:8px;background:rgba(0,0,0,50%);border-radius:4px;min-height:20;}"//鼠标悬浮颜色变深
                "QScrollBar::add-line:vertical{height:9px;width:8px;border-image:url(:/images/bottom.png);subcontrol-position:bottom;}"//下箭头
                "QScrollBar::sub-line:vertical{height:9px;width:8px;border-image:url(:/images/top.png);subcontrol-position:top;}"//上箭头
                "QScrollBar::add-line:vertical:hover{height:7px;width:6px;border-image:url(:/images/bottom.png);border:1px;subcontrol-position:bottom;}"//鼠标悬浮下箭头
                "QScrollBar::sub-line:vertical:hover{height:7px;width:6px;border-image:url(:/images/top.png);border:1px;subcontrol-position:top;}"//鼠标悬浮上箭头
                "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{background:rgba(0,0,0,10%);border-radius:4px;}");//滚动时部分

    ui->online_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//表格只读
    ui->online_tableWidget->setItemDelegate(new NoFocusDelegate());//去掉表格虚框
    ui->online_tableWidget->setTextElideMode(Qt::ElideRight);//防止文本过长显示右边
    ui->online_tableWidget->setShowGrid(false);//取消网格
    ui->online_tableWidget->setColumnCount(1);//设定显示一列内容
    ui->online_tableWidget->setColumnWidth(0,251);//设置宽度
    online_userlist();//显示在线用户

    ui->online_tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏第一行
    //ui->online_tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏滚动条

    std::thread getMsg(&chattable::getchat,this);//用一个线程定时接收
    getMsg.detach();
}

chattable::~chattable()
{
    delete ui;
}


void chattable::getchat()
{

    sockrecv=socketconnect();
    Alldata alldata;
    alldata.type='4';
    memcpy(alldata.Username,thisname.c_str(),thisname.length());
    memcpy(alldata.UserID,thisID.c_str(),thisID.length());

    char *sendMsg = (char*)malloc(needSend);
    memcpy(sendMsg, &alldata, needSend);
    int pos = 0;
    int len = 0;
    while (pos < needSend) {
        len = send(sockrecv, sendMsg + pos, needSend, 0);
        if (len <= 0) {
            perror("ERRPR");
            break;
        }
        pos += len;
    }
    free(sendMsg);

    cout<<"recving........"<<endl;

    while(1){//循环接收信息
        char *recvMsg = (char*)malloc(needRecv);
        pos=0;
        while(pos<needRecv){
            len=recv(sockrecv,recvMsg+pos,sizeof(Alldata),0);
            if(len<0){
                cout<<"Recieve Data Failed!"<<endl;
                break;
            }
            pos+=len;
        }
        mutex_.lock();//上锁
        memcpy(&alldata,recvMsg,sizeof(Alldata));
        free(recvMsg);

        SYSTEMTIME sys;//API获得系统时间
        GetLocalTime(&sys);

        fromname=alldata.fromname;//发消息人的名字
        string filename="./chatlog/"+thisname+"_"+fromname+".txt";//保存的文件名
        string Msg=alldata.information;//消息
        string fromname_timestring=fromname+" "+to_string(sys.wYear)+"/"+to_string(sys.wMonth)+"/"+to_string(sys.wDay)+" "+to_string(sys.wHour)+":"+to_string(sys.wMinute)+":"+to_string(sys.wSecond);//名字+时间

        cout<<"get "<<Msg<<endl;

        if(toname==fromname){
            ui->chat_textBrowser->append(QString::fromStdString(" "+fromname_timestring).toUtf8());
            ui->chat_textBrowser->append(QString::fromStdString(" "+Msg).toUtf8());
            ui->chat_textBrowser->moveCursor(QTextCursor::End);
        }


        /*ofstream ofile;//把收到的消息写入文件
        ofile.open(filename,ios::app);
        ofile<<("\n "+fromname_timestring)<<"\n "+Msg;


        ifstream ifile;
        string line;
        int thisname_index=0;
        int n=GetTxtLine("useronline.txt");
        ifile.open("useronline.txt");
        for(int i=1;i<=n;i++){
            getline(ifile,line);
            if(line==thisname){
                thisname_index=i;
                break;
            }
        }
        ifile.close();

        int fromname_index=0;
        ifile.open("useronline.txt");
        for(int i=1;i<=n;i++){
            getline(ifile,line);
            if(line==fromname){
                fromname_index=i;
                break;
            }
        }
        ifile.close();

        if(fromname_index<thisname_index) fromname_index+=1;*/
        //ui->online_tableWidget->item(2,0)->setBackground(QBrush(QColor(255, 0, 0)));



        mutex_.unlock();//解锁
        Sleep(500);//暂停0.5秒，防止两个socket发生错误
    }
}

//-------------------------------------------------------------------------------------------------

//nativeEvent主要用于进程间通信-消息传递，使用这种方式后来实现窗体的缩放 [加上了这函数，窗口也能移动了]
bool chattable::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)

    MSG *param = static_cast<MSG *>(message);

    switch (param->message)
    {
    case WM_NCHITTEST:
    {
        int nX = GET_X_LPARAM(param->lParam) - this->geometry().x();
        int nY = GET_Y_LPARAM(param->lParam) - this->geometry().y();

        // 如果鼠标位于子控件上，则不进行处理
        if (childAt(nX, nY) != nullptr)
            return QWidget::nativeEvent(eventType, message, result);

        *result = HTCAPTION;

        // 鼠标区域位于窗体边框，进行缩放
        if ((nX > 0) && (nX < m_nBorderWidth))
            *result = HTLEFT;

        if ((nX > this->width() - m_nBorderWidth) && (nX < this->width()))
            *result = HTRIGHT;

        if ((nY > 0) && (nY < m_nBorderWidth))
            *result = HTTOP;

        if ((nY > this->height() - m_nBorderWidth) && (nY < this->height()))
            *result = HTBOTTOM;

        if ((nX > 0) && (nX < m_nBorderWidth) && (nY > 0)
                && (nY < m_nBorderWidth))
            *result = HTTOPLEFT;

        if ((nX > this->width() - m_nBorderWidth) && (nX < this->width())
                && (nY > 0) && (nY < m_nBorderWidth))
            *result = HTTOPRIGHT;

        if ((nX > 0) && (nX < m_nBorderWidth)
                && (nY > this->height() - m_nBorderWidth) && (nY < this->height()))
            *result = HTBOTTOMLEFT;

        if ((nX > this->width() - m_nBorderWidth) && (nX < this->width())
                && (nY > this->height() - m_nBorderWidth) && (nY < this->height()))
            *result = HTBOTTOMRIGHT;

        return true;
    }
    }

    return QWidget::nativeEvent(eventType, message, result);
}

void chattable::mouseMoveEvent(QMouseEvent *event)
{
    //去表格虚框
    QPoint EndPos;
    if ( event->buttons() == Qt::LeftButton )
    {
    EndPos = event->globalPos() - StartPos;
    this->move(EndPos);
    }
}
void NoFocusDelegate::paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex &index) const
{
    QStyleOptionViewItem itemOption(option);
    if (itemOption.state & QStyle::State_HasFocus)
        itemOption.state = itemOption.state ^ QStyle::State_HasFocus;
    QStyledItemDelegate::paint(painter, itemOption, index);
}

//-------------------------------------------------------------------------------------------------

void chattable::on_push_returnlogin_clicked()//返回按钮
{
    Alldata alldata;
    alldata.type='9';
    alldata.type_='9';
    memcpy(alldata.Username,thisname.c_str(),thisname.length());
    memcpy(alldata.Username,thisID.c_str(),thisID.length());

    char *sendMsg = (char*)malloc(needSend);
    memcpy(sendMsg,&alldata,needSend);
    int pos=0;
    int len=0;
    while(pos<needSend){
        len=send(sock, sendMsg+pos, needSend, 0);
        if(len<=0){
            perror("ERRPR");
            break;
        }
        pos+=len;
    }
    free(sendMsg);

    //send(sock,(char*)&alldata,sizeof(Alldata),0);
    closesocket(sock);
    MainWindow *father=new MainWindow();
    this->close();//聊天界面关闭
    father->show();//登录界面打开
}

void chattable::on_exit_pushButton_clicked()//离开按钮
{
    Alldata alldata;
    alldata.type='9';
    alldata.type_='9';
    memcpy(alldata.Username,thisname.c_str(),thisname.length());
    //memcpy(alldata.Username,thisID.c_str(),thisID.length());

    char *sendMsg = (char*)malloc(needSend);
    memcpy(sendMsg,&alldata,needSend);
    int pos=0;
    int len=0;
    while(pos<needSend){
        len=send(sock, sendMsg+pos, needSend, 0);
        if(len<=0){
            perror("ERRPR");
            break;
        }
        pos+=len;
    }
    free(sendMsg);

    //send(sock,(char*)&alldata,sizeof(Alldata),0);
    closesocket(sock);
    this->close();
}

void chattable::on_search_pushButton_clicked()//搜索框，未完成
{
    if(ui->search_user->text().isEmpty()){
        QMessageBox::information(this,"提示","请输入要聊天用户");
    }
}

void chattable::online_userlist(){//展示在线用户
    ui->online_tableWidget->verticalHeader()->hide();//隐藏第一列
    ui->online_tableWidget->horizontalHeader()->hide();//隐藏第一行
    ui->online_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置单元格整行选中
    ui->online_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑

    int n=GetTxtLine("useronline.txt");
    cout<<"online number: "<<n<<endl;
    string line;
    ifstream ifile;
    ifile.open("useronline.txt");
    for(int i=1;i<=n;i++){
        getline(ifile,line);
        if(line==thisname){
            break;
        }
    }
    ifile.close();

    cout<<"line: "<<line<<endl;

    ifstream file;
    file.open("useronline.txt");
    QString user;
    user=QString(line.c_str());
    if(!line.empty()){
        QTableWidgetItem *name=new QTableWidgetItem(user);
        name->setBackground(QBrush(QColor(0, 255, 0)));
        int rowcount=ui->online_tableWidget->rowCount();
        ui->online_tableWidget->insertRow(rowcount);
        ui->online_tableWidget->setItem(rowcount,0,name);
    }

    for(int i=0;i<n;i++){

        getline(file,line);
        if(line==thisname) continue;
        user=QString(line.c_str());
        QTableWidgetItem *name=new QTableWidgetItem(user);
        int rowcount=ui->online_tableWidget->rowCount();
        ui->online_tableWidget->insertRow(rowcount);
        ui->online_tableWidget->setItem(rowcount,0,name);
    }
    file.close();
}


void chattable::on_online_tableWidget_cellDoubleClicked(int row, int column)//双击在线用户的名字，显示聊天内容
{
    ifstream file;
    int n=GetTxtLine("useronline.txt");
    file.open("useronline.txt");
    string line;
    for(int i=1;i<=n;i++){
        getline(file,line);
        if(QString(line.c_str())==ui->online_tableWidget->item(row,0)->text()){//点击的行数的内容和在线列表的内容行行对比,如果名字是点击的名字就停止
            file.close();
            toname=line;
            break;
        }
    }
    file.close();

    line=line.empty();
    ui->tonameshow_textEdit->setText(QString(toname.c_str()));//对话框上面显示的名字
    ui->chat_textBrowser->clear();//清空对话框内容

    string filename;
    filename="./chatlog/"+thisname+"_"+toname+".txt";
    int txtline=GetTxtLine(filename.c_str());
    ifstream file_;
    file_.open(filename);

    for (int i=1; i <= txtline; i++) {
        getline(file_,line);
        ui->chat_textBrowser->append(line.c_str());
    }
    file_.close();
}

void chattable::on_check_pushButton_clicked()//点击刷新在线用户表
{
    std::thread t2(&chattable::getlist,this);
    t2.detach();

}


void chattable::getlist()//获取在线列表
{
    mutex_.lock();
    Alldata alldata;
    alldata.type='1';

    char *sendMsg = (char*)malloc(needSend);
    memcpy(sendMsg,&alldata,needSend);
    int pos=0;
    int len=0;
    while(pos<needSend){
        len=send(sock, sendMsg+pos, needSend, 0);
        if(len<=0){
            perror("ERRPR");
            break;
        }
        pos+=len;
    }
    free(sendMsg);
    cout<<"sended!!"<<endl;

    cout<<"Getting list......"<<endl;

    char *recvMsg = (char*)malloc(needRecv);
    pos=0;
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
    cout<<"Get!!!!"<<endl;

    fstream file;
    file.open("useronline.txt",ios::binary|ios::out);
    file.write(alldata.fileData,alldata.length);
    cout<<"Receive File Successful!"<<endl;
    file.close();

    ui->online_tableWidget->setRowCount(0);//清空table中的文本
    online_userlist();
    mutex_.unlock();
}


void chattable::on_sendButton_clicked()//发送按钮
{
    if(ui->inputtext->document()->isEmpty()){
        QMessageBox::information(this,"提示","输入的内容不可为空！");
    }
    if(ui->inputtext->toPlainText().count()>MAX_INPUT){
        QMessageBox::warning(this,"警告","输入的字符数不可超过100！！");
    }
    else{
        std::thread sendMsg(&chattable::sendMessage,this);
        sendMsg.detach();
        QString input=ui->inputtext->toPlainText();

        string filename="./chatlog/"+thisname+"_"+toname+".txt";
        string line,emptyline;
        ifstream ifile;
        int txtline=GetTxtLine(filename.c_str());
        getline(ifile,line);
        emptyline=emptyline.empty();
        ifile.close();

        SYSTEMTIME sys;
        GetLocalTime(&sys);
        //string toname_timestring=toname+" "+to_string(sys.wYear)+"/"+to_string(sys.wMonth)+"/"+to_string(sys.wDay)+" "+to_string(sys.wHour)+":"+to_string(sys.wMinute)+":"+to_string(sys.wSecond);
        string thisname_timestring=thisname+" "+to_string(sys.wYear)+"/"+to_string(sys.wMonth)+"/"+to_string(sys.wDay)+" "+to_string(sys.wHour)+":"+to_string(sys.wMinute)+":"+to_string(sys.wSecond);

        ui->chat_textBrowser->append(("\n			      "+thisname_timestring).c_str());
        ui->chat_textBrowser->append("			      "+input);
        ofstream ofile;
        ofile.open(filename.c_str(),ios::app);
        if(line==emptyline&&txtline==1) ofile<<"			      "<<thisname_timestring<<"\n"<<"\n"<<"			      "<<input.toStdString().c_str();
        else ofile<<"\n"<<"\n"<<"			      "<<thisname_timestring<<"\n"<<"			      "<<input.toStdString().c_str();
        ui->inputtext->clear();
        ofile.close();
        ui->chat_textBrowser->moveCursor(QTextCursor::End);
    }
}

void chattable::sendMessage()//发送线程的函数
{
    mutex_.lock();

    Alldata alldata;
    alldata.type='2';
    memcpy(alldata.fromname,thisname.c_str(),thisname.length());
    memcpy(alldata.toname,toname.c_str(),toname.length());
    QString input=ui->inputtext->toPlainText().toUtf8();
    strcpy(alldata.information,input.toStdString().c_str());//用memcpy会出问题
    string test=input.toUtf8().toStdString().c_str();
    string testall=alldata.information;
    cout<<test<<endl;
    cout<<"send inf: "<<testall<<endl;
    cout<<input.toUtf8().toStdString()<<endl;

    char *sendMsg = (char*)malloc(needSend);
    memcpy(sendMsg,&alldata,needSend);
    int pos=0;
    int len=0;
    while(pos<needSend){
        len=send(sock, sendMsg+pos, needSend, 0);
        if(len<=0){
            perror("ERRPR");
            break;
        }
        pos+=len;
    }
    free(sendMsg);

    mutex_.unlock();
}

void chattable::on_save_message_button_clicked()//保存聊天记录
{
    QString fileName=QFileDialog::getSaveFileName(this,tr("保存聊天记录"),tr("聊天记录"),tr("文本(*.txt)"));
    QFile file(fileName);
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream stream(&file);
    stream << ui->chat_textBrowser->toPlainText();
    stream.flush();
    file.close();
}

void chattable::on_file_button_clicked()
{
    QMessageBox::information(this,"提示","该功能尚未实现QAQ");
}

void chattable::on_cut_button_clicked()
{
    Screen *s=new Screen();
    s->show();
}

void chattable::on_picture_button_clicked()
{
    QMessageBox::information(this,"提示","对不起，还不能使用该功能哦QAQ");
}
