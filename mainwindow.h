#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "centralwidget.h"
#include "settingswidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;

  QStackedWidget* stackWidget_;

  CentralWidget* centralWidget_;
  SettingsWidget* settingsWidget_;

private slots:
  void openSettings();
  void closeSettings();
};
#endif // MAINWINDOW_H
