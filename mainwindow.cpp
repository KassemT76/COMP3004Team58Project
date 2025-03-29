#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
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

    //Set to home after screens are set up
    goToHome();

    //SLOTS

    connect(ui->homeButton, SIGNAL(released()), this, SLOT(goToHome()));

    //SIGNALS

    //Home Screen
    connect(screenHome, SIGNAL(sendToHome()), this, SLOT(goToHome()));
    connect(screenHome, SIGNAL(sendToProfile()), this, SLOT(goToProfile()));
    connect(screenHome, SIGNAL(sendToBolus()), this, SLOT(goToBolus()));

    //Profile Screen
    connect(screenProfileSetup, SIGNAL(sendToAddProfile()), this, SLOT(goToAddProfile()));
    connect(screenProfileSetup, SIGNAL(sendToHome()), this, SLOT(goToHome()));

    //Bolus Screen
    connect(screenBolus, SIGNAL(sendToHome()), this, SLOT(goToHome()));

    //Add Profile Screen
    connect(screenAddProfile, SIGNAL(sendToProfile()), this, SLOT(goToProfile()));
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

