#include "screenprofilesetup.h"
#include "ui_screenprofilesetup.h"
#include <QDebug>
#include <QWidget>
#include <QTableWidget>

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
    delete ui;
}

void ScreenProfileSetup::goToHome(){
    emit sendToHome();
}

void ScreenProfileSetup::goToAddProfile(){
    emit sendToAddProfile();
}

void ScreenProfileSetup::addProfile(QString inName, double inBasalRate, double inCarbRatio, double inCorrectionFactor, double inTargetBG, int inStartTime, int inEndTime){
    if(nameExists(inName) || names.length() >= 6){
        return;//name already exists or number of profiles exceed 6, so don't put in profile
    }
    names.append(inName);
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
    ui->profileTable->setVerticalHeaderItem(rowCount, nameWidget);
    ui->profileTable->setItem(rowCount, 0, timeWidget);
    ui->profileTable->setItem(rowCount, 1, basalWidget);
    ui->profileTable->setItem(rowCount, 2, correctWidget);
    ui->profileTable->setItem(rowCount, 3, carbWidget);
    ui->profileTable->setItem(rowCount, 4, targetWidget);
}
void ScreenProfileSetup::removeProfile(){
    QTableWidgetItem *selected = ui->profileTable->currentItem();
    if(selected == nullptr){//if nothing is selected, do nothing
        return;
    }
    QTableWidgetItem* rowHeader = ui->profileTable->verticalHeaderItem(selected->row());
    if(ui->selectedProfile->text() == rowHeader->text()){//if removed row is active profile
        ui->selectedProfile->setText("none");
    }
    names.removeOne(rowHeader->text());
    emit sendRemoveProfile(rowHeader->text());
    ui->profileTable->removeRow(selected->row());
}
void ScreenProfileSetup::editProfile(){
    QTableWidgetItem *selected = ui->profileTable->currentItem();
    QString input = ui->editText->toPlainText();
    ui->editText->setText("");
    double val = 0;
    int index = selected->column();
    if(index == 0){//setting time, have to adjust differently than other values
        //each input.mid is a section of the time clock format: XX:XX-XX:XX, inputs must be exact
        //qInfo() << input.mid(0, 2) << input.mid(3, 2)<< input.mid(6, 2) << input.mid(9, 2);
        bool ok1;
        int startHr = input.mid(0, 2).toInt(&ok1);
        bool ok2;
        int startMin = input.mid(3, 2).toInt(&ok2);
        bool ok3;
        int endHr = input.mid(6, 2).toInt(&ok3);
        bool ok4;
        int endMin = input.mid(9, 2).toInt(&ok4);
        if(!ok1 || !ok2 || !ok3 || !ok4 || startHr >=24 || startHr < 0 || endHr >=24 || endHr < 0 ||
                startMin >=60 || startMin < 0 || endMin >=60 || endMin < 0){//if edit input is inappropriate, don't edit
            return;
        }
        int start = startHr*60+startMin;
        int end = endHr*60+startMin;
        if(start >= end){//check if time range is appropriate
            return;
        }
    }
    else{
        bool ok;
        val = input.toDouble(&ok);
        if(!ok){//if edit input is inappropriate, do nothing
            return;
        }
        input = QString::number(val, 'f', 2);//set to 2 decimals
    }
    selected->setText(input);
    QTableWidgetItem* rowHeader = ui->profileTable->verticalHeaderItem(selected->row());
    emit sendEditProfile(index, input, rowHeader->text());
}
void ScreenProfileSetup::selectProfile(){
    QTableWidgetItem *selected = ui->profileTable->currentItem();
    if(selected == nullptr){//if nothing is selected, do nothing
        return;
    }
    QTableWidgetItem* rowHeader = ui->profileTable->verticalHeaderItem(selected->row());
    ui->selectedProfile->setText(rowHeader->text());
    emit sendSelectProfile(rowHeader->text());
}
bool ScreenProfileSetup::nameExists(QString inName){
    for(QString name: names){
        if(name == inName){
            return true;
        }
    }
    return false;
}

