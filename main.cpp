#include "mainwindow.h"

#include <QApplication>

#include <iostream>
#include <LabJackM.h>
#include <QtWidgets>

int main(int argc, char *argv[])
{
  int error, handle;
  error = LJM_OpenS("T7", "USB", "-2", &handle);
  if (error) {
      char errorStr[LJM_MAX_NAME_SIZE];
      LJM_ErrorToString(error, errorStr);
      std::cerr << "Error connecting to DAQ device: " << errorStr << std::endl;
    } else {
      int deviceType,
        connectionType,
        serialNumber;
      LJM_GetHandleInfo(handle, &deviceType, &connectionType, &serialNumber, nullptr, nullptr, nullptr);
      std::cout << "Connected to DAQ device: " << deviceType << " : " << serialNumber << std::endl;
    }

  QApplication a(argc, argv);
  QWidget w;
  QLabel *label = new QLabel(QApplication::translate("windowlayout", "Name:"));
  QLineEdit *lineEdit = new QLineEdit();

  QHBoxLayout *layout = new QHBoxLayout();
  layout->addWidget(label);
  layout->addWidget(lineEdit);
  w.setLayout(layout);
  w.setWindowTitle(
      QApplication::translate("windowlayout", "Window layout"));
  w.show();
  return a.exec();
}
