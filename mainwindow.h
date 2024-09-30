#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>

#include "subscriberqtadapter.h"

class MainWindow : public QObject
{
Q_OBJECT
Q_PROPERTY(QString test READ test CONSTANT)
Q_PROPERTY(const PressureSubscriberQtAdapter* psiSub READ psiSub CONSTANT)
public:
  QString test() { return test_; }
  const PressureSubscriberQtAdapter* psiSub() const { return &psiSub_; }
private:
  QString test_ = "test";
  PressureSubscriberQtAdapter psiSub_;
};

#endif // MAINWINDOW_H
