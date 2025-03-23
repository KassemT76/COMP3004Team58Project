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
};

#endif // SCREENBOLUS_H
