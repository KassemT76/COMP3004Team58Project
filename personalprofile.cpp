#include "personalprofile.h"

PersonalProfile::PersonalProfile(QString name, double basalRate, double insulinToCarbRatio, double correctionFactor, double targetBG, int time):
    name(name),
    basalRate(basalRate),
    insulinToCarbRatio(insulinToCarbRatio),
    correctionFactor(correctionFactor),
    targetBG(targetBG),
    distributionTime(time)
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
int PersonalProfile::getTime(){
    return distributionTime;
}
void PersonalProfile::setTime(int time){
    distributionTime = time;
}
