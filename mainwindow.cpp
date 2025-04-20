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
    chartShaded = false;

    // UI
    ui->setupUi(this);

    logLayout = new QVBoxLayout();
    ui->logConsole->setLayout(logLayout);
    logText = new QTextEdit(this);
    logText->setReadOnly(true);
    logText->setWordWrapMode(QTextOption::NoWrap);
    logLayout->addWidget(logText);

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
    insulinPump = new InsulinPump(100, 235, 0);

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
    connect(screenHome, SIGNAL(sendStopBolus()), this, SLOT(stopBolus()));

    // Profile Screen
    connect(screenProfileSetup, SIGNAL(sendToAddProfile()), this, SLOT(goToAddProfile()));
    connect(screenProfileSetup, SIGNAL(sendToSettings()), this, SLOT(goToSettings()));
    connect(screenProfileSetup, SIGNAL(sendRemoveProfile(QString)), this, SLOT(removeProfile(QString)));
    connect(screenProfileSetup, SIGNAL(sendEditProfile(int, QString, QString)), this, SLOT(editProfile(int, QString, QString)));
    connect(screenProfileSetup, SIGNAL(sendSelectProfile(QString)), this, SLOT(selectProfile(QString)));

    // Bolus Screen
    connect(screenBolus, SIGNAL(sendToHome()), this, SLOT(goToHome()));
    connect(screenBolus, SIGNAL(sendConfirmBolus(int, int, int, int, double, double)), this, SLOT(confirmBolus(int, int, int, int, double, double)));
    connect(screenBolus, SIGNAL(sendCalcUnits(double, double)), this, SLOT(calcUnits(double, double)));
    connect(screenBolus, SIGNAL(sendCalcExtended(int, int, int, int, double, double)), this, SLOT(calcExtended(int, int, int, int, double, double)));

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
    //Do 1 Tick
    currentTimeStep+=5;

    //Insulin Pump
    //TODO: DECAY, operations
    QString logMessage = "";
    logMessage += insulinPump->distributeInsulin(currentTimeStep);//output
    if (insulinPump->getBasalDeActive() != chartShaded){
        chartShaded = insulinPump->getBasalDeActive();
        screenHome->startShadedArea();
    }

    // This is updating the battery level
    int battery = insulinPump->useBattery();
    screenHome->setBattery(battery);
    //make a use insulin function

    double newGlucoseLevel = insulinPump->getGlucoseLevel();

    //check for profile/bolus time, if it ended, get the next possible profile
    QString result = insulinPump->updateCGM(currentTimeStep);
    if(result != ""){
        screenProfileSetup->updateActiveProfile(insulinPump->getProfileManager()->getActiveProfile());
        logMessage += result;
    }
    if(insulinPump->getBolusActive()){//checks for Bolus status and updates lable accordingly
        screenHome->setBolusActive("ACTIVE");
    }
    else{
        screenHome->setBolusActive("INACTIVE");
    }
    //Update chart
    screenHome->addPoint(newGlucoseLevel);

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
    QString time = screenHome->setTime(currentTimeStep);
    // screenHome->setBattery(insulinPump->getBattery());
    screenHome->setIL(insulinPump->getInsulinLevel());
    screenHome->setIOB(insulinPump->getInsulinOB());

    //Log Console
    logText->append(time+" "+logMessage);

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
    if(insulinPump->getProfileManager()->getActiveProfile() == insulinPump->getProfileManager()->getProfile(inName)){
        //if selected profile is being used
        insulinPump->stopBasalDelievery();
    }
    insulinPump->getProfileManager()->removeProfile(inName);
}
void MainWindow::editProfile(int index, QString input, QString rowName){
    insulinPump->getProfileManager()->editProfile(index, input, rowName);
}
void MainWindow::selectProfile(QString inName){
    insulinPump->getProfileManager()->selectProfile(inName);
}

void MainWindow::confirmBolus(int now, int later, int durHr, int durMin, double totalCarbs, double currentBG){
    QString logMessage = insulinPump->giveBolus(now, later, durHr, durMin, currentTimeStep, totalCarbs, currentBG);
    if(logMessage == ""){//when bolus has no errors
        screenHome->setBolusActive("ACTIVE");
        return;
    }
    QString time = screenHome->setTime(currentTimeStep);
    logText->append(time+" "+logMessage);
}

void MainWindow::calcUnits(double totalCarbs, double currentBG){
    //FIND A WAY FOR INSULIN TO TRANSFER THE ACTIVE PROFILE(IF EXISTS) SO THAT IT CAN CALC UNIT
    insulinPump->initailizeBolus(totalCarbs, currentBG);
    screenBolus->updateCalc(insulinPump->getBolusCalculator()->getFinalBolus());
}
void MainWindow::calcExtended(int now, int later, int durHr, int durMin, double totalCarbs, double currentBG){
    //INSULIN PUMP DELIEVERS BOLUS IN A TIME RANGE
    insulinPump->initailizeExtended(now, later, durHr, durMin, currentTimeStep, totalCarbs, currentBG);
    screenBolus->updateExtended(insulinPump->getBolusCalculator()->getImmediateBolus(), insulinPump->getBolusCalculator()->getExtendedBolus());
}

void MainWindow::startDelivery(){
    QString logMessage = insulinPump->giveBasal(currentTimeStep);
    if(logMessage == ""){//if no profile
        return;
    }
    QString time = screenHome->setTime(currentTimeStep);
    logText->append(time+" "+logMessage);
}
void MainWindow::stopDelivery(){
    QString logMessage = insulinPump->stopBasal();
    if(logMessage == ""){//if no profile
        return;
    }
    QString time = screenHome->setTime(currentTimeStep);
    logText->append(time+" "+logMessage);
}
void MainWindow::stopBolus(){
    insulinPump->stopBolusDelievery();
    QString time = screenHome->setTime(currentTimeStep);
    logText->append(time+"  | bolus ended manually");
}
