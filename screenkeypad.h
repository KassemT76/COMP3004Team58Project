#ifndef SCREENKEYPAD_H
#define SCREENKEYPAD_H

#include <QWidget>

namespace Ui {
class ScreenKeypad;
}

class ScreenKeypad : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenKeypad(QWidget *parent = nullptr);
    ~ScreenKeypad();

private:
    Ui::ScreenKeypad *ui;
};

#endif // SCREENKEYPAD_H
