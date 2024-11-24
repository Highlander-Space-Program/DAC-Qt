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
  Q_PROPERTY(const QList<QPointF>* data READ data NOTIFY dataChanged)
  Q_PROPERTY(QDateTime start READ start NOTIFY startChanged)
  Q_PROPERTY(QDateTime end READ end NOTIFY endChanged)
public:
  explicit PressureSubscriberQtAdapter (QObject *parent = nullptr) : QObject(parent) { }
  explicit PressureSubscriberQtAdapter (Broadcaster<PressureData> &broadcaster, QObject *parent = nullptr) : QObject(parent) {
    broadcaster.subscribe([this](const PressureData *data) {
      static int i = 0, decimation = 10;
      if (data && !i) {
        while (!data_.empty() && data_.front().x() < (data->timestamp-duration_).time_since_epoch().count()) { data_.pop_front(); data_.shrink_to_fit(); }
        this->data_.push_back(QPointF(data->timestamp.time_since_epoch().count(), data->pressure()));

        start_ = QDateTime::fromMSecsSinceEpoch(data->timestamp.time_since_epoch().count());
        end_= QDateTime::fromMSecsSinceEpoch((data->timestamp-duration_).time_since_epoch().count());
        emit startChanged(start_);
        emit endChanged(end_);
      }
      i = (i+1) % decimation;
    });
  }

  const QList<QPointF>* data() const { return &data_; }

  QDateTime start() const { return start_; }
  QDateTime end() const { return end_; }

public slots:
  void update(QLineSeries *series) {
   if (series) {
      series->replace(data_);

      auto chart = series->chart();
      chart->removeSeries(series);
      chart->addSeries(series);
   }
  }

signals:
  void dataChanged(const QList<QPointF>&);
  void startChanged(const QDateTime);
  void endChanged(const QDateTime);

private:
  std::chrono::milliseconds duration_ {10000};
  QDateTime start_;
  QDateTime end_;
  QList<QPointF> data_;
};

#endif // SUBSCRIBERQTADAPTER_H
