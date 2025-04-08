#ifndef SCREENHOME_H
#define SCREENHOME_H

#include <QWidget>
#include <QDebug>
#include "chart.h"
namespace Ui {
class ScreenHome;
}

class ScreenHome : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenHome(QWidget *parent = nullptr);
    ~ScreenHome();

    void setTime(int);
    void setIOB(double);
    void setIL(double);
    void setGlucoseLevel(double);
    void setBattery(int);

    void addPoint(double);
    void startShadedArea();
private:
    Ui::ScreenHome *ui;

    Chart* chart;

signals:
    void sendToBolus();
    void sendToProfile();

private slots:
    void goToProfile();
    void goToBolus();
};

#endif // SCREENHOME_H
