#include "screenprofilesetup.h"
#include "ui_screenprofilesetup.h"

ScreenProfileSetup::ScreenProfileSetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenProfileSetup)
{
    ui->setupUi(this);

    connect(ui->backButton, SIGNAL(released()), this, SLOT(goToHome()));
    connect(ui->addButton, SIGNAL(released()), this, SLOT(goToAddProfile()));
}

ScreenProfileSetup::~ScreenProfileSetup()
{
    delete ui;
}

void ScreenProfileSetup::goToHome(){
    emit sendToHome();
}

void ScreenProfileSetup::goToAddProfile(){
    emit sendToAddProfile();
}
