#include <QApplication>
#include <QQmlApplicationEngine>
#include <QJsonDocument>
#include <QFile>
#include <QDir>

#include "sinks/LabJackSink.h"
#include "broadcast/Broadcaster.h"
#include "models/ForceData.h"
#include "models/TemperatureData.h"
#include "models/PressureData.h"
#include "Config.h"

#include <spdlog/spdlog.h>

Config read_config();

#include <InfluxDBFactory.h>

int main(int argc, char *argv[])
{
  spdlog::info("Starting DAC-Qt");
  QApplication app(argc, argv);
  
  Config config = read_config();

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

  LabJackSink lj_sink;
  try {
    lj_sink.openS("ANY", "-2", "ANY");
  } catch (LabJackException &e) {
    
  }
//  lj_sink.start_stream(100, 100, std::make_shared<InjectorTestStrategy>(pressureBroadcaster));

  QQmlApplicationEngine engine;
  // QString path = QString::fromStdString(std::string(BUILD_DIR) + "/../DAC-Qt/Main.qml");
  QString path = QString::fromStdString("./DAC-Qt/Main.qml");
  const QUrl url = QUrl::fromLocalFile(QDir::current().absoluteFilePath(path));
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
    &app, []() { QCoreApplication::exit(-1); },
    Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}

Config read_config() {
// CMAKE_CURRENT_BINARY_DIR
  // std::cout << "Build directory: " << BUILD_DIR << std::endl;
  // QString path = QString::fromStdString(std::string(BUILD_DIR) + "/config.json");
  // QFile f(path);
  // QFile f(path);

  QFile f("config.json");
  if(f.open(QIODevice::ReadOnly)) {
    Config config;
    QJsonDocument json = QJsonDocument::fromJson(f.readAll());
    config.labjack.identifier = json["labjack"]["identifier"].toString().toStdString();
    config.labjack.device_type = json["labjack"]["device_type"].toString().toStdString();
    config.labjack.connection_type= json["labjack"]["connection"].toString().toStdString();
    config.influx.address = json["influx"]["address"].toString().toStdString();
    config.influx.token = json["influx"]["token"].toString().toStdString();
    return config;
  } else {
    spdlog::error("Could not open config.json: {}", f.errorString().toStdString());
    // TODO handle (throw or show dialog)
  }
}