#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QPushButton>
#include <QGridLayout>
#include <QWidget>

class SettingsWidget : public QWidget
{
  Q_OBJECT
public:
  explicit SettingsWidget(QWidget *parent = nullptr);

private:
  QGridLayout* grid;
  QPushButton* saveButton;

private slots:
  void save();

signals:
  void settingsClose();
};

#endif // SETTINGSWIDGET_H
