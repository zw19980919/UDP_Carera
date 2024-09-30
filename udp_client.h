#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H
#include <QUdpSocket>

class udp_client
{
   Q_OBJECT
  public:
  udp_client(QObject *parent = nullptr);
  private:
          QUdpSocket *client;

  private slots:
          void messageReceive()
          {
                  QByteArray data;
                  data.resize(client->pendingDatagramSize());
                  QHostAddress addr;
                  quint16 port;
                  client->readDatagram(data.data(),data.size(),&addr,&port);

          }
  };

#endif // UDP_CLIENT_H
