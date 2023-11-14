#include <vector>
#include <iostream>

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "broadcast/Broadcaster.hpp"
#include "broadcast/Sink.hpp"

#include "MassData.h"
#include "PressureData.h"

int main(int argc, char *argv[])
{
  // ** TESTING ** //
  // run cmake then make then ./appDAC-Qt.app/Contents/MacOS/appDAC-Qt

  std::vector<std::shared_ptr<BroadcasterBase>> broadcasters;
  broadcasters.push_back(Broadcaster<MassData>::getInstance());
  broadcasters.push_back(Broadcaster<PressureData>::getInstance());

  Sink Sink1(broadcasters);

  MassData m1;
  Sink1.sendData();

  MassData m2;
  m2.mass = 0.1;
  m2.voltage1 = 2.3;
  m2.voltage2 = 2.4; 
  Sink1.sendData();





  MassData m3;
  m3.mass = 1.2;
  m3.voltage1 = 3.4;
  m3.voltage2 = 6.9; 
  Sink1.sendData();

  MassData m4;
  m4.mass = -3.1;
  m4.voltage1 = 2.3;
  m4.voltage2 = -2.4; 
  Sink1.sendData();

  std::vector <MassData> mvec = {m3, m4}; 

  Sink Sink2(broadcasters);

  sink2.sendData()

  // ** TESTING ** //


  // QGuiApplication app(argc, argv);

  // QQmlApplicationEngine engine;
  // const QUrl url(u"qrc:/DAC-Qt/Main.qml"_qs);
  // QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
  //   &app, []() { QCoreApplication::exit(-1); },
  //   Qt::QueuedConnection);
  // engine.load(url);

  // return app.exec();
}
