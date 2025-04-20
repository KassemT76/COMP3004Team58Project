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
    if(ui->carbsSpinbox->value() <= 0){//if no carbs input(must at least have carbs, this input is invalid)
        return;
    }
    int durHr = (int)ui->durationHr->value();
    int durMin = (int)ui->durationMin->value();
    int delieverNow = (int)ui->deliverNow->value();
    if(ui->extendedCheckBox->isChecked()){//when extended
        sendConfirmBolus(delieverNow, 100-delieverNow, durHr,durMin, ui->carbsSpinbox->value(), ui->glucoseSpinbox->value());
    }
    else{//when immediate
        sendConfirmBolus(-1, -1, -1, -1, ui->carbsSpinbox->value(), ui->glucoseSpinbox->value());
    }
    ui->carbsSpinbox->setValue(0.0);
    ui->glucoseSpinbox->setValue(0.0);
    ui->deliverNow->setValue(0);
    ui->deliverLater->setText("0");
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
    ui->deliverLater->setText(QString::number(100-(int)ui->deliverNow->value()));

    emit sendCalcExtended((int)ui->deliverNow->value(), 100-(int)ui->deliverNow->value(), (int)ui->durationHr->value(), (int)ui->durationMin->value(), ui->carbsSpinbox->value(), ui->glucoseSpinbox->value());
}
void ScreenBolus::updateCalc(double bolus){
    ui->unitsView->setText(QString::number(bolus));
}
void ScreenBolus::updateExtended(double now, double later){
    ui->nowView->setText(QString::number(now));
    ui->laterView->setText(QString::number(later));
}
