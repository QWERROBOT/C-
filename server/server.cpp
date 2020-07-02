#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "file.h"
#include "server.h"
#include <pthread.h>
#define BUFSIZE 100
#define BUFFER_SIZE 1024
using namespace std;

pthread_mutex_t mutex;  // 定义互斥锁，全局变量

Alldata allalldata;

void *client_signup(void *arg)
{
	// 上锁，在没有解锁之前，pthread_mutex_lock()会阻塞
	pthread_mutex_lock(&mutex);

	Alldata alldata;
	alldata = *(struct Alldata*)arg;

	int sum = 0;
	
	sum = get_user_number();
	cout << "sum=  " << sum << endl << endl;
	//int clnt_sock = *(int *)arg;


	cout << "Registering:" << endl;
	cout << "Got name :  " << alldata.Username << "   " << strlen(alldata.Username) << endl;
	cout << "Got id :  " << alldata.UserID << "   " << strlen(alldata.UserID) << endl;
	cout << "Got password :  " << alldata.UserPassword << "   " << strlen(alldata.UserPassword) << endl;
	
	string username = alldata.Username, userid = alldata.UserID;
	int name = checkname(username), id = checkid(userid);
	if (username == "user" || username == "user_bak" || username == "useronline" || username == "useronline_bak" || username == "usersocket" || username == "usersocket_bak") name = 2;
	if (name == 1 && id == 1) {
		sum++;
		change_sumuser(sum);
		alldata.signup_type = 'Y';
		write_data(USERFILE, alldata.Username);
		write_data(USERFILE, alldata.UserID);
		write_data(USERFILE, alldata.UserPassword);
	}
	if (name == 2 && id == 1) alldata.signup_type = 'N';
	if (name == 1 && id == 2) alldata.signup_type = 'I';
	if (name == 2 && id == 2) alldata.signup_type = 'A';

	cout << "Signup++++" << endl;

	int needSend = sizeof(Alldata);
	char *sendMsg = (char*)malloc(needSend);
	memcpy(sendMsg, &alldata, needSend);
	int pos = 0;
	int len = 0;
	while (pos < needSend) {
		len = send(alldata.clnt_sock, sendMsg + pos, needSend, 0);
		if (len <= 0) {
			perror("ERRPR");
			break;
		}
		pos += len;
	}
	free(sendMsg);

	// 解锁，pthread_mutex_lock()唤醒，不阻塞
	pthread_mutex_unlock(&mutex);

	//close(alldata.clnt_sock);
	return NULL;
}

void *client_login(void *arg)
{
	// 上锁，在没有解锁之前，pthread_mutex_lock()会阻塞
	pthread_mutex_lock(&mutex);
	char yes = 'Y';
	char no = 'N';

	int linenumber = 0;
	//int clnt_sock = *(int *)arg;
	int yorn = 0;

	Alldata alldata;
	alldata = *(struct Alldata*)arg;

	cout << "Logging in......" << endl;
	cout << "Got id :  " << alldata.UserID << "   " << strlen(alldata.UserID) << endl;
	cout << "Got password :  " << alldata.UserPassword << "   " << strlen(alldata.UserPassword) << endl;

	linenumber = GetTxtLine(USERFILE);
	for (int j = 3; j <= linenumber; j += 3) {
		if (strcmp(alldata.UserID, (char*)getLineinf(USERFILE, j).c_str()) == 0) {
			if (strcmp(alldata.UserPassword, (char*)getLineinf(USERFILE, j + 1).c_str()) == 0) {
				strcpy(alldata.Username, (char*)getLineinf(USERFILE, j - 1).c_str());

				string line;                          //判断当前用户是否已经出现在online表中
				int txtline = GetTxtLine("useronline.txt");
				ifstream file;
				file.open("useronline.txt");
				int t = 0;
				for (int k = 0; k < txtline; k++) {
					getline(file, line);
					if (strcmp(alldata.Username, line.c_str())==0) {
						t = 1;
						cout << "you are online" << endl;
						break;
					}
				}
				file.close();
				if (t == 0) {
					cout << "you are not online" << endl;
					ofstream file_;
					file_.open("useronline.txt", ios::app);
					if (txtline == 1 && line.empty()) file_ << alldata.Username;
					else file_ << "\n" << alldata.Username;
					file_.close();
				}

				yorn = 1;
				cout << "yes" << endl;
				break;
			}
			else {
				cout << "no1" << endl;
				break;
			}
		}
		else {
			cout << "no2" << endl;
		}
	}
	
	cout << "Login++++" << endl;

	if (yorn == 1) alldata.judge = 'Y';

	int needSend = sizeof(Alldata);
	char *sendMsg = (char*)malloc(needSend);
	memcpy(sendMsg, &alldata, needSend);
	int pos = 0;
	int len = 0;
	while (pos < needSend) {
		len = send(alldata.clnt_sock, sendMsg + pos, sizeof(Alldata), 0);
		if (len <= 0) {
			perror("ERRPR");
			break;
		}
		pos += len;
	}
	//send(alldata.clnt_sock, (char*)&alldata, sizeof(Alldata), 0);
	free(sendMsg);
	
	// 解锁，pthread_mutex_lock()唤醒，不阻塞
	pthread_mutex_unlock(&mutex);

	//close(alldata.clnt_sock);
	return NULL;
}

