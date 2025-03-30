#include "screenaddprofile.h"
#include "ui_screenaddprofile.h"
#include <QDebug>

ScreenAddProfile::ScreenAddProfile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenAddProfile)
{
    ui->setupUi(this);

    connect(ui->backButton, SIGNAL(released()), this, SLOT(goToProfile()));
    connect(ui->confirmButton, SIGNAL(released()), this, SLOT(gatherInfo()));
}

ScreenAddProfile::~ScreenAddProfile()
{
    delete ui;
}

void ScreenAddProfile::goToProfile(){
    emit sendToProfile();
}

void ScreenAddProfile::gatherInfo(){
    QString inName = ui->nameEnter->toPlainText();
    QString inBasal = ui->basalEnter->toPlainText();
    QString inCorrection = ui->correctEnter->toPlainText();
    QString inCarb = ui->carbEnter->toPlainText();
    QString inTarget = ui->targetEnter->toPlainText();
    QString inStartHr = ui->startHour->toPlainText();
    QString inStartMin = ui->startMin->toPlainText();
    QString inEndHr = ui->endHour->toPlainText();
    QString inEndMin = ui->endMin->toPlainText();
    ui->nameEnter->setText("");
    ui->basalEnter->setText("");
    ui->correctEnter->setText("");
    ui->carbEnter->setText("");
    ui->targetEnter->setText("");
    ui->startHour->setText("");
    ui->startMin->setText("");
    ui->endHour->setText("");
    ui->endMin->setText("");
    bool okBasal;
    double basal = inBasal.toDouble(&okBasal);//basal will be 0 if text is not double, ok = true if it is double, false otherwise
    bool okCorrection;
    double correct = inCorrection.toDouble(&okCorrection);
    bool okCarb;
    double carb = inCarb.toDouble(&okCarb);
    bool okTarget;
    double target = inTarget.toDouble(&okTarget);
    bool okStartHr;
    int startHr = inStartHr.toInt(&okStartHr);
    bool okStartMin;
    int startMin = inStartMin.toInt(&okStartMin);
    bool okEndHr;
    int endHr = inEndHr.toInt(&okEndHr);
    bool okEndMin;
    int endMin = inEndMin.toInt(&okEndMin);
    int startTime, endTime = 0;
    if(okStartHr && okStartMin && okEndHr && okEndMin){//check correct input
        if(startHr < 24 && startHr >= 0 && endHr < 24 && endHr >= 0 && startMin < 60 && startMin >= 0 && endMin < 60 && endHr >= 0 ){
            //check if time is appropriate
            startTime = startHr*60 + startMin;//we convert start and end hours into min
            endTime = endHr*60 + endMin;
            if(startTime >= endTime){//if start is after or at end time
                return;
            }
        }
        else{//if time is inappropriate
            return;
        }
    }//if time is not int
    else{
        return;
    }
    if(okBasal && okCorrection && okCarb && okTarget){
    //if all info is correct
        profileSetup.addProfile(inName, basal, carb, correct, target, startTime, endTime);
        emit sendToProfile();
    }
}

