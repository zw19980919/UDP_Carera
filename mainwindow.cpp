#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->pushButton->setCheckable(true);

  udpSocket = new udp_client();
  udpThread = new QThread ;
  udpSocket->moveToThread(udpThread);
  udpThread->start();
  connect(udpSocket, &udp_client::show_photo, this, &MainWindow::show_photo);

//  winsockThread = new winsocket();
//  winsockThread->init("192.168.1.2", 6000);
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    qDebug()<<"HELLO WORLD "<<endl;

}

void MainWindow::on_pushButton_clicked(bool checked)
{
    QString ipv4 = ui->lineEdit->text();
    if(ipv4 == "")
    {
        ui->textBrowser->append("请输入一个正确ipv4地址");
    }
    qDebug()<<ipv4<<endl;
    qDebug()<<checked<<endl;
}


void MainWindow::show_photo(QByteArray *data)
{
    QImage image;
    qDebug() << "gui thread ID:" << QThread::currentThreadId();
    bool flag = image.loadFromData((uchar *)(data->data() + 4), data->size() - 8);
     qDebug()<<"show_photo size:"<<data->size()<<endl;
        if(flag)
        {
            QPixmap pixmap=QPixmap::fromImage(image);
            ui->label->setPixmap(pixmap);
            data->clear();
        }
}












