#ifndef SCREENPROFILESETUP_H
#define SCREENPROFILESETUP_H

#include <QWidget>

namespace Ui {
class ScreenProfileSetup;
}

class ScreenProfileSetup : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenProfileSetup(QWidget *parent = nullptr);
    ~ScreenProfileSetup();

private:
    Ui::ScreenProfileSetup *ui;

signals:
    void sendToHome();
    void sendToAddProfile();

private slots:
    void goToHome();
    void goToAddProfile();
};

#endif // SCREENPROFILESETUP_H
