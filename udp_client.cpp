#include "udp_client.h"

volatile quint16 bindPort = 6000;

udp_client::udp_client(QObject *parent = 0):QObject(parent)
{

                  client = new QUdpSocket(this);
                  client->bind(bindPort);
                  // 使用bind函数监听
                  // 一个QUdpSocket只能监听一个端口
                  connect(client,SIGNAL(readyread()),this,SLOT(messageReceive()));

}
