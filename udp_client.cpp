#include "udp_client.h"

volatile quint16 bindPort = 6000;

udp_client::udp_client(QObject *parent):QObject(parent)
{

                  client = new QUdpSocket(this);
                  //client->bind(QHostAddress("127.0.0.1"),bindPort);
                  client->bind(bindPort);
                  // 使用bind函数监听
                  // 一个QUdpSocket只能监听一个端口
                  connect(client,SIGNAL(readyRead()),this,SLOT(messageReceive()));

}

void udp_client::messageReceive()
{
        g_photo_data.resize(client->pendingDatagramSize());
        QHostAddress addr;
        quint16 port;
        client->readDatagram(g_photo_data.data(),g_photo_data.size(),&addr,&port);
        qDebug()<<"read datagram size:"<<g_photo_data.size()<<endl;
        emit show_photo();
}
