#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H
#include <QUdpSocket>
#include <QCoreApplication>
#include <QDebug>
#include <QUdpSocket>
#include <QHostAddress>
#include "qthread.h"
#include <WinSock2.h>


class udp_client: public QObject
{
  Q_OBJECT
  public:
  #define photo_size 10
  udp_client(QObject *parent = nullptr);
  QByteArray g_photo_data[photo_size];     //全局图像数据,接收可能比处理更频繁
  int photo_offset = 0;                    //现在待发送的图像数据是第几个
  private:
          QUdpSocket *client;

  private slots:
          void messageReceive();

  signals:
    void show_photo(QByteArray *data);
};


#endif // UDP_CLIENT_H