void *client_getonlinelist(void *arg)
{
	// 上锁，在没有解锁之前，pthread_mutex_lock()会阻塞
	pthread_mutex_lock(&mutex);

	Alldata alldata;
	alldata = *(struct Alldata*)arg;

	cout << "Gettingfile........." << endl;
	
	fstream file;
	file.open("useronline.txt", ios::binary | ios::in | ios::ate);//打开时指针在文件尾
	alldata.length = file.tellg();
	//int length = file.tellg();
	//char* fileData = new char[length];
	file.seekg(0);
	file.read(alldata.fileData, alldata.length);

	int needSend = sizeof(Alldata);
	char *sendMsg = (char*)malloc(needSend);
	memcpy(sendMsg, &alldata, needSend);
	int pos = 0;
	int len = 0;
	while (pos < needSend) {
		len = send(alldata.clnt_sock, sendMsg + pos, sizeof(Alldata), 0);
		cout << "chuanle" << endl;
		if (len <= 0) {
			perror("ERRPR");
			break;
		}
		pos += len;
	}

	//send(alldata.clnt_sock, (char*)&alldata, sizeof(Alldata), 0);
	cout << "File Transfer Successful!" << endl;
	free(sendMsg);

	file.close();

	// 解锁，pthread_mutex_lock()唤醒，不阻塞
	pthread_mutex_unlock(&mutex);

	//close(alldata.clnt_sock);
	//pthread_exit(0);
	return NULL;
}


void *getinf(void *arg)
{

	Alldata alldata;
	alldata = *(struct Alldata*)arg;


	//while (1) {
		if (alldata.clnt_sock > 0) {
			pthread_mutex_lock(&mutex);
			string name = alldata.Username;
			int num = GetTxtLine("useronline.txt");
			string *user = new string[num];
			string line;
			string fromname;
			ifstream ifile;
			ifile.open("useronline.txt");
			for (int i = 0; i < num; i++) {
				getline(ifile, line);
				user[i] = line + ".txt";
			}
			ifile.close();
			for (int i = 0; i < num; i++) {
				ifile.open(user[i]);
				getline(ifile, line);
				fromname = line;
				getline(ifile, line);
				if (line == name) {
					getline(ifile, line);
					ifile.close();
					fstream file(user[i], ios::out);//清空文件内容

					memcpy(alldata.fromname, fromname.c_str(), sizeof(fromname.c_str()));
					memcpy(alldata.information, line.c_str(), sizeof(alldata.information));
					cout << "..." << endl;
					int needSend = sizeof(Alldata);
					char *sendMsg = (char*)malloc(needSend);
					memcpy(sendMsg, &alldata, needSend);
					int pos = 0;
					int len = 0;
					while (pos < needSend) {
						len = send(alldata.clnt_sock, sendMsg + pos, needSend, 0);
						if (len <= 0) {
							perror("ERRPR");
							break;
						}
						pos += len;
					}
					free(sendMsg);
					pthread_mutex_unlock(&mutex);

					break;
				}
				ifile.close();
			}
			pthread_mutex_unlock(&mutex);

			//string inf = allalldata.information;
			/*if (allalldata.type_ == '9'&&memcmp(allalldata.Username, alldata.Username, strlen(alldata.Username)) == 0) {
				string name = alldata.Username, name_ = allalldata.Username;
				cout << "allall " << name_ << "all " << name << endl;
				allalldata.type_ = '0';
				memset(allalldata.Username, 0, strlen(allalldata.Username));
				pthread_mutex_unlock(&mutex);
				break;
			}*/
			//if (!inf.empty() && memcmp(allalldata.toname, alldata.Username, strlen(alldata.Username)) == 0) {
			//	cout << "..." << endl;
			//	int needSend = sizeof(Alldata);
			//	char *sendMsg = (char*)malloc(needSend);
			//	memcpy(sendMsg, &allalldata, needSend);
			//	int pos = 0;
			//	int len = 0;
			//	while (pos < needSend) {
			//		len = send(alldata.clnt_sock, sendMsg + pos, needSend, 0);
			//		if (len <= 0) {
			//			perror("ERRPR");
			//			break;
			//		}
			//		pos += len;
			//	}
			//	free(sendMsg);
			//	inf = inf.empty();
			//	memcpy(allalldata.information, inf.c_str(), inf.length());
			//	pthread_mutex_unlock(&mutex);
			//}
			//else {
			//	cout << "none" << endl;
			//	pthread_mutex_unlock(&mutex);
			//	sleep(1);//暂停1s
				//usleep(500000);
				//continue;
			//}
		}
	//}


	//close(alldata.clnt_sock);
	return NULL;
}

