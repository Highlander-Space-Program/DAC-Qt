#ifndef VISUALIZATIONCONTEXT_H
#define VISUALIZATIONCONTEXT_H

#include <QObject>
#include <QAbstractSeries>
#include <QXYSeries>
#include <iostream>

#include <LabJackM.h>
#include <QDateTime>
#include <QDateTimeAxis>
#include <fstream>
#include "PressureData.h"
#include "TelemetryChannel.h"

class VisualizationContext : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QDateTime minX READ minX WRITE setMinX NOTIFY onMinXChanged)
  Q_PROPERTY(QDateTime maxX READ maxX WRITE setMaxX NOTIFY onMaxXChanged)
  Q_PROPERTY(QString currentValue READ currentValue WRITE setCurrentValue NOTIFY onCurrentValueChanged)
public:
  explicit VisualizationContext(TelemetryChannel<PressureData>* channel, QObject *parent = nullptr)
  : minX_{QDateTime::currentDateTime()},
    maxX_{QDateTime::currentDateTime()},
    currentValue_{"0"} {

    output_file_.open("burst.csv", std::ios_base::out | std::ios_base::app);
    if (!output_file_) {
      std::cout << "Error opening file\n";
    }
    if (output_file_.eof()) { // TODO proper file existence check
      output_file_ << "timestamp,voltage,pressure\n";
    }

    channel->subscribe([&](const std::vector<PressureData> &buffer, const size_t size){
      data_end_ = std::min(size, 10000ul);
      for (size_t i {0}; i < size; i++) {
        output_file_ << (std::chrono::duration_cast<std::chrono::milliseconds>(buffer[i].timestamp.time_since_epoch())).count() << ','
                     << buffer[i].voltage() << ','
                     << buffer[i].pressure()
                     << std::endl;
      }
      std::move(buffer.begin(), buffer.begin()+data_end_, data_.begin());
    });
  }

  QDateTime minX() { return minX_; }
  QDateTime maxX() { return maxX_; }
  QString currentValue() { return currentValue_; }
  void setMinX(const QDateTime &minX) {
    minX_ = minX;
    emit onMinXChanged();
  }
  void setMaxX(const QDateTime &maxX) {
    maxX_ = maxX;
    emit onMaxXChanged();
  }
  void setCurrentValue(const QString &currentValue) {
    currentValue_ = currentValue;
    emit onCurrentValueChanged();
  }

signals:
  void onMinXChanged();
  void onMaxXChanged();
  void onCurrentValueChanged();

public slots:
  void update(QAbstractSeries* series) {
    using namespace std::chrono;
    using namespace std::chrono_literals;

    if (!series) return;
    auto xy_series = dynamic_cast<QXYSeries*>(series);

    auto point = data_[0];
    milliseconds ms = duration_cast<milliseconds>(point.timestamp.time_since_epoch());
    xy_series->append({
      static_cast<qreal>(ms.count()),
      point.pressure()
    });
    while(xy_series->count() > 100000) {
      xy_series->remove(0);
    }
    setMinX(QDateTime::fromMSecsSinceEpoch((ms - 30s).count()));
    setMaxX(QDateTime::fromMSecsSinceEpoch(ms.count()));
    setCurrentValue(QString::fromStdString(std::to_string(data_[data_end_-1].pressure())));
  }

private:
  std::fstream output_file_;
  std::array<PressureData, 10000> data_;
  size_t data_end_ {0};
  QDateTime minX_;
  QDateTime maxX_;
  QString currentValue_;
};

#endif // VISUALIZATIONCONTEXT_H
