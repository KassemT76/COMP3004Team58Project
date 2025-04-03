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
    if(profileManager->getProfile(inName) != nullptr){
        return;//if there already exists a profile with the same name, don't add it
    }
    profileManager->addProfile(inName, inBasalRate, inCarbRatio, inCorrectionFactor, inTargetBG, inStartTime, inEndTime);
    int rowCount = ui->profileTable->rowCount();
    ui->profileTable->insertRow(rowCount);
    QTableWidgetItem* nameWidget = new QTableWidgetItem(inName);
    PersonalProfile profile;
    QString time = profile.getDisplayTime(inStartTime) + "-" + profile.getDisplayTime(inEndTime);
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
    QTableWidgetItem *selected = ui->profileTable->currentItem();
    qInfo() << selected->text() << selected->column();
    QString input = ui->editText->toPlainText();
    ui->editText->setText("");
    if(selected->column() == 0){

    }
    else{
        bool ok;
        double val = input.toDouble(&ok);
        if(!ok){//if value is inappropriate
            return;
        }

    }

}
void ScreenProfileSetup::selectProfile(){

    //SEND SIGNAL TO INSULIN PUMP, WHERE IT WOULD CALL PROFILE MANAGER

}


void ScreenProfileSetup::setProfileManager(ProfileManager* passedManager){
    profileManager = passedManager;
}
ProfileManager* ScreenProfileSetup::getManager(){
    return profileManager;
}
