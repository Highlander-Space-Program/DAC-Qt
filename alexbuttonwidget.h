#ifndef ALEXBUTTONWIDGET_H
#define ALEXBUTTONWIDGET_H


#include <QWidget>
#include <QPushButton>

class AlexButtonWidget
{
public:
    AlexButtonWidget();
    ~AlexButtonWidget();
    QPushButton *AlexButton;

private:

public slots:
    void setlayout(QWidget & w);

signals:
    void buttonClicked();

};

#endif // ALEXBUTTONWIDGET_H
