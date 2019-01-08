#include "client.h"

client::client()
{

}
int client::linkstart(){
    //return 1;
    char sendbuf[BUFSIZE];//发送缓冲区
    char revbuf[BUFSIZE];//接受缓冲区
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
        //cout<<retval_name<<endl;
        ZeroMemory(sendbuf, BUFSIZE);
        ZeroMemory(revbuf, BUFSIZE);

        sprintf(sendbuf, "PASS %s\r\n", pw.c_str());
        //cout<<sendbuf<<endl;
        send(hostsoc, sendbuf, strlen(sendbuf), 0);
        recv(hostsoc, revbuf, sizeof(revbuf), 0);//230
        for (int i = 0; i< 3; i++)
            retval_pw += revbuf[i];
        //cout<<retval_pw<<endl;
        ZeroMemory(sendbuf, BUFSIZE);
        ZeroMemory(revbuf, BUFSIZE);

        if(retval_name == "331" && retval_pw == "230"){
            //closesocket(hostsoc);
            //WSACleanup();
            return 1;
        }
        else return -3;//用户名密码错误


    }
    return -4;//其他错误

}



int client::upload(const char *openfile){
    char sendbuf[BUFSIZE];
    char recvbuf[BUFSIZE];
    char databuf[BUFSIZE];
    ssize_t len, send_len;
    int result;
    FILE * f;
    f = fopen(openfile, "rb");
    if (NULL == f)
    return -1;//文件不存在

    //寻找相对目录
    char *s = new char[100];
    strcpy(s, openfile);
    char *p;
    char *filename;
    const char *d = "/";
    p = strtok(s,d);
        while(p)
        {
            filename = p;
            p=strtok(NULL,d);
        }
    //cout<<filename<<endl;

    if(!this->pasvstart())
        return -2;//被动模式开启失败

    ZeroMemory(sendbuf, BUFSIZE);
    sprintf(sendbuf, "STOR %s\r\n", filename);
    send(hostsoc, sendbuf, strlen(sendbuf), 0);
    ZeroMemory(databuf, BUFSIZE);
    while ((len = fread(databuf, 1, BUFSIZE, f)) > 0)
    {
        //cout<<databuf<<endl;
        send_len = send(hostsocpasv, databuf, len, 0);
        if(send_len != len)
        {
            closesocket(hostsocpasv);
            fclose(f);
            return -3;//发送文件失败
        }

    }
    closesocket(hostsocpasv);
    fclose(f);
    ZeroMemory(recvbuf, BUFSIZE);
    len = recv(hostsoc, recvbuf, BUFSIZE, 0);
    //cout<<recvbuf<<endl;
    recvbuf[len] = 0;
    sscanf(recvbuf, "%d", &result);
    if(result == 150)
    {
        closesocket(hostsoc);
        return 1;//上传成功
    }
    return -3;

}

int client::pasvstart(){//开启pasv套接字
    char sendbuf[BUFSIZE];
    char recvbuf[BUFSIZE];
    int addr[6];
    int retval;
    int serverlen;
    string retval_msg = "";

    ZeroMemory(sendbuf, BUFSIZE);
    sprintf(sendbuf, "PASV\r\n");
    send(hostsoc, sendbuf, strlen(sendbuf), 0);
    recv(hostsoc, recvbuf, sizeof(recvbuf), 0);
    sscanf(recvbuf, "%*[^(](%d,%d,%d,%d,%d,%d)",&addr[0],&addr[1],&addr[2],&addr[3],&addr[4],&addr[5]);

    hostsocpasv = socket(AF_INET,SOCK_STREAM, 0);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(ipaddr.c_str());
    serveraddr.sin_port = htons((short)addr[4]*256+addr[5]);
    serverlen = sizeof(serveraddr);
    retval = connect(hostsocpasv, (LPSOCKADDR)&serveraddr, serverlen);
    if (retval == SOCKET_ERROR)
        return 0;
    return 1;
}

void client::finish(){
    closesocket(hostsoc);
    WSACleanup();
}

