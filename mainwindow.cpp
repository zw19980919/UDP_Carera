#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->pushButton->setCheckable(true);
  udpSocket = new udp_client(this);
  connect(udpSocket, &udp_client::show_photo, this, &MainWindow::show_photo);
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


void MainWindow::show_photo()
{
    QImage image;
    bool flag = image.loadFromData((const uchar *)udpSocket->g_photo_data.data(),udpSocket->g_photo_data.size());
     qDebug()<<"show_photo size:"<<udpSocket->g_photo_data.size()<<endl;
        if(flag)
        {
            QPixmap pixmap=QPixmap::fromImage(image);
            ui->label->setPixmap(pixmap);
            udpSocket->g_photo_data.clear();
        }
}












