#ifndef CLIENT_H
#define CLIENT_H
#include "winsock2.h"
#include <iostream>
#include "string.h"
#include "dialogupload.h"
#include "QApplication.h"

using namespace std;




class client
{
public:
    client();
    string ipaddr;//服务器ip地址
    string name;//登陆用户名
    string pw;//登陆密码
    WSADATA wsa;//wsadata
    SOCKET hostsoc;//服务器套接字
    SOCKADDR_IN serveraddr;//服务器地址
    CONST int BUFSIZE = 64;
    int linkstart();//连接服务器
    int upload(const char *openfile);//上传文件
    SOCKET pasvstart();//开启被动连接
    void finish();//结束套接字
    int download(const char *storedir, const char *downloadfile);//下载文件
};

#endif // CLIENT_H
