# QT-OurChat
C++大作业，因为时间问题以及知识不够，暂时完成了这么多，还有很多地方可以修改，代码逻辑不够完善

没有数据库，用文件管理数据

服务端要在Linux运行（本人使用了云服务器），没有写Makefile，可以自己写一个，或者复制如下命令
g++ -c server.cpp file.cpp -std=c++11

g++ file.o server.o -o server -pthread

即可生成server的程序，然后./server运行

服务端的用户信息保存在user.txt中，如果运行出错了，请手动修改

客户端使用时，不要同时退出两个客户端，因为服务端只用了一个全局变量来进行线程通信，会导致一些线程没有关闭
