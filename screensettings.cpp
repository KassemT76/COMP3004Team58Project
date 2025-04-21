#include "screensettings.h"
#include "ui_screensettings.h"

ScreenSettings::ScreenSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenSettings)
{
    ui->setupUi(this);

    connect(ui->profileButton, SIGNAL(released()), this, SLOT(goToProfile()));
    connect(ui->backButton, SIGNAL(released()), this, SLOT(goToHome()));
    connect(ui->stopDeliveryButton, SIGNAL(released()), this, SLOT(stopDelivery()));
}

ScreenSettings::~ScreenSettings()
{
    delete ui;
}

void ScreenSettings::goToHome(){
    emit sendToHome();
}

void ScreenSettings::goToProfile(){
    emit sendToProfile();
}

void ScreenSettings::stopDelivery(){
    emit sendStopDeliverySignal();
}
