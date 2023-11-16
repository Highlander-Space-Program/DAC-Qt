#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <InfluxDB.h>
#include <InfluxDBFactory.h>

#include "TelemetryChannel.h"
#include "PressureData.h"
#include "visualizationcontext.h"
#include "LabJackSink.h"

int main(int argc, char *argv[])
{
  auto db = influxdb::InfluxDBFactory::Get("http://<token>@localhost:8086?db=burst_test");
  db->batchOf(100);

  TelemetryChannel<PressureData> channel;
  channel.subscribe([&db](const std::vector<PressureData>& buffer, const size_t size){
    // upload to influx
    std::vector<influxdb::Point> v;
    for (const auto& i : buffer) {
      db->write(influxdb::Point("test2")
        .setTimestamp(i.timestamp)
        .addField("pressure", i.pressure())
        .addField("voltage", i.voltage())
        .addTag("sensor", "pt-01"));
    }
    db->flushBatch();
  });

  LabJackSink lj_sink;
  int error = lj_sink.open();
  char err_str[LJM_MAX_NAME_SIZE];
  LJM_ErrorToString(error, err_str);
  if (error) std::cout << err_str << std::endl;

  lj_sink.pressure_channel = &channel;
  int scan_rate = 100;
  error = lj_sink.start_stream(scan_rate, scan_rate, {"AIN0"});
  LJM_ErrorToString(error, err_str);
  if (error) std::cout << err_str << std::endl;
  QApplication app(argc, argv);

  QQmlApplicationEngine engine;
  const QUrl url(u"qrc:/DAC-Qt/Main.qml"_qs);
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
    &app, []() { QCoreApplication::exit(-1); },
    Qt::QueuedConnection);

  VisualizationContext visualizationContext(&channel);
  engine.rootContext()->setContextProperty("visualizationContext", &visualizationContext);
  engine.load(url);

  int ret = app.exec();
  db->flushBatch();
  db.release();

  return ret;
}
