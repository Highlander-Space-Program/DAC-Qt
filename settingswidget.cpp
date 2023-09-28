#include "settingswidget.h"

SettingsWidget::SettingsWidget(QWidget *parent)
  : QWidget{parent}
  , grid{new QGridLayout(this)}
  , saveButton{new QPushButton("Save", this)}
{
  layout()->addWidget(saveButton);
  setLayout(grid);

  connect(saveButton, &QPushButton::clicked,
          this, &SettingsWidget::save);
}

void SettingsWidget::save() {
  emit settingsClose();
}
