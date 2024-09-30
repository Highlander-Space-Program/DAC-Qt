#include <QApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QFile>

#include <InfluxDBFactory.h>
#include <spdlog/spdlog.h>

#include "broadcast/Broadcaster.h"
#include "models/ForceData.h"
#include "models/TemperatureData.h"
#include "models/PressureData.h"
#include "sinks/LabJackSink.h"
#include "sinks/ColdFlowSinkStrategy.h"
#include "mainwindow.h"
#include "subscriberqtadapter.h"

int main(int argc, char *argv[])
{
  spdlog::info("Starting DAC-Qt");

  QCoreApplication::setOrganizationName("Highlander Space Program");
  QCoreApplication::setOrganizationDomain("https://github.com/Highlander-Space-Program/");
  QCoreApplication::setApplicationName("DAQ-Qt");

  QSettingsWrapper settings;
  // Set empty keys to default values
  settings.setValue("labjack/identifier", settings.value("labjack/identifier", "ANY"));
  settings.setValue("labjack/device_type", settings.value("labjack/device_type", "ANY"));
  settings.setValue("labjack/connection_type", settings.value("labjack/connection_type", "ANY"));
  settings.setValue("influx/protocol", settings.value("influx/protocol", "http"));
  settings.setValue("influx/address", settings.value("influx/address", "localhost"));
  settings.setValue("influx/port", settings.value("influx/port", "8086"));
  settings.setValue("influx/db", settings.value("influx/db", ""));
  settings.setValue("influx/measurement", settings.value("influx/measurement", ""));
  settings.setValue("influx/token", settings.value("influx/token", ""));

  auto forceBroadcaster = Broadcaster<ForceData>::getInstance();
  auto temperatureBroadcaster = Broadcaster<TemperatureData>::getInstance();
  auto pressureBroadcaster = Broadcaster<PressureData>::getInstance();

  std::stringstream ss;
  ss << settings.value("influx/protocol").toString().toStdString()
     << "://"
     << settings.value("influx/token").toString().toStdString()
     << '@'
     << settings.value("influx/address").toString().toStdString()
     << ':'
     << settings.value("influx/port").toString().toStdString()
     << "?db="
     << settings.value("influx/db").toString().toStdString();
  std::string measurement = settings.value("influx/measurement").toString().toStdString();

  spdlog::info("InfluxDB connection string: {}", ss.str());
  spdlog::info("InfluxDB measurement: {}", measurement);

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
//  lj_sink.openS(settings.value("labjack/device_type", settings.value("labjack/identifier", settings.value("labjack/connection_type");
//  lj_sink.start_stream(1, 10, coldFlowStrategy);

  //PressureSubscriberQtAdapter pressureQtSubscriber(*pressureBroadcaster);
  PressureSubscriberQtAdapter pressureQtSubscriber;

  QApplication app(argc, argv);
  MainWindow main_window_context(&settings);

  QQmlApplicationEngine engine;
  const QUrl url(u"qrc:/DAC-Qt/Main.qml"_qs);
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
    &app, []() { QCoreApplication::exit(-1); },
    Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("context", &main_window_context);
  engine.load(url);

  return app.exec();
}