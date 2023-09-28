#include "mainwindow.h"

#include <QApplication>

#include <iostream>
#include <LabJackM.h>

int main(int argc, char *argv[])
{
  int error, handle;

  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
