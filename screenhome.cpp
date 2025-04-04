#include "screenhome.h"
#include "ui_screenhome.h"

ScreenHome::ScreenHome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenHome)
{
    ui->setupUi(this);

    connect(ui->settingsButton, SIGNAL(released()), this, SLOT(goToProfile()));
    connect(ui->bolusButton, SIGNAL(released()), this, SLOT(goToBolus()));

    chart = new Chart(ui->chartHolder);
}

ScreenHome::~ScreenHome()
{
    delete ui;
}

void ScreenHome::goToProfile(){
    emit sendToProfile();
}
void ScreenHome::goToBolus(){
    emit sendToBolus();
}

void ScreenHome::setTime(int t) {
    int hours = t / 60;
    int minutes = t % 60;

    QString formattedTime = QString("%1:%2")
        .arg(hours, 2, 10, QChar('0'))   // 2-digit hours, pad with 0
        .arg(minutes, 2, 10, QChar('0'));// 2-digit minutes, pad with 0

    ui->time->setText(formattedTime);
}

void ScreenHome::setIOB(double iob){
    ui->iobValue->setText(QString::number(iob) + " u");
}

void ScreenHome::setIL(double il){
    ui->insulinLevelValue->setText(QString::number(il) + " u");
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

