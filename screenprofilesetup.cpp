#include "screenprofilesetup.h"
#include "ui_screenprofilesetup.h"
#include <QDebug>

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

void ScreenProfileSetup::addProfile(QString inName, double inBasalRate, double inCarbRatio, double inCorrectionFactor, double inTargetBG, int inStartTime, int inEndTime){
    PersonalProfile newProfile(inName, inBasalRate, inCarbRatio, inCorrectionFactor, inTargetBG, inStartTime, inEndTime);
    profiles.append(newProfile);
    //****CODE TO CHANGE ADD PROFILE TO UI HERE VV****
    qInfo() << inName << " " << inBasalRate << " " <<  inCarbRatio << " " <<  inCorrectionFactor << " " << inTargetBG << " " <<  inStartTime << " " <<  inEndTime;
}
void ScreenProfileSetup::removeProfile(QString profileName){

}
PersonalProfile& ScreenProfileSetup::getProfile(QString profileName){
    for(PersonalProfile profile: profiles){
        if(profile.getName() == profileName){
            return profile;
        }
    }
    return activeProfile;
}
