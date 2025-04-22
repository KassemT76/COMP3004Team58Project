#ifndef SCREENSETTINGS_H
#define SCREENSETTINGS_H

/**
 * @brief This file contains the ScreenSettings class which is used to create the settings screen of the insulin pump application.
 * @details The ScreenSettings class is a QWidget that displays the settings screen for the insulin pump application.
 * It provides buttons to navigate to the home and profile setup screens, and to stop delivery.
 * 
 * @author Kassem Taha
 */

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
