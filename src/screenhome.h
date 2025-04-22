#ifndef SCREENHOME_H
#define SCREENHOME_H

/**
 * @file screenhome.h
 * @brief This file contains the ScreenHome class which is used to create the home screen of the insulin pump application.
 * @details The ScreenHome class is a QWidget that displays the current glucose level, insulin on board (IOB), insulin level (IL), and battery status.
 * It also provides buttons to navigate to the settings and bolus screens. The class uses a Chart object to display glucose levels over time.
 * 
 * @author Kassem Taha
 */

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
