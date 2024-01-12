#include <QApplication>
#include <QQmlApplicationEngine>

#include "broadcast/Broadcaster.h"
#include "models/ForceData.h"
#include "models/TemperatureData.h"
#include "models/PressureData.h"

#include <InfluxDBFactory.h>

int main(int argc, char *argv[])
{
  auto forceBroadcaster = Broadcaster<ForceData>::getInstance();
  auto temperatureBroadcaster = Broadcaster<TemperatureData>::getInstance();
  auto pressureBroadcaster = Broadcaster<PressureData>::getInstance();

  auto db = influxdb::InfluxDBFactory::Get("http://localhost:8086/?db=test");
  pressureBroadcaster->subscribe([&db](const PressureData *data){
      db->write(influxdb::Point{"test"}
      .addField("value", 10)
      .addTag("host", "localhost"));
  });

  QApplication app(argc, argv);

  QQmlApplicationEngine engine;
  const QUrl url(u"qrc:/DAC-Qt/Main.qml"_qs);
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
    &app, []() { QCoreApplication::exit(-1); },
    Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
