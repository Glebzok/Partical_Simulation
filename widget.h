#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "body3.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr, vector<Particle*> ps = {}, QString name = "name");
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void PlaybackStep();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
    vector<Particle*> ps;
    QTimer* playBackTimer;
    QString name;
    int TimeElapsed;
};

#endif // WIDGET_H
