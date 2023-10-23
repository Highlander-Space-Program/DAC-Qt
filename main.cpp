#include "mainwindow.h"
#include "mass_data.h"
#include "temperature_data.h"
#include "pressure_data.h"

#include <QApplication>

#include <iostream>
#include <LabJackM.h>

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
  MainWindow w;
  w.show();
  return a.exec();
}
