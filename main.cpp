#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  qDebug() << "main thread ID:" << QThread::currentThreadId();
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
