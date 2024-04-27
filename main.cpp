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
#include "sinks/LabJackSink.h"
#include "sinks/ColdFlowSinkStrategy.h"

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

  std::stringstream ss;
  ss << config.influx.protocol << "://" << config.influx.token << '@' << config.influx.address << ':' << config.influx.port << "?db=" << config.influx.db;
  std::cout << "Connection string: " << ss.str() << std::endl;
  std::string measurement = config.influx.measurement;
  std::cout <<  measurement << std::endl;
  auto db = influxdb::InfluxDBFactory::Get(ss.str());
  pressureBroadcaster->subscribe([&db, &measurement](const PressureData *data){
    try {
      db->write(influxdb::Point{measurement}
                        .addField("pressure", data->pressure())
                        .addField("voltage", data->voltage())
                        .addTag("sensor", data->label)
      );
    } catch (influxdb::InfluxDBException &e) {
      std::cerr << e.what() << std::endl;
    }
  });
  forceBroadcaster->subscribe([&db, &measurement](const ForceData *data){
    try {
      db->write(influxdb::Point{measurement}
                        .addField("force", data->force())
                        .addField("voltage", data->voltage())
                        .addTag("sensor", data->label)
      );
    } catch (influxdb::InfluxDBException &e) {
      std::cerr << e.what() << std::endl;
    }
  });

  auto pt02Data = std::make_shared<CalibratedPressureData>(425.37, -222.30); // PT 6
  auto pt03Data = std::make_shared<CalibratedPressureData>(410.41, -207.26); // PT 5
  auto pt04Data = std::make_shared<PressureData>(0, 1600, 0.5, 4.5); // PT 3
  auto pt05Data = std::make_shared<PressureData>(0, 1600, 0.5, 4.5); // PT 1
  auto pt06Data = std::make_shared<CalibratedPressureData>(406.16, -214.30); // PT 7
  auto lc01Data = std::make_shared<ForceData>(500, 0.002, 5);
  auto lc02Data = std::make_shared<ForceData>(1000, 0.002, 5);
  auto lc03Data = std::make_shared<ForceData>(1000, 0.002, 5);
  auto coldFlowStrategy = std::make_shared<ColdFlowSinkStrategy>(pt02Data,
                                                                 pt03Data,
                                                                 pt04Data,
                                                                 pt05Data,
                                                                 pt06Data,
                                                                 lc01Data,
                                                                 lc02Data,
                                                                 lc03Data,
                                                                 pressureBroadcaster,
                                                                 forceBroadcaster);

  LabJackSink lj_sink;
  lj_sink.openS(config.labjack.device_type, config.labjack.identifier, config.labjack.connection_type);
  lj_sink.start_stream(1, 10, coldFlowStrategy);

  QQmlApplicationEngine engine;
  // QString path = QString::fromStdString(std::string(BUILD_DIR) + "/../DAC-Qt/Main.qml");
  QString path = QString::fromStdString("../DAC-Qt/Main.qml");
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
    config.influx.protocol = json["influx"]["protocol"].toString().toStdString();
    config.influx.address = json["influx"]["address"].toString().toStdString();
    config.influx.port = json["influx"]["port"].toString().toStdString();
    config.influx.token = json["influx"]["token"].toString().toStdString();
    config.influx.db = json["influx"]["db"].toString().toStdString();
    config.influx.measurement = json["influx"]["measurement"].toString().toStdString();
    return config;
  } else {
    spdlog::error("Could not open config.json: {}", f.errorString().toStdString());
    // TODO handle (throw or show dialog)
  }
}