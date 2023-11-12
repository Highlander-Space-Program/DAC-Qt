#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "TelemetryChannel.h"
#include "PressureData.h"
#include "visualizationcontext.h"
#include "LabJackSink.h"

int main(int argc, char *argv[])
{
  TelemetryChannel<PressureData> channel;
  channel.subscribe([](const std::vector<PressureData>& buffer, const size_t size){
    // upload to influx
  });

  LabJackSink lj_sink;
  int error = lj_sink.open();
  char err_str[LJM_MAX_NAME_SIZE];
  LJM_ErrorToString(error, err_str);
  if (error) std::cout << err_str << std::endl;

  lj_sink.pressure_channel = &channel;
  int scan_rate = 10000;
  error = lj_sink.start_stream(scan_rate/2, scan_rate, {"AIN0"});
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

  return app.exec();
}
