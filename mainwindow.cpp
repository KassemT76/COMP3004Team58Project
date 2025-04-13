#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    //Timer
    timer = new QTimer(this);
    currentTimeStep = 0;

    //UI
    ui->setupUi(this);

    //Set up screens
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

    //Insulin Pump
    insulinPump = new InsulinPump(100, 0, 0);

    //Set to home after screens are set up
    goToHome();

    //SLOTS

    // UI
    connect(ui->homeButton, SIGNAL(released()), this, SLOT(goToHome()));
    connect(ui->startButton, SIGNAL(released()), this, SLOT(startSimulation()));
    connect(ui->stopButton, SIGNAL(released()), this, SLOT(stopSimulation()));
    connect(ui->pauseButton, SIGNAL(released()), this, SLOT(pauseSimulation()));

    // Simulation
    connect(timer, SIGNAL(timeout()), this, SLOT(simulationStep()));

    //SIGNALS

    // Home Screen
    connect(screenHome, SIGNAL(sendToProfile()), this, SLOT(goToProfile()));
    connect(screenHome, SIGNAL(sendToBolus()), this, SLOT(goToBolus()));

    // Profile Screen
    connect(screenProfileSetup, SIGNAL(sendToAddProfile()), this, SLOT(goToAddProfile()));
    connect(screenProfileSetup, SIGNAL(sendToHome()), this, SLOT(goToHome()));
    connect(screenProfileSetup, SIGNAL(sendRemoveProfile(QString)), this, SLOT(removeProfile(QString)));
    connect(screenProfileSetup, SIGNAL(sendEditProfile(int, QString, QString)), this, SLOT(editProfile(int, QString, QString)));
    connect(screenProfileSetup, SIGNAL(sendSelectProfile(QString)), this, SLOT(selectProfile(QString)));

    // Bolus Screen
    connect(screenBolus, SIGNAL(sendToHome()), this, SLOT(goToHome()));
    connect(screenBolus, SIGNAL(sendConfirmBolus()), this, SLOT(confirmBolus()));
    connect(screenBolus, SIGNAL(sendCalcUnits(double, double)), this, SLOT(calcUnits(double, double)));
    connect(screenBolus, SIGNAL(sendCalcExtended(int, int, double, double, double)), this, SLOT(calcExtended(int, int, double, double, double)));

    // Add Profile Screen
    connect(screenAddProfile, SIGNAL(sendToProfile()), this, SLOT(goToProfile()));
    connect(screenAddProfile, SIGNAL(sendProfile(QString, double, double, double, double,int,int)), this, SLOT(addProfile(QString, double, double, double, double,int,int)));
}

MainWindow::~MainWindow()
{
    delete screenHome;
    delete screenBolus;
    delete screenProfileSetup;
    delete screenLock;
    delete screenAddProfile;

    delete insulinPump;
    delete timer;

    delete ui;
}

//Routing

void MainWindow::goToHome(){
    screenBolus->hide();
    screenLock->hide();
    screenProfileSetup->hide();
    screenAddProfile->hide();

    screenHome->show();
}

void MainWindow::goToLock(){
    screenBolus->hide();
    screenHome->hide();
    screenProfileSetup->hide();
    screenAddProfile->hide();

    screenLock->show();
}

void MainWindow::goToBolus(){
    screenHome->hide();
    screenLock->hide();
    screenProfileSetup->hide();
    screenAddProfile->hide();
    screenBolus->show();
}

void MainWindow::goToProfile(){
    screenBolus->hide();
    screenLock->hide();
    screenHome->hide();
    screenAddProfile->hide();

    screenProfileSetup->show();
}

void MainWindow::goToAddProfile(){
    screenBolus->hide();
    screenLock->hide();
    screenHome->hide();
    screenProfileSetup->hide();

    screenAddProfile->show();
}


void MainWindow::addProfile(QString name, double basal, double carb, double correct, double target,int start,int end){
    screenProfileSetup->addProfile(name, basal, carb, correct, target, start, end);
    insulinPump->getProfileManager()->addProfile(name, basal, carb, correct, target, start, end);
    goToProfile();
}
//Simulation

void MainWindow::simulationStep(){
    //Do 1 Tick
    currentTimeStep++;

    //Insulin Pump
    double n = 6.95 + 3.05 * qSin(currentTimeStep * 0.3);
    screenHome->setGlucoseLevel(n);
    screenHome->addPoint(n);
    if(currentTimeStep % 5 == 0){
        screenHome->startShadedArea();
    }
    //Update UI
    screenHome->setTime(currentTimeStep);
    screenHome->setBattery(insulinPump->getBattery());
    screenHome->setIL(insulinPump->getInsulinLevel());
    screenHome->setIOB(insulinPump->getInsulinOB());
}

void MainWindow::startSimulation(){
    timer->start(500);
}

void MainWindow::stopSimulation(){
    timer->stop();
    currentTimeStep = 0;
}

void MainWindow::pauseSimulation(){
    timer->stop();
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

void MainWindow::confirmBolus(){
    //INSULIN PUMP DELIEVERS BOLUS
}
void MainWindow::calcUnits(double totalCarbs, double currentBG){
    //FIND A WAY FOR INSULIN TO TRANSFER THE ACTIVE PROFILE(IF EXISTS) SO THAT IT CAN CALC UNIT
    insulinPump->initailizeBolus(totalCarbs, currentBG);
    screenBolus->updateCalc(insulinPump->getBolusCalculator()->getBolus());
}
void MainWindow::calcExtended(int now, int later, double duration, double totalCarbs, double currentBG){
    //INSULIN PUMP DELIEVERS BOLUS IN A TIME RANGE
    insulinPump->initailizeExtended(now, later, duration, totalCarbs, currentBG);
    screenBolus->updateExtended(insulinPump->getBolusCalculator()->getImmediateBolus(), insulinPump->getBolusCalculator()->getExtendedBolus());
}
