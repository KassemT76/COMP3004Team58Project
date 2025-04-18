#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QTextEdit>

#include "screenhome.h"
#include "screenbolus.h"
#include "screenprofilesetup.h"
#include "screenlock.h"
#include "screenaddprofile.h"
#include "screensettings.h"
#include "insulinpump.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    ScreenHome* screenHome = nullptr;
    ScreenBolus* screenBolus = nullptr;
    ScreenLock* screenLock = nullptr;
    ScreenProfileSetup* screenProfileSetup = nullptr;
    ScreenAddProfile* screenAddProfile = nullptr;
    ScreenSettings* screenSettings = nullptr;




private:

    Ui::MainWindow *ui;

    InsulinPump* insulinPump;

    QTimer* timer;
    int currentTimeStep;
    bool chartShaded;

    QTextEdit *logText;
    QVBoxLayout *logLayout;

private slots:
    //Routing
    void goToHome();
    void goToLock();
    void goToBolus();
    void goToProfile();
    void goToAddProfile();
    void goToSettings();


    // Main Window
    void addBattery();
    void removeBattery();
    void addCarbs();
    void removeCarbs();

    // These slots will be called by the QTimer and the simulation
    void simulationStep();
    void startSimulation();
    void stopSimulation();
    void pauseSimulation();


    // other, misc fuctions
    void resetBattery();

    // screen profile setup:
    void addProfile(QString, double, double, double, double, int, int);
    void removeProfile(QString);
    void editProfile(int, QString, QString);
    void selectProfile(QString);

    // screen bolus:
    void confirmBolus(int, int, double, double, double);
    void calcUnits(double, double);
    void calcExtended(int, int, double, double, double);

    //screen settings
    void startDelivery();
    void stopDelivery();
};

#endif // MAINWINDOW_H
