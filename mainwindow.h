#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "udp_client.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_pushButton_clicked();
  void on_pushButton_clicked(bool checked);

  void show_photo();

private:
  Ui::MainWindow *ui;
  udp_client *udpSocket;
};
#endif // MAINWINDOW_H
