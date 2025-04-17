#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    // Timer
    timer = new QTimer(this);
    currentTimeStep = 0;

    // UI
    ui->setupUi(this);
    ui->batterySlider->setEnabled(false);
    ui->insulinLevelSlider->setEnabled(false);
    ui->iobSlider->setEnabled(false);
    ui->glucoseSlider->setEnabled(false);


    // Set up screens
    if (!screenHome)
        screenHome = new ScreenHome(this->ui->frame);
    if (!screenBolus)
        screenBolus = new ScreenBolus(this->ui->frame);
    if (!screenLock)
        screenLock = new ScreenLock(this->ui->frame);
    if (!screenProfileSetup)
        screenProfileSetup = new ScreenProfileSetup(this->ui->frame);
    if (!screenAddProfile)
        screenAddProfile = new ScreenAddProfile(this->ui->frame);
    if (!screenSettings)
        screenSettings = new ScreenSettings(this->ui->frame);

    // Insulin Pump
    insulinPump = new InsulinPump(100, 0, 0);

    // Set to home after screens are set up
    goToHome();

    /// SLOTS ///

    // UI
    connect(ui->homeButton, SIGNAL(released()), this, SLOT(goToHome()));
    connect(ui->startButton, SIGNAL(released()), this, SLOT(startSimulation()));
    connect(ui->stopButton, SIGNAL(released()), this, SLOT(stopSimulation()));
    connect(ui->pauseButton, SIGNAL(released()), this, SLOT(pauseSimulation()));

    connect(ui->rechargeButton, SIGNAL(released()), this, SLOT(resetBattery()));
    connect(ui->addCarbsButton, SIGNAL(released()), this, SLOT(addCarbs()));
    connect(ui->removeCarbsButton, SIGNAL(released()), this, SLOT(removeCarbs()));

    // Simulation
    connect(timer, SIGNAL(timeout()), this, SLOT(simulationStep()));

    /// SIGNALS ///

    // Home Screen
    connect(screenHome, SIGNAL(sendToSettings()), this, SLOT(goToSettings()));
    connect(screenHome, SIGNAL(sendToBolus()), this, SLOT(goToBolus()));

    // Profile Screen
    connect(screenProfileSetup, SIGNAL(sendToAddProfile()), this, SLOT(goToAddProfile()));
    connect(screenProfileSetup, SIGNAL(sendToSettings()), this, SLOT(goToSettings()));
    connect(screenProfileSetup, SIGNAL(sendRemoveProfile(QString)), this, SLOT(removeProfile(QString)));
    connect(screenProfileSetup, SIGNAL(sendEditProfile(int, QString, QString)), this, SLOT(editProfile(int, QString, QString)));
    connect(screenProfileSetup, SIGNAL(sendSelectProfile(QString)), this, SLOT(selectProfile(QString)));

    // Bolus Screen
    connect(screenBolus, SIGNAL(sendToHome()), this, SLOT(goToHome()));
    connect(screenBolus, SIGNAL(sendConfirmBolus()), this, SLOT(confirmBolus()));
    connect(screenBolus, SIGNAL(sendCalcUnits()), this, SLOT(calcUnits()));
    connect(screenBolus, SIGNAL(sendCalcExtended()), this, SLOT(calcExtended()));

    // Add Profile Screen
    connect(screenAddProfile, SIGNAL(sendToProfile()), this, SLOT(goToProfile()));
    connect(screenAddProfile, SIGNAL(sendProfile(QString, double, double, double, double,int,int)), this, SLOT(addProfile(QString, double, double, double, double,int,int)));

    // Settings Screen
    connect(screenSettings, SIGNAL(sendToProfile()), this, SLOT(goToProfile()));
    connect(screenSettings, SIGNAL(sendToHome()), this, SLOT(goToHome()));
    connect(screenSettings, SIGNAL(sendStartDeliverySignal()), this, SLOT(startDelivery()));
    connect(screenSettings, SIGNAL(sendStopDeliverySignal()), this, SLOT(stopDelivery()));

}

MainWindow::~MainWindow()
{
    delete screenHome;
    delete screenBolus;
    delete screenProfileSetup;
    delete screenLock;
    delete screenAddProfile;
    delete screenSettings;

    delete insulinPump;
    delete timer;

    delete ui;
}

/// Routing ///

void MainWindow::goToHome(){
    screenBolus->hide();
    screenLock->hide();
    screenProfileSetup->hide();
    screenAddProfile->hide();
    screenSettings->hide();

    screenHome->show();
}

void MainWindow::goToLock(){
    screenBolus->hide();
    screenHome->hide();
    screenProfileSetup->hide();
    screenAddProfile->hide();
    screenSettings->hide();

    screenLock->show();
}

