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

    QString setTime(int);
    void setIOB(double);
    void setIL(double);
    void setGlucoseLevel(double);
    void setBattery(int);
    void stopBolus();
    void addPoint(double);
    void startShadedArea();
    void setBolusTime(int);
    void setBolusActive(QString);
private:
    Ui::ScreenHome *ui;

    Chart* chart;

signals:
    void sendToBolus();
    void sendToSettings();
    void sendStopBolus();
private slots:
    void goToSettings();
    void goToBolus();
};

#endif // SCREENHOME_H
