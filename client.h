#ifndef CLIENT_H
#define CLIENT_H
#include "winsock2.h"
#include <iostream>
#include "string.h"

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
    char sendbuf[64];//发送缓冲区
    char revbuf[64];//接受缓冲区
    int linkstart();//连接服务器
};

#endif // CLIENT_H
