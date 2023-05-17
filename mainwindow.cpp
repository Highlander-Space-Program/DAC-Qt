#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include <QFile>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QDebug>
#include <QDateTime>

#include <LabJackM.h>

QT_BEGIN_NAMESPACE

using json = nlohmann::json;
using namespace std::chrono;

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  charts.push_back(createPtChart());
  chartView = new QChartView(charts.front());

  chartView->setRenderHint(QPainter::Antialiasing);
  ui->gridLayout->addWidget(chartView);
}

MainWindow::~MainWindow()
{
  delete ui;
}

QChart* MainWindow::createPtChart() {
  int error, handle;
  error = LJM_OpenS("T7", "USB", "ANY", &handle);
  if (error) {
    char errorStr[LJM_MAX_NAME_SIZE];
    LJM_ErrorToString(error, errorStr);
    qCritical() << "Error connecting to DAQ device: " << errorStr << Qt::endl;
  } else {
    int deviceType,
      connectionType,
      serialNumber;
    LJM_GetHandleInfo(handle, &deviceType, &connectionType, &serialNumber, nullptr, nullptr, nullptr);
    qInfo() << "Connected to DAQ device: " << deviceType << " : " << serialNumber << Qt::endl;
  }

  // Read from json
  json input;
  std::ifstream f("data/pt_data.json", std::ios::in);
  if (f.fail()) {
    qWarning() << "Error opening pressure transducer data file\n";
    return nullptr;
  }
  input = json::parse(f);

  // Create chart
  QChart *chart = new QChart();
  chart->setTitle("Pressure vs. Time");

  // Setup data series
  QLineSeries *series = new QLineSeries();
  for (const auto& point : input["data"]) {
    QDateTime dt;
    microseconds timestamp(static_cast<long long>(static_cast<double>(point[0])*1000000.0));
    dt.setMSecsSinceEpoch(duration_cast<milliseconds>(timestamp).count());
    series->append(dt.toMSecsSinceEpoch(), point[1].get<double>());
  }
  f.close();
  chart->addSeries(series);

  // Setup axes
  QDateTimeAxis *xaxis = new QDateTimeAxis();
  xaxis->setFormat("hh:mm:ss.zzz");
  xaxis->setTitleText("Timestamp");
  chart->addAxis(xaxis, Qt::AlignBottom);
  series->attachAxis(xaxis); // Attach axis *after* adding it to the chart

  QValueAxis *yaxis = new QValueAxis();
  yaxis->setLabelFormat("%i");
  yaxis->setTitleText("Pressure (psi)");
  chart->addAxis(yaxis, Qt::AlignLeft);
  series->attachAxis(yaxis);

  return chart;
}

QT_END_NAMESPACE
