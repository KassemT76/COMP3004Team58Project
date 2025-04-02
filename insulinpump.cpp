#include "insulinpump.h"

InsulinPump::InsulinPump(int battery, double insulinLevel, double insulinOnBoard) :
    battery(battery),
    insulinLevel(insulinLevel),
    insulinOnBoard(insulinOnBoard)
{
    this->bolusCalculator = new BolusCalculator();
    this-> batteryUsage = 0;
    this->batteryOffset = 5;
}


InsulinPump::~InsulinPump(){
    delete bolusCalculator;
}

void InsulinPump::initailizeBolus(PersonalProfile* profile, int totalCarbs, double currentBG){
    this->bolusCalculator->calculateBolus(totalCarbs, currentBG, profile);
}

Error InsulinPump::giveBolus(){
    
}

void InsulinPump::startBasalDelievery(){

}

void InsulinPump::stopBasalDelievery(){

}

int InsulinPump::useBattery(){
    if (battery > 0){
        batteryUsage++;
        if (batteryUsage >= batteryOffset){
            battery--;
            batteryUsage = 0;
        }
    }
    return battery;
}

void InsulinPump::rechargeBattery(){
    battery = 100;
    batteryUsage = 0;
}

bool InsulinPump::setBatteryOffset(int offset){
    if (offset > 0){
        batteryOffset = offset;
        return true;
    }
    return false;
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
