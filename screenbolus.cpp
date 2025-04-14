#include "screenbolus.h"
#include "ui_screenbolus.h"
#include <QDebug>

ScreenBolus::ScreenBolus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenBolus)
{
    ui->setupUi(this);

    connect(ui->backButton, SIGNAL(released()), this, SLOT(goToHome()));
    connect(ui->confirmButton, &QPushButton::released, this, &ScreenBolus::confirmBolus);
    connect(ui->viewCalculationButton, &QPushButton::released, this, &ScreenBolus::calcUnits);
    connect(ui->viewUnitsButton, &QPushButton::released, this, &ScreenBolus::calcExtended);
}

ScreenBolus::~ScreenBolus()
{
    delete ui;
}

void ScreenBolus::goToHome(){
    emit sendToHome();
}
void ScreenBolus::confirmBolus(){
    if(ui->extendedCheckBox->isChecked()){
        double duration = ui->durationHr->value() + ui->durationMin->value()/60;
        sendConfirmBolus(ui->deliverNow->value(), ui->deliverLater->value(), duration,
                         ui->carbsSpinbox->value(), ui->glucoseSpinbox->value());
    }
    else{
        sendConfirmBolus(0, 0, 0, ui->carbsSpinbox->value(), ui->glucoseSpinbox->value());
    }
    ui->carbsSpinbox->setValue(0.0);
    ui->glucoseSpinbox->setValue(0.0);
    ui->deliverNow->setValue(0);
    ui->deliverLater->setValue(0);
    ui->durationHr->setValue(0);
    ui->durationMin->setValue(0);
    ui->unitsView->setText("");
    ui->nowView->setText("");
    ui->laterView->setText("");
}
void ScreenBolus::calcUnits(){
    emit sendCalcUnits(ui->carbsSpinbox->value(), ui->glucoseSpinbox->value());
}

void ScreenBolus::calcExtended(){
    double duration = ui->durationHr->value() + ui->durationMin->value()/60;
    emit sendCalcExtended(ui->deliverNow->value(), ui->deliverLater->value(), duration,
                          ui->carbsSpinbox->value(), ui->glucoseSpinbox->value());
}
void ScreenBolus::updateCalc(double bolus){
    ui->unitsView->setText(QString::number(bolus));
}
void ScreenBolus::updateExtended(double now, double later){
    ui->nowView->setText(QString::number(now));
    ui->laterView->setText(QString::number(later));
}
