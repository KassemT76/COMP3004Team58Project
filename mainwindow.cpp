#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    insulinPump = new InsulinPump(100, 0, 0, screenProfileSetup);

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
    connect(screenHome, SIGNAL(sendToHome()), this, SLOT(goToHome()));
    connect(screenHome, SIGNAL(sendToProfile()), this, SLOT(goToProfile()));
    connect(screenHome, SIGNAL(sendToBolus()), this, SLOT(goToBolus()));

    // Profile Screen
    connect(screenProfileSetup, SIGNAL(sendToAddProfile()), this, SLOT(goToAddProfile()));
    connect(screenProfileSetup, SIGNAL(sendToHome()), this, SLOT(goToHome()));

    // Bolus Screen
    connect(screenBolus, SIGNAL(sendToHome()), this, SLOT(goToHome()));

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
    goToProfile();
}
//Simulation

void MainWindow::simulationStep(){
    //Do 1 Tick
    currentTimeStep++;

    //Insulin Pump
    //TODO: DECAY, operations

    //Update UI
    screenHome->setTime(currentTimeStep);
    screenHome->setBattery(insulinPump->getBattery());
    screenHome->setIL(insulinPump->getInsulinLevel());
    screenHome->setIOB(insulinPump->getInsulinOB());
}

void MainWindow::startSimulation(){
    timer->start(100);
}

void MainWindow::stopSimulation(){
    timer->stop();
    currentTimeStep = 0;
}

void MainWindow::pauseSimulation(){
    timer->stop();
}
