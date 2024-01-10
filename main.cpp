#include <QApplication>
#include <QQmlApplicationEngine>

#include "broadcast/Broadcaster.h"
#include "models/ForceData.h"
#include "models/TemperatureData.h"
#include "models/PressureData.h"
#include "sinks/LabJackSink.h"
#include "sinks/LabJackSinkStrategy.h"

int main(int argc, char *argv[])
{
  auto forceBroadcaster = Broadcaster<ForceData>::getInstance();
  auto temperatureBroadcaster = Broadcaster<TemperatureData>::getInstance();
  auto pressureBroadcaster = Broadcaster<PressureData>::getInstance();

  pressureBroadcaster->subscribe([](const PressureData* data){
    std::cout << data->label << ": " << data->pressure() << std::endl;
  });

  LabJackSink labJackSink;
  labJackSink.openS("ANY", "ANY", "ANY");
  labJackSink.start_stream(1, 1, std::make_shared<InjectorTestStrategy>(pressureBroadcaster));

  QApplication app(argc, argv);

  QQmlApplicationEngine engine;
  const QUrl url(u"qrc:/DAC-Qt/Main.qml"_qs);
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
    &app, []() { QCoreApplication::exit(-1); },
    Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
