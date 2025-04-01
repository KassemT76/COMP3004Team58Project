#include "insulinpump.h"

InsulinPump::InsulinPump(int battery, double insulinLevel, double insulinOnBoard) :
    battery(battery),
    insulinLevel(insulinLevel),
    insulinOnBoard(insulinOnBoard)
{

}

InsulinPump::~InsulinPump(){
    delete bolusCalculator;
}

void InsulinPump::initailizeBolus(PersonalProfile* profile, int totalCarbs, double currentBG){
    this.bolusCalculator = new BolusCalculator(profile, totalCarbs, currentBG);
}

Error InsulinPump::giveBolus(){
    // TODO: This part should be next, need to discuss what the plan is now...
}

void InsulinPump::startBasalDelievery(){

}

void InsulinPump::stopBasalDelievery(){

}

int InsulinPump::getBattery(){
    return battery;
}
double InsulinPump::getInsulinLevel(){
    return insulinLevel;
}
void InsulinPump::setInsulinLevel(double newLevel){
    insulinLevel = newLevel;
}
double InsulinPump::getInsulinOB(){
    return insulinOnBoard;
}
void InsulinPump::setInsulinOB(double newOB){
    insulinOnBoard = newOB;
}

void InsulinPump::setBattery(int newBattery){
    battery = newBattery;
}

// Should be implemented by functions returning an error
// void InsulinPump::raiseError(){

// }