#include "insulinpump.h"

InsulinPump::InsulinPump(int battery, double insulinLevel, double insulinOnBoard) :
    battery(battery),
    insulinLevel(insulinLevel),
    insulinOnBoard(insulinOnBoard)
{
    this->bolusCalculator = new BolusCalculator();
    this->batteryUsage = 0;
    this->batteryOffset = 5;
    this->currGlucoseLevel = 0;
    this->profileManager = new ProfileManager();
}


InsulinPump::~InsulinPump(){
    delete bolusCalculator;
    delete profileManager;
}

void InsulinPump::initailizeBolus(PersonalProfile* profile, int totalCarbs, double currentBG){
    this->bolusCalculator->calculateBolus(totalCarbs, currentBG, profile);
}

Error InsulinPump::giveBolus(){
    //check if there is enough insulin

    //check battery level

    //check if pump has enough insulin for the bolus

    //Deliver immediate bolus

    //startextended bolus if neded

    // Reduce battery by 1% per unit (simplified)cd
    Error error;
    return error;
}

void InsulinPump::startBasalDelievery(){
    basalDeliveryActive = true;//this would start a background process that continously delivers basal insulin
}

void InsulinPump::stopBasalDelievery(){
    basalDeliveryActive = false;//this would stop the basal delivey process
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
ProfileManager* InsulinPump::getProfileManager(){
    return profileManager;
}

double InsulinPump::getGlucoseLevel(){return currGlucoseLevel;}

void InsulinPump::setGlucoseLevel(double g){currGlucoseLevel = g;}

// Should be implemented by functions returning an error
// void InsulinPump::raiseError(){

// }
