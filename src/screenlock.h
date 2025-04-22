#ifndef SCREENLOCK_H
#define SCREENLOCK_H

/**
 * @brief This file contains the ScreenLock class which is used to create the lock screen of the insulin pump application.
 * @details The ScreenLock class is a QWidget that displays a lock screen for the insulin pump application.
 * 
 * @warning this class in incomplete
 * 
 * @author Kassem Taha
 */

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
