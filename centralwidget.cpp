#include "centralwidget.h"

CentralWidget::CentralWidget(QWidget *parent)
  : QWidget{parent}
    , vbox{new QVBoxLayout{this}}
{

  for (size_t i = 0; i < 4; i++) {
      buttons.push_back(new QPushButton{"Button"});
      vbox->addWidget(buttons[i]);
      connect(buttons[i], &QPushButton::clicked,
              this, &CentralWidget::onClick);
  }

  setLayout(vbox);
}

void CentralWidget::onClick() {
  emit settingsButtonClicked();
}
