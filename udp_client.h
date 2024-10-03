#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H
#include <QUdpSocket>
#include <QCoreApplication>
#include <QDebug>
#include <QUdpSocket>
#include <QHostAddress>
//#include <QNetworkDatagram>


class udp_client: public QObject
{
  Q_OBJECT
  public:
  udp_client(QObject *parent = nullptr);
  QByteArray g_photo_data;//全局图像数据

  private:
          QUdpSocket *client;

  private slots:
          void messageReceive();

  signals:
    void show_photo();
};


#endif // UDP_CLIENT_H

