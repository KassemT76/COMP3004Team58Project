#ifndef SCREENBOLUS_H
#define SCREENBOLUS_H

#include <QWidget>

namespace Ui {
class ScreenBolus;
}

class ScreenBolus : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenBolus(QWidget *parent = nullptr);
    ~ScreenBolus();
    void updateCalc(double);
    void updateExtended(double, double);

private:
    Ui::ScreenBolus *ui;

signals:
    void sendToHome();
    void sendConfirmBolus();
    void sendCalcUnits(double, double);
    void sendCalcExtended(int, int, int, double, double);

private slots:
    void goToHome();
    void confirmBolus();
    void calcUnits();
    void calcExtended();
};

#endif // SCREENBOLUS_H
