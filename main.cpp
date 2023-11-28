#include <vector>
#include <iostream>

#include <QApplication>
#include <QQmlApplicationEngine>

#include "broadcast/Broadcaster.h"
#include "broadcast/Sink.h"

#include "ForceData.h"
#include "PressureData.h"
#include "TemperatureData.h"

void PrintForceData(const ForceData* data) {
    std::cout << "MASS DATA CALLBACK :::: ";
    if (data) {
        std::cout << "Mass: " << data->mass << ", Voltage1: " << data->voltage1 << ", Voltage2: " << data->voltage2 << std::endl;
    } else {
      std::cout << "noData";
    }
}

void PrintPressureData(const PressureData* data) {
    std::cout << "Pressure DATA CALLBACK :::: ";
    if (data) {
        std::cout << "Pressure: " << data->pressure << ", Voltage1: " << data->voltage1 << ", Voltage2: " << data->voltage2 << std::endl;
    } else {
      std::cout << "noData";
    }
}

void PrintTemperatureData(const TemperatureData* data) {
    std::cout << "Temperature DATA CALLBACK :::: ";
    if (data) {
        std::cout << "weight???: " << data->weight << ", Voltage1: " << data->voltage1 << ", Voltage2: " << data->voltage2 << std::endl;
    } else {
      std::cout << "noData";
    }
}

int main(int argc, char *argv[])
{
  // ** TESTING ** //
  // run cmake then make then ./appDAC-Qt.app/Contents/MacOS/appDAC-Qt

  std::vector<std::shared_ptr<BroadcasterBase>> broadcasters;
  broadcasters.push_back(Broadcaster<ForceData>::getInstance());
  Broadcaster<ForceData>::getInstance()->subscribe(PrintForceData);
  broadcasters.push_back(Broadcaster<PressureData>::getInstance());
  Broadcaster<PressureData>::getInstance()->subscribe(PrintPressureData);


  Sink Sink1(broadcasters);
  Sink Sink2(broadcasters);

  ForceData* m1 = new ForceData();
  std::vector <TelemetryData*> mvec1 = {m1};

  Sink1.sendData(mvec1);

  ForceData* m2 = new ForceData();
  m2->mass = 0.1;
  m2->voltage1 = 2.3;
  m2->voltage2 = 2.4; 

  std::vector <TelemetryData*> mvec2 = {m2};
  Sink1.sendData(mvec2);



  ForceData* m3 = new ForceData();
  m3->mass = 1.2;
  m3->voltage1 = 3.4;
  m3->voltage2 = 6.9; 

  ForceData* m4 = new ForceData();
  m4->mass = -3.1;
  m4->voltage1 = 2.3;
  m4->voltage2 = -2.4; 

  PressureData* p1 = new PressureData();
  p1->pressure = -4.2;
  p1->voltage1 = 6.9;
  p1->voltage2 = 3.7; 

  std::vector <TelemetryData*> mvec3 = {m3, m4, p1};
  Sink1.sendData(mvec3);

  std::cout << "\n\nTesting Sink2\n";
  Sink2.sendData(mvec3);
  delete m1;
  delete m2;
  delete m3;
  delete m4;

  // ** TESTING ** //


  // QApplication app(argc, argv);

  // QQmlApplicationEngine engine;
  // const QUrl url(u"qrc:/DAC-Qt/Main.qml"_qs);
  // QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
  //   &app, []() { QCoreApplication::exit(-1); },
  //   Qt::QueuedConnection);
  // engine.load(url);

  // return app.exec();
}
