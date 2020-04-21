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
        recv(hostsoc, revbuf, sizeof(revbuf), 0);//220状态字
        ZeroMemory(revbuf, BUFSIZE);

        sprintf(sendbuf, "USER %s\r\n", name.c_str());

        send(hostsoc, sendbuf, strlen(sendbuf), 0);//不能用sizeof()，要用strlen()
        recv(hostsoc, revbuf, sizeof(revbuf), 0);//331状态字
        for (int i = 0; i< 3; i++)
            retval_name += revbuf[i];

        ZeroMemory(sendbuf, BUFSIZE);
        ZeroMemory(revbuf, BUFSIZE);

        sprintf(sendbuf, "PASS %s\r\n", pw.c_str());

        send(hostsoc, sendbuf, strlen(sendbuf), 0);
        recv(hostsoc, revbuf, sizeof(revbuf), 0);//230
        for (int i = 0; i< 3; i++)
            retval_pw += revbuf[i];

        ZeroMemory(sendbuf, BUFSIZE);
        ZeroMemory(revbuf, BUFSIZE);

        if(retval_name == "331" && retval_pw == "230"){
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
    SOCKET hostsocpasv = pasvstart();
    //if(!this->pasvstart())
      //  return -2;//被动模式开启失败

    ZeroMemory(sendbuf, BUFSIZE);
    sprintf(sendbuf, "STOR %s\r\n", filename);
    send(hostsoc, sendbuf, strlen(sendbuf), 0);
    ZeroMemory(databuf, BUFSIZE);
    while ((len = fread(databuf, 1, BUFSIZE, f)) > 0)
    {
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
    recvbuf[len] = 0;
    sscanf(recvbuf, "%d", &result);
    if(result == 150)
    {
        return 1;//上传成功
    }
    return -3;
}

int client::download(const char *storedir,const char *downloadfile){//下载文件，第一个参数是本地保存文件夹路径，第二个参数是需要下载的服务器文件名称
    ssize_t len, write_len;
    char sendbuf[BUFSIZE];
    char recvbuf[BUFSIZE];
    char databuf[BUFSIZE];
    int result;
    if (!strlen(storedir))
        return -1;//本地目录不存在
    if (!strlen(downloadfile))
        return -2;//未指定下载文件
    string a = storedir;
    string b = downloadfile;
    string c = a + "/" + b;
    const char *filename = c.c_str();



    sprintf(sendbuf, "TYPE I\r\n");//指定传输模式
    send(hostsoc, sendbuf, strlen(sendbuf), 0);
    recv(hostsoc, recvbuf, sizeof(recvbuf), 0);

    SOCKET hostsocpasv = pasvstart();

    ZeroMemory(sendbuf, sizeof(sendbuf));
    ZeroMemory(recvbuf, sizeof(recvbuf));
    sprintf(sendbuf, "RETR %s\r\n", downloadfile);
    send(hostsoc, sendbuf, strlen(sendbuf), 0);
    len = recv(hostsoc, recvbuf, sizeof(recvbuf), 0);
    recvbuf[len] = 0;
    sscanf(recvbuf, "%d", &result);
    if(result != 150)
        return -2;//文件不存在
    FILE *f = fopen(filename, "ab");
    if(f == NULL)
    {
        return -1;
    }
    ZeroMemory(databuf, sizeof(databuf));
    //判断有无断点

    FILE *f_b = fopen(filename, "r");
    int filesize = 0;
    int chunk = 0;
    int appendix = 0;
    if(f_b)//有断点
    {
        fseek(f_b, 0, SEEK_END);   ///将文件指针移动文件结尾
        filesize = ftell(f_b);
        chunk = filesize / BUFSIZE;
        appendix = filesize - chunk * BUFSIZE;
    }
    fclose(f_b);
    int count = 0;
    while(count < chunk){
        recv(hostsocpasv, databuf, BUFSIZE, 0);
        count ++;
    }
    char appendixbuf[appendix];
    ZeroMemory(appendixbuf, sizeof(appendixbuf));
    recv(hostsocpasv, appendixbuf, appendix, 0);
    printf("filesize:%d\n", filesize);
    fseek(f, (long)filesize, SEEK_SET);
    while ((len = recv(hostsocpasv, databuf, BUFSIZE, 0)) > 0) {
                printf("len:%d\n", len);
                write_len = fwrite(&databuf, len, 1, f);
                if (write_len != 1) //写入文件不完整
                {
                    closesocket(hostsocpasv); //关闭套接字
                    fclose(f); //关闭文件
                    return -1;
                }
        }

    fclose(f);
    closesocket(hostsocpasv);
    return 1;
}

SOCKET client::pasvstart(){//开启pasv套接字
    SOCKET hostsocpasv;
    char sendbuf[BUFSIZE];
    char recvbuf[BUFSIZE];
    int addr[6];
    int retval;
    int serverlen;
    int result = 0;
    ssize_t len;


    ZeroMemory(sendbuf, BUFSIZE);
    sprintf(sendbuf, "PASV\r\n");
    send(hostsoc, sendbuf, strlen(sendbuf), 0);
    while (result != 227){
    ZeroMemory(recvbuf, sizeof(recvbuf));
    len = recv(hostsoc, recvbuf, sizeof(recvbuf), 0);
    recvbuf[len] = 0;
    sscanf(recvbuf, "%d", &result);
    }
    sscanf(recvbuf, "%*[^(](%d,%d,%d,%d,%d,%d)",&addr[0],&addr[1],&addr[2],&addr[3],&addr[4],&addr[5]);
    //新建一个pasv套接字
    hostsocpasv = socket(AF_INET,SOCK_STREAM, 0);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(ipaddr.c_str());
    serveraddr.sin_port = htons((short)addr[4]*256+addr[5]);
    serverlen = sizeof(serveraddr);
    retval = connect(hostsocpasv, (LPSOCKADDR)&serveraddr, serverlen);
    if (retval == SOCKET_ERROR)
        return 0;
    return hostsocpasv;
}

void client::finish(){
    closesocket(hostsoc);
    WSACleanup();
}

