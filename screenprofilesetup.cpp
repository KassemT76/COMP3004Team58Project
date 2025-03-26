#include "screenprofilesetup.h"
#include "ui_screenprofilesetup.h"

ScreenProfileSetup::ScreenProfileSetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenProfileSetup)
{
    ui->setupUi(this);
}

ScreenProfileSetup::~ScreenProfileSetup()
{
    delete ui;
}
void ScreenProfileSetup::addProfile(PersonalProfile& inProfile){

}
void ScreenProfileSetup::removeProfile(QString profileName){

}
PersonalProfile& ScreenProfileSetup::getProfile(QString profileName){
    PersonalProfile profile;

    return profile;
}
