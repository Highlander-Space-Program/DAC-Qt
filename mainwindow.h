#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>

#include "subscriberqtadapter.h"

class QSettingsWrapper : public QSettings {
  Q_OBJECT
  QML_NAMED_ELEMENT(QSettings)
public:
  explicit QSettingsWrapper(QObject *parent = nullptr) : QSettings(parent) {}

public slots:
  inline void setValue(const QString &key, const QVariant &value) {
    QSettings::setValue(key, value);
    emit valueChanged(key, value);
  }
  inline QVariant value(const QString &key, const QVariant &defaultValue) const {
    return QSettings::value(key, defaultValue);
  }
  inline QVariant value(const QString &key) const {
    return QSettings::value(key);
  }

signals:
  void valueChanged(QAnyStringView key, const QVariant& value);

};

class MainWindow : public QObject
{
Q_OBJECT
Q_PROPERTY(QSettingsWrapper* settings READ settings NOTIFY settingsChanged)
Q_PROPERTY(const PressureSubscriberQtAdapter* psiSub READ psiSub CONSTANT)
public:
  MainWindow() =default;
  MainWindow(QSettingsWrapper *settings, PressureSubscriberQtAdapter *psiSub) : settings_(settings), psiSub_(psiSub)  { }

  const PressureSubscriberQtAdapter* psiSub() const { return psiSub_; }
  QSettingsWrapper* settings() { return settings_; }

signals:
  void settingsChanged(QSettingsWrapper *settings);

private:
  QSettingsWrapper *settings_ = nullptr;
  PressureSubscriberQtAdapter *psiSub_;
};

#endif // MAINWINDOW_H
