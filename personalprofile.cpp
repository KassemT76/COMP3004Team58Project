#include "personalprofile.h"

PersonalProfile::PersonalProfile(QString name, double basalRate, double insulinToCarbRatio, double correctionFactor, double targetBG, int startTime, int endTime):
    name(name),
    basalRate(basalRate),
    insulinToCarbRatio(insulinToCarbRatio),
    correctionFactor(correctionFactor),
    targetBG(targetBG),
    startTime(startTime),
    endTime(endTime)
{
}

QString PersonalProfile::getName(){
    return name;
}
void PersonalProfile::setName(QString newName){
    name = newName;
}
double PersonalProfile::getBasalRate(){
    return basalRate;
}
void PersonalProfile::setBasalRate(double newRate){
    basalRate = newRate;
}
double PersonalProfile::getCarbRatio(){
    return insulinToCarbRatio;
}
void PersonalProfile::setCarbRatio(double newRatio){
    insulinToCarbRatio = newRatio;
}
double PersonalProfile::getCorrectionFactor(){
    return correctionFactor;
}
void PersonalProfile::setCorrectionFactor(double newFactor){
    correctionFactor = newFactor;
}
double PersonalProfile::getTargetBG(){
    return targetBG;
}
void PersonalProfile::setTargetBG(double newTarget){
    targetBG = newTarget;
}
int PersonalProfile::getStartTime(){
    return startTime;
}
void PersonalProfile::setStartTime(int time){
    startTime = time;
}
int PersonalProfile::getEndTime(){
    return endTime;
}
void PersonalProfile::setEndTime(int time){
    endTime = time;
}
double PersonalProfile::getTimeHr(){
    double time = endTime - startTime;
    time = time/60;
    return endTime;
}
QString PersonalProfile::getDisplayTime(int time){
    int hr = time/60;
    QString display = (QString::number(hr).rightJustified(2, '0')+":"+(QString::number(time-hr*60)).rightJustified(2, '0'));
    return display;
}

