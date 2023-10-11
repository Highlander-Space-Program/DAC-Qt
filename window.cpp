#include "window.h"
#include <QPushButton>
#include <QWidget>
#include <QGridLayout>
#include <QObject>

Window::Window() {
    QPushButton *AlexButton = new QPushButton();
    AlexButton->setText("AlexButton");
    QGridLayout *HomePage = new QGridLayout();
    HomePage->addWidget(AlexButton);

    QPushButton *Back = new QPushButton();
    Back->setText("Back");
    QGridLayout *BackPage = new QGridLayout();
    BackPage->addWidget(Back);
    QAbstractButton::connect(AlexButton, SIGNAL(clicked()), this, SLOT(&Window::setLayout));

    w.setLayout(HomePage);
}

Window::~Window() {

}


void Window::setLayout(QGridLayout *newLayout) {
    w.setLayout(newLayout);
}

void Window::showWindow() {
    w.show();
}
