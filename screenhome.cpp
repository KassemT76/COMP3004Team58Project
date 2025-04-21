#include "screenhome.h"
#include "ui_screenhome.h"
#include <cmath>

ScreenHome::ScreenHome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenHome)
{
    ui->setupUi(this);

    connect(ui->settingsButton, SIGNAL(released()), this, SLOT(goToSettings()));
    connect(ui->bolusButton, SIGNAL(released()), this, SLOT(goToBolus()));
    connect(ui->stopBolusButton, &QPushButton::released, this, &ScreenHome::stopBolus);
    chart = new Chart(ui->chartHolder);
}

ScreenHome::~ScreenHome()
{
    delete ui;
}

void ScreenHome::goToSettings(){
    emit sendToSettings();
}
void ScreenHome::goToBolus(){
    emit sendToBolus();
}

QString ScreenHome::setTime(int t) {
    int hours = t / 60;
    int minutes = t % 60;

    QString formattedTime = QString("%1:%2")
        .arg(hours, 2, 10, QChar('0'))   // 2-digit hours, pad with 0
        .arg(minutes, 2, 10, QChar('0'));// 2-digit minutes, pad with 0

    ui->time->setText(formattedTime);
    return formattedTime;
}

void ScreenHome::setIOB(double iob){
    iob = round(100*iob)/100;//round to two decimals
    ui->iobValue->setText(QString::number(iob) + " u");
}

void ScreenHome::setIL(double il){
    il = round(100*il)/100;//round to two decimals
    if(il < 0){
        il = 0;
    }
    ui->insulinLevelValue->setText(QString::number(il) + " u");
}

void ScreenHome::setGlucoseLevel(double g){
    g = round(100*g)/100;//round to two decimals
    ui->glucoseValue->setText(QString::number(g));
}

void ScreenHome::setBattery(int b){
    ui->batteryValue->setText(QString::number(b) + "%");
}

void ScreenHome::addPoint(double glucose){
    chart->addPoint(glucose);
}

void ScreenHome::startShadedArea(){
    chart->shadeArea();
}

void ScreenHome::stopBolus(){
    ui->bolusActive->setText("INACTIVE");
    emit sendStopBolus();
}

void ScreenHome::setBolusActive(QString text){
    ui->bolusActive->setText(text);
}
void ScreenHome::setBolusTime(int time){
    int hours = time / 60;
    int minutes = time % 60;

    QString formattedTime = QString("%1:%2")
        .arg(hours, 2, 10, QChar('0'))   // 2-digit hours, pad with 0
        .arg(minutes, 2, 10, QChar('0'));// 2-digit minutes, pad with 0

    ui->timeOfBolus->setText(formattedTime);
}