void MainWindow::goToBolus(){
    screenHome->hide();
    screenLock->hide();
    screenProfileSetup->hide();
    screenAddProfile->hide();
    screenSettings->hide();

    screenBolus->show();
}

void MainWindow::goToProfile(){
    screenBolus->hide();
    screenLock->hide();
    screenHome->hide();
    screenAddProfile->hide();
    screenSettings->hide();

    screenProfileSetup->show();
}

void MainWindow::goToAddProfile(){
    screenBolus->hide();
    screenLock->hide();
    screenHome->hide();
    screenProfileSetup->hide();
    screenSettings->hide();

    screenAddProfile->show();
}

void MainWindow::goToSettings(){
    screenBolus->hide();
    screenLock->hide();
    screenHome->hide();
    screenProfileSetup->hide();
    screenAddProfile->hide();

    screenSettings->show();
}


/// Main Window ///

void MainWindow::addBattery(){
    insulinPump->setBattery(insulinPump->getBattery() + 5);
}
void MainWindow::removeBattery(){
    insulinPump->setBattery(insulinPump->getBattery() - 5);
}
void MainWindow::addCarbs(){
    insulinPump->setGlucoseLevel(insulinPump->getGlucoseLevel() - 0.5);
}
void MainWindow::removeCarbs(){
    insulinPump->setGlucoseLevel(insulinPump->getGlucoseLevel() - 0.5);
}

/// Simulation ///

void MainWindow::simulationStep(){
    //Do 5 Tick
    currentTimeStep += 5;

    //Insulin Pump
    //TODO: DECAY, operations
    int battery = insulinPump->useBattery();
    screenHome->setBattery(battery);

    insulinPump->setGlucoseLevel((6.95 + 3.05 * qSin((currentTimeStep / 5) * 0.3))); //this should be removed later
    double newGlucoseLevel = insulinPump->getGlucoseLevel();

    //Update chart
    screenHome->addPoint(newGlucoseLevel);

    if(currentTimeStep % 25 == 0){ //replace with check if we are not adminstring a bolus once function is done
        screenHome->startShadedArea();
    }


    //Update UI

    //This Screen
    ui->batterySlider->setValue(insulinPump->getBattery());
    ui->batteryValue->setText(QString::number(ui->batterySlider->value()));

    ui->insulinLevelSlider->setValue(insulinPump->getInsulinLevel());
    ui->insulinLevelValue->setText(QString::number(ui->insulinLevelSlider->value()));

    ui->iobSlider->setValue(insulinPump->getInsulinOB());
    ui->iobValue->setText(QString::number(ui->iobSlider->value()));

    ui->glucoseSlider->setValue(newGlucoseLevel);
    ui->glucoseValue->setText(QString::number(newGlucoseLevel, 2, 2));

    //Home Screen
    screenHome->setGlucoseLevel(newGlucoseLevel);
    screenHome->setTime(currentTimeStep);
    // screenHome->setBattery(insulinPump->getBattery());
    screenHome->setIL(insulinPump->getInsulinLevel());
    screenHome->setIOB(insulinPump->getInsulinOB());
}

void MainWindow::startSimulation(){
    timer->start(500);
}

void MainWindow::stopSimulation(){
    timer->stop();
    currentTimeStep = 0;
    screenHome->setTime(currentTimeStep);
    insulinPump->rechargeBattery();
    screenHome->setBattery(insulinPump->getBattery());
}

void MainWindow::pauseSimulation(){
    timer->stop();
}


void MainWindow::resetBattery(){
    insulinPump->rechargeBattery();
}
/// Profile Functions ///
void MainWindow::addProfile(QString name, double basal, double carb, double correct, double target,int start,int end){
    screenProfileSetup->addProfile(name, basal, carb, correct, target, start, end);
    insulinPump->getProfileManager()->addProfile(name, basal, carb, correct, target, start, end);
    goToProfile();
}
void MainWindow::removeProfile(QString inName){
    insulinPump->getProfileManager()->removeProfile(inName);
}
void MainWindow::editProfile(int index, QString input, QString rowName){
    insulinPump->getProfileManager()->editProfile(index, input, rowName);
}
void MainWindow::selectProfile(QString inName){
    insulinPump->getProfileManager()->selectProfile(inName);
}

/// Bolus Calculations ///
void MainWindow::confirmBolus(){
    //INSULIN PUMP DELIEVERS BOLUS
}
void MainWindow::calcUnits(){
    //FIND A WAY FOR INSULIN TO TRANSFER THE ACTIVE PROFILE(IF EXISTS) SO THAT IT CAN CALC UNIT
}
void MainWindow::calcExtended(){
    //INSULIN PUMP DELIEVERS BOLUS IN A TIME RANGE
}

void MainWindow::startDelivery(){
    qInfo() << "Starting basal delivery...";
}
void MainWindow::stopDelivery(){
    qInfo() << "Stopping basal delivery...";
}
