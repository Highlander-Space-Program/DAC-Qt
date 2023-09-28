#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "centralwidget.h"

QT_BEGIN_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , stackWidget_{new QStackedWidget{this}}
  , centralWidget_{new CentralWidget{this}}
  , settingsWidget_{new SettingsWidget{this}}
{
  ui->setupUi(this);

  stackWidget_->addWidget(centralWidget_);
  stackWidget_->addWidget(settingsWidget_);

  setCentralWidget(stackWidget_);

  connect(centralWidget_, &CentralWidget::settingsButtonClicked,
          this, &MainWindow::openSettings);
  connect(settingsWidget_, &SettingsWidget::settingsClose,
          this, &MainWindow::closeSettings);
}

MainWindow::~MainWindow()
{
  delete stackWidget_;
  delete ui;
}

void MainWindow::openSettings() {
  stackWidget_->setCurrentIndex(stackWidget_->indexOf(settingsWidget_));
}
void MainWindow::closeSettings() {
  stackWidget_->setCurrentIndex(stackWidget_->indexOf(centralWidget_));
}

QT_END_NAMESPACE
