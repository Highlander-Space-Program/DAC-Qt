#ifndef SUBSCRIBERQTADAPTER_H
#define SUBSCRIBERQTADAPTER_H

#include <iostream>

#include <QChart>
#include <QLineSeries>
#include <QObject>
#include <QtQmlIntegration>

#include <functional>

#include "broadcast/Broadcaster.h"
#include "models/PressureData.h"

class PressureSubscriberQtAdapter : public QObject
{
  Q_OBJECT
  QML_NAMED_ELEMENT(Subscriber)
  Q_PROPERTY(const QQueue<QPointF>* data READ data NOTIFY dataChanged)
public:
  explicit PressureSubscriberQtAdapter (QObject *parent = nullptr) {
    float x = 0.0f;
    for (size_t i=0; i<10000; i++) {
      data_.push_back(QPointF(QDateTime::currentDateTime().toMSecsSinceEpoch()+i*1000, sin(x)));
      x += 0.1;
    }

  }
//  explicit PressureSubscriberQtAdapter (Broadcaster<PressureData> &broadcaster, QObject *parent = nullptr) {
//    auto& queue = this->data_;
//    broadcaster.subscribe([&queue, this](const PressureData *data) {
//      while (queue.length() >= this->max_size_) { data_.pop_back(); }
//      queue.push_back(QPointF(data->timestamp.time_since_epoch().count(), data->data()));
//    });
//  }

  const QQueue<QPointF>* data() const { return &data_; }

public slots:
  void update(QLineSeries *series) {
    if (series) {
      qint64 t = QDateTime::currentDateTime().toMSecsSinceEpoch();
      double y = sin(2 * 3.14159 / 2000 * t);

      min_ = std::min(min_, y);
      max_ = std::max(max_, y);
      if (!series->attachedAxes().empty()) {
        series->attachedAxes()[0]->setMin(start_);
        series->attachedAxes()[0]->setMax(t);
        series->attachedAxes()[1]->setMin(min_);
        series->attachedAxes()[1]->setMax(max_);
      }

      series->append(t, y);

//    while (!data_.empty()) {
//      std::cout << data_.front().x() << ' ' << data_.front().y() << std::endl;
//      series->append(data_.front());
//      data_.pop_front();
//    }

      auto chart = series->chart();
      chart->removeSeries(series);
      chart->addSeries(series);
    }
  }

signals:
  void dataChanged();

private:
  QDateTime start_ = QDateTime::currentDateTime();
  qint64 duration_ms = 60000;
  qreal min_ = 0;
  qreal max_ = 0;
  QQueue<QPointF> data_;
};

#endif // SUBSCRIBERQTADAPTER_H
