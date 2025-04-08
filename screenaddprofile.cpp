#include "screenaddprofile.h"
#include "ui_screenaddprofile.h"
#include <QDebug>

ScreenAddProfile::ScreenAddProfile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenAddProfile)
{
    ui->setupUi(this);

    connect(ui->backButton, SIGNAL(released()), this, SLOT(goToProfile()));
    connect(ui->confirmButton, SIGNAL(released()), this, SLOT(gatherInfo()));
}

ScreenAddProfile::~ScreenAddProfile()
{
    delete ui;
}

void ScreenAddProfile::goToProfile(){
    emit sendToProfile();
}

void ScreenAddProfile::gatherInfo(){
    //Grab values from the ui form

    QString inName = ui->nameEnter->toPlainText();

    double basal = ui->basalEnter->value();
    double correct = ui->correctEnter->value();
    double carb = ui->carbEnter->value();
    double target = ui->targetEnter->value();

    int startHr = ui->startHour->value();
    int startMin = ui->startMin->value();
    int endHr = ui->endHour->value();
    int endMin = ui->endMin->value();

    // Reset UI fields
    ui->nameEnter->setText("");

    ui->basalEnter->setValue(0.0);
    ui->correctEnter->setValue(0.0);
    ui->carbEnter->setValue(0.0);
    ui->targetEnter->setValue(0.0);

    ui->startHour->setValue(0);
    ui->startMin->setValue(0);
    ui->endHour->setValue(0);
    ui->endMin->setValue(0);

    //Calculate Time
    int startTime, endTime = 0;

    //we convert start and end hours into min
    startTime = startHr*60 + startMin;
    endTime = endHr*60 + endMin;

    //if start is after or at end time
    if(startTime >= endTime){
        return;
    }
    //if all info is correct, add the profile!
    emit sendProfile(inName, basal, carb, correct, target, startTime, endTime);
}

