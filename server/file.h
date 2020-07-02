#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<cstring>

#define USERFILE "user.txt"
#define USERFILE_BAK "user_bak.txt"

using namespace std;


int GetTxtLine(const char *filename);

int get_user_number();

string getLineinf(const char *filename, int line);

void write_data(const char *filename, char* data);

void write_usernumber(int sum, const char *filename);

void write_XXfile_to_XXfile(const char *filename1, const char *filename2);

void write_firstline_to_file(const char *filename1, const char *filename2);

void write_exceptoneinf_to_otherfile(const char *filename1, const char *filename2);

void change_sumuser(int sum);

void delete_online_user(string username);

int checkname(string name);

int checkid(string id);