void *client_chattable(void *arg)
{
	// 上锁，在没有解锁之前，pthread_mutex_lock()会阻塞
	//pthread_mutex_lock(&mutex);

	Alldata alldata;
	alldata = *(struct Alldata*)arg;

	pthread_t thread_id;

	pthread_mutex_init(&mutex, NULL); // 初始化互斥锁，互斥锁默认是打开的

	// 上锁，在没有解锁之前，pthread_mutex_lock()会阻塞
	pthread_mutex_lock(&mutex);
	int txtline = GetTxtLine("usersocket.txt");
	ofstream ofile;
	ofile.open("usersocket.txt", ios::app);
	if (txtline == 1) ofile << alldata.Username << "\n" << alldata.clnt_sock;
	else ofile << "\n" << alldata.Username << "\n" << alldata.clnt_sock;
	ofile.close();
	// 解锁，pthread_mutex_lock()唤醒，不阻塞
	pthread_mutex_unlock(&mutex);
	string ID = alldata.UserID;
	cout << ID << " is chatting!!!" << endl;

	while (1) {
		if (alldata.clnt_sock > 0) {
			Alldata alldata2;
			int needRecv = sizeof(Alldata);
			char *recvMsg = (char*)malloc(needRecv);
			int len;
			int pos = 0;
			while (pos < needRecv) {
				len = recv(alldata.clnt_sock, recvMsg + pos, sizeof(Alldata), 0);
				if (len < 0) {
					cout << "Recieve Data Failed!" << endl;
					break;
				}
				pos += len;
			}
			memcpy(&alldata2, recvMsg, sizeof(Alldata));
			alldata2.clnt_sock = alldata.clnt_sock;

			free(recvMsg);

			string toname = alldata2.toname, fromname = alldata2.fromname, inf = alldata2.information;
			cout << "type " << alldata2.type << endl;
			cout << "toname " << toname << endl;
			cout << "fromname " << fromname << endl;
			cout << "inf " << inf << endl;

			if (alldata2.type == '1') {                     //获取在线列表
				//给回调函数传的参数，&connfd，地址传递
				pthread_create(&thread_id, NULL, client_getonlinelist, &alldata2);  //创建线程
				pthread_detach(thread_id); // 线程分离，结束时自动回收资源，不阻塞
				cout << "Yes11" << endl;
				alldata2.type = '0';
			}
			if (alldata2.type == '2') {                     //发消息
				cout << "Forwarding message........." << endl;
				pthread_mutex_lock(&mutex);

				string filename = fromname + ".txt";
				ofstream ofile;
				ofile.open(filename,ios::out);
				ofile << fromname << "\n" << toname << "\n" << inf;
				ofile.close();

				cout << "Yes22" << endl;
				alldata2.type = '0';
				pthread_mutex_unlock(&mutex);
			}

			if (alldata2.type == '9') {                     //客户端结束
				pthread_mutex_lock(&mutex);

				string d_name;
				d_name = alldata2.Username;
				delete_online_user(d_name);//将用户从在线列表删除

				allalldata.type_ = '9';
				memcpy(allalldata.Username, alldata2.Username, sizeof(alldata2.Username));
				//memcpy(allalldata.UserID, alldata2.UserID, sizeof(alldata2.UserID));

				pthread_mutex_unlock(&mutex);
				cout << alldata2.UserID << " leave." << endl;
				break;
			}

		}

	}

	// 解锁，pthread_mutex_lock()唤醒，不阻塞
	//pthread_mutex_unlock(&mutex);

	close(alldata.clnt_sock);
	return NULL;
}


