#include "client.h"

client::client()
{

}
int client::linkstart(){
    //return 1;
    int retval;//返回状态
    int serverlen;//套接字长度
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0){
        return -1;//初始化失败
    }

    hostsoc = socket(AF_INET,SOCK_STREAM, 0);//生成一个socket
    if (hostsoc == INVALID_SOCKET){
        WSACleanup();
        return -2;//套接字生成失败
    }
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(ipaddr.c_str());
    serveraddr.sin_port = htons((short)21);
    serverlen = sizeof(serveraddr);

    retval = connect(hostsoc, (LPSOCKADDR)&serveraddr, serverlen);

    if (retval == SOCKET_ERROR){
        closesocket(hostsoc);
        WSACleanup();
        return 0;
    }
    else{//验证用户名和密码
        string retval_name = "";
        string retval_pw = "";
        recv(hostsoc, revbuf, sizeof(revbuf), 0);
        //cout<<revbuf<<endl;//220 信息
        ZeroMemory(revbuf, BUFSIZE);

        sprintf(sendbuf, "USER %s\r\n", name.c_str());
        //cout<<sendbuf<<endl;
        send(hostsoc, sendbuf, strlen(sendbuf), 0);//不能用sizeof()，要用strlen()
        recv(hostsoc, revbuf, sizeof(revbuf), 0);//331
        for (int i = 0; i< 3; i++)
            retval_name += revbuf[i];
        cout<<retval_name<<endl;
        ZeroMemory(sendbuf, BUFSIZE);
        ZeroMemory(revbuf, BUFSIZE);

        sprintf(sendbuf, "PASS %s\r\n", pw.c_str());
        //cout<<sendbuf<<endl;
        send(hostsoc, sendbuf, strlen(sendbuf), 0);
        recv(hostsoc, revbuf, sizeof(revbuf), 0);//230
        for (int i = 0; i< 3; i++)
            retval_pw += revbuf[i];
        cout<<retval_pw<<endl;
        ZeroMemory(sendbuf, BUFSIZE);
        ZeroMemory(revbuf, BUFSIZE);

        if(retval_name == "331" && retval_pw == "230"){
            closesocket(hostsoc);
            WSACleanup();
            return 1;
        }
        else return -3;//用户名密码错误


    }
    return -4;

}

int client::download(){
  return 1;
}

