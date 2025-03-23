#ifndef SCREENLOCK_H
#define SCREENLOCK_H

#include <QWidget>

namespace Ui {
class ScreenLock;
}

class ScreenLock : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenLock(QWidget *parent = nullptr);
    ~ScreenLock();

private:
    Ui::ScreenLock *ui;
};

#endif // SCREENLOCK_H
