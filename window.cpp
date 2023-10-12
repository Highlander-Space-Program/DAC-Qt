#include "window.h"
#include <QPushButton>
#include <QWidget>
#include <QGridLayout>
#include <QObject>
#include <iostream>

Window::Window(QWidget *parent)
    : QMainWindow(parent)
{
    QPushButton *AlexButton = new QPushButton("AlexButton", &HomePage);
    HomePageLayout->addWidget(AlexButton);

    QPushButton *Back = new QPushButton();
    Back->setText("Back");

    BackPageLayout->addWidget(Back);
    QAbstractButton::connect(AlexButton, &QPushButton::released, this, &Window::handleAlexButton);
    QAbstractButton::connect(Back, &QPushButton::released, this, &Window::handleBack);


    HomePage.setLayout(HomePageLayout);
    BackPage.setLayout(BackPageLayout);

    stackedLayout->addWidget(&HomePage);
    stackedLayout->addWidget(&BackPage);

    MainLayout->addLayout(stackedLayout, 0, 0);
    setLayout(MainLayout);

    pageComboBox->addItem("Home Page");
    pageComboBox->addItem("Back Page");
    connect(pageComboBox, &QComboBox::activated,
            stackedLayout, &QStackedLayout::setCurrentIndex);
}

Window::~Window() {

}

void Window::showCurrentWindow() {
    stackedLayout->widget(stackedLayout->currentIndex())->show();
}

void Window::handleAlexButton() {
    stackedLayout->widget(stackedLayout->currentIndex())->hide();
    stackedLayout->setCurrentIndex(1);
    showCurrentWindow();
}
void Window::handleBack() {
    stackedLayout->widget(stackedLayout->currentIndex())->hide();
    stackedLayout->setCurrentIndex(0);
    showCurrentWindow();
}

void Window::showHomePage() {
    stackedLayout->widget(0)->show();
}
