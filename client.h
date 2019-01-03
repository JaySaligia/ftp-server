#ifndef CLIENT_H
#define CLIENT_H
#include "winsock2.h"
#include <iostream>
#include "string.h"
using namespace std;

#pragma comment(lib,"ws2_32.lib")
//#pragma warning(disable:4996)

class client
{
public:
    client();
    string ipaddr;
    SOCKET hostsoc;//服务器套接字
    int linkstart();//连接测试
};

#endif // CLIENT_H
