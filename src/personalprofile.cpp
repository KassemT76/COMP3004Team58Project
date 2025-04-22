#include "personalprofile.h"

/**
 * @brief The PersonalProfile class represents a personal profile for an insulin pump user.
 * 
 * @details The PersonalProfile class contains information about the user's insulin delivery settings,
 * including basal rate, insulin-to-carb ratio, correction factor, target blood glucose level, and time range.
 * It provides methods to get and set these values, as well as to display the time in a user-friendly format.
 * 
 * @author Hollen Lo
 */

PersonalProfile::PersonalProfile(QString name, double basalRate, double insulinToCarbRatio, double correctionFactor, double targetBG, int startTime, int endTime):
    name(name),
    basalRate(basalRate),
    insulinToCarbRatio(insulinToCarbRatio),
    correctionFactor(correctionFactor),
    targetBG(targetBG),
    startTime(startTime),
    endTime(endTime)
{
    insulinOB = 0;
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

double PersonalProfile::getInsulinOB(){
    return insulinOB;
}

void PersonalProfile::setInsulinOB(double insulinOB){
    this->insulinOB = insulinOB;
}

QString PersonalProfile::getDisplayTime(int time){
    int hr = time/60;
    QString display = (QString::number(hr).rightJustified(2, '0')+":"+(QString::number(time-hr*60)).rightJustified(2, '0'));

    return display;
}
