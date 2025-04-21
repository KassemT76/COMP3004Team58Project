#ifndef SCREENSETTINGS_H
#define SCREENSETTINGS_H

#include <QWidget>

namespace Ui {
class ScreenSettings;
}

class ScreenSettings : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenSettings(QWidget *parent = nullptr);
    ~ScreenSettings();

signals:
    void sendStopDeliverySignal();
    void sendToProfile();
    void sendToHome();

private slots:
    void goToHome();
    void goToProfile();
    void stopDelivery();

private:
    Ui::ScreenSettings *ui;
};

#endif // SCREENSETTINGS_H