void *client(void *arg)
{
	// 上锁，在没有解锁之前，pthread_mutex_lock()会阻塞
	//pthread_mutex_lock(&mutex);
	pthread_t thread_id;

	pthread_mutex_init(&mutex, NULL); // 初始化互斥锁，互斥锁默认是打开的

	Alldata alldata;
	alldata = *(struct Alldata*)arg;

	string toname = alldata.toname, fromname = alldata.fromname, inf = alldata.information, id = alldata.UserID;
	cout << "1......" << endl;
	cout << "toname " << toname << endl;
	cout << "fromname " << fromname << endl;
	cout << "type " << alldata.type << endl;
	cout << "inf " << inf << endl;
	cout << "ID " << id << endl;

	while (1){
		
		if (allalldata.type_ == '9'&&memcmp(allalldata.Username, alldata.Username, strlen(alldata.Username)) == 0) 
		{
			//pthread_mutex_lock(&mutex);
			cout << "close!!!!!" << endl;
			//pthread_mutex_unlock(&mutex);
			sleep(1);
			allalldata.type_ = '0';
			memset(allalldata.Username, 0, strlen(allalldata.Username));
			
			
			break;
		}

		if (alldata.clnt_sock > 0) {
			if (alldata.type == '1') {                     //注册
				client_signup(&alldata);
				//pthread_create(&thread_id, NULL, client_signup, &alldata); //创建线程
				//pthread_detach(thread_id); // 线程分离，结束时自动回收资源，不阻塞
				cout << "Yes1" << endl;
				
				break;
			}
			if (alldata.type == '2') {                     //登录
				client_login(&alldata);
				//pthread_create(&thread_id, NULL, client_login, &alldata);
				//pthread_detach(thread_id);
				cout << "Yes2" << endl;

				//alldata.type = '0';
				break;
			}
			if (alldata.type == '3') {                     //chattable
				//给回调函数传的参数，&connfd，地址传递
				pthread_create(&thread_id, NULL, client_chattable, &alldata);
				pthread_detach(thread_id);
				cout << "Yes3" << endl;
				alldata.type = '0';
			}
			if (alldata.type == '4') {                     //获取信息
				getinf(&alldata);
				//pthread_create(&thread_id, NULL, getinf, &alldata);
				//pthread_detach(thread_id);
				//cout << "Yes4" << endl;
				usleep(500000);
			}
		}
		//pthread_mutex_unlock(&mutex);
	}

	// 解锁，pthread_mutex_lock()唤醒，不阻塞
	//pthread_mutex_unlock(&mutex);

	close(alldata.clnt_sock);
	return NULL;
}

int main(){

	int sum = 0;

	pthread_t thread_id;

	pthread_mutex_init(&mutex, NULL); // 初始化互斥锁，互斥锁默认是打开的

	//创建套接字
	int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//将套接字和IP、端口绑定
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));//每个字节都用0填充
	serv_addr.sin_family = AF_INET;//使用IPv4地址
        serv_addr.sin_addr.s_addr = inet_addr("xxx.xxx.xxx.xxx");//具体的IP地址
        serv_addr.sin_port = htons(xxx);//端口

	bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));//bind()绑定服务器端口，将套接字绑定到本地的地址和端口上


	while (1) {
		// 上锁，在没有解锁之前，pthread_mutex_lock()会阻塞
		//pthread_mutex_lock(&mutex);

		char type;
		char yes = 'Y';
		char no = 'N';

		int linenumber = 0;
		sum = get_user_number();
		cout << "sum=  " << sum << endl << endl;
		//UserData recvUser;


		//进入监听状态，等待用户发起请求
		listen(serv_sock, 200);//监听客户端连接accept()接受连接
		cout << "Listening......" << endl;

		//接收客户端请求
		char cli_ip[INET_ADDRSTRLEN] = "";
		struct sockaddr_in clnt_addr;
		socklen_t clnt_addr_size = sizeof(clnt_addr);
		int clnt_sock = -1;

		
		do {
			clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
			if (clnt_sock < 0) {
				printf("Connected Error, re-try to get connected with client ... \n");
			}
		} while (clnt_sock < 0);
		cout << "Successfully connected" << endl << endl;
		inet_ntop(AF_INET, &clnt_addr.sin_addr, cli_ip, INET_ADDRSTRLEN);
		cout << "client ip=" << cli_ip << ",port=" << ntohs(clnt_addr.sin_port) << endl;


		if (clnt_sock > 0) {
			Alldata alldata;
			int needRecv = sizeof(Alldata);
			char *recvMsg = (char*)malloc(needRecv);
			int len;
			int pos = 0;
			while (pos < needRecv) {
				len = recv(clnt_sock, recvMsg + pos, sizeof(Alldata), 0);
				if (len < 0) {
					cout << "Recieve Data Failed!" << endl;
					break;
				}
				pos += len;
			}
			memcpy(&alldata, recvMsg, sizeof(Alldata));
			alldata.clnt_sock = clnt_sock;
			cout << "sock is:  " << clnt_sock << endl;

			//给回调函数传的参数，&connfd，地址传递
			pthread_create(&thread_id, NULL, client, &alldata); //创建线程
			pthread_detach(thread_id); // 线程分离，结束时自动回收资源，不阻塞

			free(recvMsg);
		}

	}
	close(serv_sock);
    return 0;
}
