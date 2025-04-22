#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
 * @brief This file contains the MainWindow class which is the main interface for the insulin pump simulation application.
 * 
 * @details The MainWindow class is responsible for managing the user interface and interactions
 * with the insulin pump simulation. It includes methods for routing between different screens,
 * starting and stopping the simulation, and updating the user interface with the current state
 * of the insulin pump.
 * 
 * @authors Ariz Kazani, Hollen Lo and Kassem Taha
 */

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QTextEdit>

#include "screenhome.h"
#include "screenbolus.h"
#include "screenprofilesetup.h"
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
    void resetInsulin();
    // screen profile setup:
    void addProfile(QString, double, double, double, double, int, int);
    void removeProfile(QString);
    void editProfile(int, QString, QString);
    void selectProfile(QString);

    // screen bolus:
    void confirmBolus(int, int, int, int, double, double);
    void calcUnits(double, double);
    void calcExtended(int, int, int, int, double, double);

    //screen settings
    void stopDelivery();

    //screen home
    void stopBolus();
};

#endif // MAINWINDOW_H
