#include"file.h"
#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<cstring>

using namespace std;

int GetTxtLine(const char *filename) {//行数
    FILE *fd;
    int count = 0;
    if (fd = fopen(filename, "r")) {
        while (!feof(fd)) {
            if ('\n' == fgetc(fd)) {
                count++;
            }
        }
    }
    count++;
    if (fd) {
        fclose(fd);
    }
    return count;
}

int get_user_number() {
    string line;
    ifstream userfile;
    userfile.open(USERFILE);//读取第一行的用户数
    getline(userfile, line);
    userfile.close();
    int sum = std::stoi(line);
    return sum;
}

string getLineinf(const char *filename, int n) {//返回n行文件的内容
    string line;
    ifstream file;
    file.open(filename);
    while (n--) {
        getline(file, line);
    }
    return line;
}

void write_data(const char *filename, char* data) {
    ofstream file;
    file.open(filename, ios::app);
    file << "\n" << data;
    file.close();
}

void write_XXfile_to_XXfile(const char *filename1, const char *filename2) { //复制一个文件的内容
    ifstream userfile;
    ofstream userfile_bak;
    userfile.open(filename1, ios::binary);
    userfile_bak.open(filename2, ios::binary);
    userfile_bak << userfile.rdbuf();
    userfile.close();
    userfile_bak.close();
}

void write_firstline_to_file(const char *filename1, const char *filename2) {//将一个文件的第一行写到另一个文件上
    string line;
    ifstream userfile;
    ofstream userfile_bak;
    userfile.open(filename1);
    userfile_bak.open(filename2);
    getline(userfile, line);
    userfile_bak << line;
    userfile.close();
    userfile_bak.close();
}

void write_exceptoneinf_to_otherfile(const char *filename1, const char *filename2) {//追加除原文件第一行的内容外的内容到新文件
    string line;
    ifstream userfile;
    ofstream userfile_bak;
    userfile.open(filename1);
    userfile_bak.open(filename2, ios::app);
    int sumline = GetTxtLine(filename1);
    for (int l = 1; l <= sumline; l++) {
        getline(userfile, line);
        if (l > 1) {
            userfile_bak << "\n" << line;
        }
    }
    userfile.close();
    userfile_bak.close();
}

void write_usernumber(int sum, const char *filename) {//只写入用户数
    string sumuser;
    ofstream file;
    file.open(filename);
    sumuser = std::to_string(sum);
    file << sumuser;
    file.close();
}

void change_sumuser(int sum) {
    write_usernumber(sum, USERFILE_BAK);
    write_exceptoneinf_to_otherfile(USERFILE, USERFILE_BAK);
    write_XXfile_to_XXfile(USERFILE_BAK, USERFILE);
}

void delete_online_user(string username) {//用户离线，从在线列表中删除
    string line;
    int n = 0;
    int txtline = GetTxtLine("useronline.txt");
    ifstream ifile_;
    ifile_.open("useronline.txt");
    for (int i = 1; i <= txtline; i++) {
        getline(ifile_, line);
        if (line == username) {
            n = i;
            break;
        }
    }
    ifile_.close();

    ifstream ifile;
    ofstream ofile;
    ifile.open("useronline.txt");
    ofile.open("useronline_bak.txt");
    for (int i = 1; i <= txtline; i++) {
        getline(ifile, line);
        if (i == n) continue;
        if (i == 1) ofile << line;
        else {
            if (n == 1 && i == 2) ofile << line;
            else ofile << "\n" << line;
        }
    }
    ifile.close();
    ofile.close();
    write_XXfile_to_XXfile("useronline_bak.txt", "useronline.txt");

    txtline = GetTxtLine("usersocket.txt");
    ifstream ifile2_;
    ifile2_.open("usersocket.txt");
    for (int i = 1; i <= txtline; i++) {
        getline(ifile2_, line);
        if (line == username) {
            n = i;
            break;
        }
    }
    ifile2_.close();

    ifstream ifile2;
    ofstream ofile2;
    ifile2.open("usersocket.txt");
    ofile2.open("usersocket_bak.txt");
    for (int i = 1; i <= txtline; i++) {
        getline(ifile2, line);
        if (i == n || i == n + 1) continue;
        if (i == 1) ofile2 << line;
        else {
            if (n == 1 && i == 3) ofile2 << line;
            else ofile2 << "\n" << line;
        }
    }
    ifile2.close();
    ofile2.close();
    write_XXfile_to_XXfile("usersocket_bak.txt", "usersocket.txt");
}
