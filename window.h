#ifndef WINDOW_H
#define WINDOW_H


#include <QMainWindow>
#include "qwidget.h"
#include <QGridLayout>
#include <QStackedLayout>
#include <QComboBox>

class Window : public QMainWindow
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();
    QWidget HomePage;
    QWidget BackPage;
    QWidget NI;
    void showCurrentWindow();
    void showHomePage();
    QGridLayout *MainLayout = new QGridLayout();
    QGridLayout *HomePageLayout = new QGridLayout();
    QGridLayout *BackPageLayout = new QGridLayout();
    QStackedLayout *stackedLayout = new QStackedLayout();
    QComboBox *pageComboBox = new QComboBox;

public slots:
    void handleAlexButton();
    void handleBack();

};

#endif // WINDOW_H
