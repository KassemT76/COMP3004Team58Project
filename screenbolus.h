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

private:
    Ui::ScreenBolus *ui;

signals:
    void sendToHome();
    void sendConfirmBolus();
    void sendCalcUnits();
    void sendCalcExtended();

private slots:
    void goToHome();
    void confirmBolus();
    void calcUnits();
    void calcExtended();
};

#endif // SCREENBOLUS_H
