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
#include <cstdio>
#include "file.h"

using namespace std;

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

struct LOGIN_UserData
{
	char Username[20] = { 0 };
	char UserID[20] = { 0 };
	char UserPassword[20] = { 0 };
	char judge = 'N';
};

struct SIGNUP_UserData
{
	char Name[20] = { 0 };
	char UserID[20] = { 0 };
	char UserPassword[20] = { 0 };
};