#include "winsocket.h"

winsocket::winsocket()
{
   initSuccess=false;
}


winsocket::~winsocket()
{
   if(initSuccess)
   {
       ::closesocket(msocket);
       ::WSACleanup();
       requestInterruption();//要求中断
       wait();//等待线程释放
   }
}

void winsocket::init(QString localIp,int localPort)
{
  qDebug("enter windock init");
    int retValue;
    //初始化网络环境
    WSADATA wsaData;
    WORD sockVersion = MAKEWORD(2, 2);
    retValue=::WSAStartup(sockVersion, &wsaData);
    if(retValue!=0)
    {
        qDebug("Socket环境初始化失败");
        QMessageBox::information(NULL,"错误提示","Socket环境初始化失败");
        return;
    }

    //创建socket
    msocket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (msocket == INVALID_SOCKET)
    {
        qDebug("创建socket出错");
        QMessageBox::information(NULL,"错误提示","创建socket出错");
        ::WSACleanup();
        return;
    }

    localAddr.sin_family = AF_INET;
//    localAddr.sin_addr.s_addr = inet_addr(localIp.toLatin1());
//    localAddr.sin_port = ::htons(localPort);
    localAddr.sin_addr.s_addr = inet_addr("192.168.1.2");
    localAddr.sin_port = ::htons(6000);
    //绑定函数
    int bufferSize = 16*2048*1288;
    setsockopt(msocket, SOL_SOCKET, SO_RCVBUF, (const char*)&bufferSize, sizeof(bufferSize));

    retValue= ::bind(msocket, (struct sockaddr*)&localAddr, sizeof(sockaddr_in));
    if(retValue==-1)
    {
        qDebug("绑定IP和端口出错");
        QMessageBox::information(NULL,"错误提示","绑定IP和端口出错");
        ::closesocket(msocket);
        ::WSACleanup();
        return;
    }

    //信号槽连接函数
    connect(this,SIGNAL(sendRecvData(char *,int,QString)),this,SLOT(dealRecvData(char *,int,QString)));

    //设置阻塞函数
    int imode = 0;
    ioctlsocket(msocket,FIONBIO,(u_long FAR*)&imode);
    if(retValue==SOCKET_ERROR)
    {
        qDebug("阻塞函数设置失败");
        QMessageBox::information(NULL,"错误提示","阻塞函数设置失败");
        ::closesocket(msocket);
        ::WSACleanup();
        return;
    }
     qDebug("线程调用");
    //线程调用
    start();
    initSuccess=true;
}


void winsocket::run()
{
    int length=0;
    int sockAddrSize=sizeof(sockaddr_in);
    char *buff = new char[10000];
    while(false==this->isInterruptionRequested())
    {
       qDebug()<<"子线程ThreadID: "<<QThread::currentThreadId();
       length=::recvfrom(msocket, (char*)buff, 10000, 0, (struct sockaddr*)&recvAddr, &sockAddrSize);
       qDebug("read winsocket len:%d", length);
       if (length == -1) {
           perror("recvfrom error");
           // 或者使用 strerror(errno) 获取更详细的错误信息
           fprintf(stderr, "recvfrom error: %s\n", strerror(errno));
       }
       qDebug("read winsocket error%d", errno);
       //sleep(1);
    }
}

void winsocket::dealRecvData(char data[],int length,QString recvIp)
{
    qDebug()<<data<<" "<<length<<" "<<recvIp;
}
