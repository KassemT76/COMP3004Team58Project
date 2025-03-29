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

private slots:
    void goToHome();
};

#endif // SCREENBOLUS_H
