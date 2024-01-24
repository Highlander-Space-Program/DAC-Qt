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

  auto db = influxdb::InfluxDBFactory::Get("http://<token>@localhost:8086?db=dry_test");
  pressureBroadcaster->subscribe([&db](const PressureData *data){
    try {
      db->write(influxdb::Point{"dry_test"}
                        .addField("pressure", data->pressure())
                        .addField("voltage", data->voltage())
                        .addTag("sensor", data->label)
      );
    } catch (influxdb::InfluxDBException &e) {
      std::cerr << e.what() << std::endl;
    }
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
