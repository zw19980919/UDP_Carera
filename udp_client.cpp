#include "udp_client.h"

volatile quint16 bindPort = 6000;

udp_client::udp_client(QObject *parent):QObject(parent)
{

                  client = new QUdpSocket(this);
                  client->bind(QHostAddress("192.168.1.2"),bindPort);
                  client->setReadBufferSize(16*1024*1024); //设置16兆
                  //client->bind(bindPort);
                  // 使用bind函数监听
                  // 一个QUdpSocket只能监听一个端口
                  connect(client,SIGNAL(readyRead()),this,SLOT(messageReceive()));

}

void udp_client::messageReceive()
{
  QHostAddress addr;
  quint16 port;
  int realsize;
  int datagramsize = 0;
  qDebug()<<"start photo data*************************************************"<<endl;
  qDebug() << "udp thread ID:" << QThread::currentThreadId();
  while(client->hasPendingDatagrams())
    {
//        qDebug()<<"client size1:"<<client->pendingDatagramSize()<<endl;
//        g_photo_data[photo_offset].resize((client->pendingDatagramSize()+ datagramsize));
//        realsize = client->readDatagram((g_photo_data[photo_offset].data() + datagramsize), g_photo_data[photo_offset].size(), &addr,&port);
//        datagramsize = realsize + datagramsize;
//        qDebug()<<"realsize:"<<realsize<<endl;

        //qDebug()<<"client size1:"<<client->pendingDatagramSize()<<endl;
        g_photo_data[photo_offset].resize(client->pendingDatagramSize());
        realsize = client->readDatagram(g_photo_data[photo_offset].data(), g_photo_data[photo_offset].size(), &addr,&port);
        qDebug()<<"realsize:"<<realsize<<endl;
        break;
    }
  for(int i = 0; i < 5; i++)
    {
      qDebug("%02x",(uint8_t)(g_photo_data[photo_offset][i]));
    }
  qDebug()<<endl;
  qDebug()<<"g_photo_data size:"<<g_photo_data[photo_offset].size()<<endl;
  if(*((unsigned int*)g_photo_data[photo_offset].data()) == g_photo_data[photo_offset].size())
    {
      qDebug()<<"send photo data::::::::"<<endl;
      emit show_photo(&g_photo_data[photo_offset]);
      photo_offset = (photo_offset + 1) % photo_size;
    }
  qDebug()<<"end photo data*************************************************"<<endl;
}
