#include "screenprofilesetup.h"
#include "ui_screenprofilesetup.h"
#include <QDebug>
#include <QWidget>
#include <QTableWidget>
#include "profilemanager.h"

ScreenProfileSetup::ScreenProfileSetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenProfileSetup)
{
    ui->setupUi(this);
    ui->profileTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    connect(ui->backButton, SIGNAL(released()), this, SLOT(goToHome()));
    connect(ui->addButton, SIGNAL(released()), this, SLOT(goToAddProfile()));
    connect(ui->selectButton, &QPushButton::released, this, &ScreenProfileSetup::selectProfile);
    connect(ui->editButton, &QPushButton::released, this, &ScreenProfileSetup::editProfile);
    connect(ui->removeButton, &QPushButton::released, this, &ScreenProfileSetup::removeProfile);
}

ScreenProfileSetup::~ScreenProfileSetup()
{
    for(PersonalProfile* profile : profiles){
        delete profile;
    }
    for(QTableWidgetItem* widget : cells){
        delete widget;
    }
    delete ui;
}

void ScreenProfileSetup::goToHome(){
    emit sendToHome();
}

void ScreenProfileSetup::goToAddProfile(){
    emit sendToAddProfile();
}

void ScreenProfileSetup::addProfile(QString inName, double inBasalRate, double inCarbRatio, double inCorrectionFactor, double inTargetBG, int inStartTime, int inEndTime){
    PersonalProfile *newProfile = new PersonalProfile(inName, inBasalRate, inCarbRatio, inCorrectionFactor, inTargetBG, inStartTime, inEndTime);
    profiles.append(newProfile);
    int rowCount = ui->profileTable->rowCount();
    ui->profileTable->insertRow(rowCount);
    QTableWidgetItem* nameWidget = new QTableWidgetItem(inName);
    QString time = newProfile->getDisplayTime(inStartTime) + "-" + newProfile->getDisplayTime(inEndTime);
    QTableWidgetItem* timeWidget = new QTableWidgetItem(time);
    QTableWidgetItem* basalWidget = new QTableWidgetItem(QString::number(inBasalRate));
    QTableWidgetItem* correctWidget = new QTableWidgetItem(QString::number(inCorrectionFactor));
    QTableWidgetItem* carbWidget = new QTableWidgetItem(QString::number(inCarbRatio));
    QTableWidgetItem* targetWidget = new QTableWidgetItem(QString::number(inTargetBG));
    cells.append(timeWidget);
    cells.append(basalWidget);
    cells.append(correctWidget);
    cells.append(carbWidget);
    cells.append(targetWidget);
    ui->profileTable->setVerticalHeaderItem(rowCount, nameWidget);
    ui->profileTable->setItem(rowCount, 0, timeWidget);
    ui->profileTable->setItem(rowCount, 1, basalWidget);
    ui->profileTable->setItem(rowCount, 2, correctWidget);
    ui->profileTable->setItem(rowCount, 3, carbWidget);
    ui->profileTable->setItem(rowCount, 4, targetWidget);
}
void ScreenProfileSetup::removeProfile(){

}
void ScreenProfileSetup::editProfile(){

}
void ScreenProfileSetup::selectProfile(){

    //SEND SIGNAL TO INSULIN PUMP, WHERE IT WOULD CALL PROFILE MANAGER

}
PersonalProfile* ScreenProfileSetup::getProfile(QString profileName){
    for(PersonalProfile* profile: profiles){
        if(profile->getName() == profileName){
            return profile;
        }
    }
    return activeProfile;
}


void ScreenProfileSetup::setProfileManager(ProfileManager* passedManager){
    profileManager = passedManager;
}
