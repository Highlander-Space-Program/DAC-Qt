#ifndef WINDOW_H
#define WINDOW_H


#include "qwidget.h"
#include <QGridLayout>

class Window : public QObject
{
public:
    Window();
    ~Window();
    QWidget w;
    void showWindow();

public slots:
    void setLayout(QGridLayout *newLayout);

};

#endif // WINDOW_H
