#include "insulinpump.h"

InsulinPump::InsulinPump(int battery, double insulinLevel, double insulinOnBoard, ScreenProfileSetup* profileScreen) :
    battery(battery),
    insulinLevel(insulinLevel),
    insulinOnBoard(insulinOnBoard)
{
    this->bolusCalculator = new BolusCalculator();
    profileManager = new ProfileManager(profileScreen);
}


InsulinPump::~InsulinPump(){
    delete bolusCalculator;
    delete profileManager;
}

void InsulinPump::initailizeBolus(PersonalProfile* profile, int totalCarbs, double currentBG){
    this->bolusCalculator->calculateBolus(totalCarbs, currentBG, profile);
}

Error InsulinPump::giveBolus(){
    Error error;
    return error;
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
