#ifndef WINSOCKET_H
#define WINSOCKET_H
#include <QUdpSocket>
#include <QCoreApplication>
#include <QDebug>
#include <QUdpSocket>
#include <QHostAddress>
#include "qthread.h"
#include <WinSock2.h>
#include <windows.h>
#include <QMessageBox>
#include <QDebug>

class winsocket : public QThread
{
   Q_OBJECT
public:
  winsocket();
  ~winsocket();
  void init(QString localIp,int localPort);

private:
    SOCKET msocket;
    sockaddr_in localAddr;
    sockaddr_in recvAddr;
    sockaddr_in remoteAddr;
    bool initSuccess;
    void run();

signals:
    void sendRecvData(char *data,int length,QString recvIp);

public slots:
    void dealRecvData(char *data,int length,QString recvIp);

};

#endif // WINSOCKET_H
