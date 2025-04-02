#include "screenprofilesetup.h"
#include "ui_screenprofilesetup.h"
#include <QDebug>
#include <QWidget>
#include <QTableWidget>

ScreenProfileSetup::ScreenProfileSetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenProfileSetup)
{
    this->setParent(parent);
    ui->setupUi(this);
    connect(ui->backButton, SIGNAL(released()), this, SLOT(goToHome()));
    connect(ui->addButton, SIGNAL(released()), this, SLOT(goToAddProfile()));
    this->setWindowFlags(Qt::Widget);
    qInfo() << this->parentWidget();
    profileLayout = new QVBoxLayout(parent);
    profileLayout->addWidget(this);
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
    PersonalProfile newProfile(inName, inBasalRate, inCarbRatio, inCorrectionFactor, inTargetBG, inStartTime, inEndTime);
    profiles.append(newProfile);
    //****CODE TO CHANGE ADD PROFILE TO UI HERE VV****
    qInfo() << inName << " " << inBasalRate << " " <<  inCarbRatio << " " <<  inCorrectionFactor << " " << inTargetBG << " " <<  inStartTime << " " <<  inEndTime;
    int rowCount = ui->profileTable->rowCount();
    qInfo() << rowCount;
    ui->profileTable->insertRow(rowCount);
    qInfo() << ui->profileTable->rowCount();
    QTableWidgetItem* nameWidget = new QTableWidgetItem(inName);
    QTableWidgetItem* timeWidget = new QTableWidgetItem(newProfile.getDisplayTime(inStartTime));
    QTableWidgetItem* basalWidget = new QTableWidgetItem(QString::number(inBasalRate));
    QTableWidgetItem* correctWidget = new QTableWidgetItem(QString::number(inCorrectionFactor));
    QTableWidgetItem* carbWidget = new QTableWidgetItem(QString::number(inCarbRatio));
    QTableWidgetItem* targetWidget = new QTableWidgetItem(QString::number(inTargetBG));
    qInfo() << newProfile.getDisplayTime(inStartTime) << " " << QString::number(inBasalRate) << " " <<  QString::number(inCorrectionFactor) << " " <<  QString::number(inCarbRatio) << " " << QString::number(inTargetBG);
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
    int columnCount = ui->profileTable->columnCount();
        for (int row = 0; row < rowCount+1; ++row) {
            // Iterate through columns
            for (int col = 0; col < columnCount; ++col) {
                // Get the item at row, col
                QTableWidgetItem *item = ui->profileTable->item(row, col);
                if (item) {
                    // Print the item text
                    qDebug() << "Row:" << row << "Col:" << col << "Value:" << item->text();
                } else {
                    // If no item exists, print "empty" or some placeholder
                    qDebug() << "Row:" << row << "Col:" << col << "Value: (empty)";
                }
            }
        }
        this->show();
        this->update();
        this->raise();
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

void ScreenProfileSetup::on_profileTable_cellChanged(int row, int column)
{

}

