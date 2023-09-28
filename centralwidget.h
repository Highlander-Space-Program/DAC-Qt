#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <memory>

class CentralWidget : public QWidget
{
  Q_OBJECT
public:
  explicit CentralWidget(QWidget *parent = nullptr);
  ~CentralWidget() = default;

private:
  QVBoxLayout* vbox;
  std::vector<QPushButton*> buttons;

signals:
  void settingsButtonClicked();

public slots:
  void onClick();

};

#endif // CENTRALWIDGET_H
