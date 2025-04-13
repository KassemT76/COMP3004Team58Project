#include "insulinpump.h"

InsulinPump::InsulinPump(int battery, double insulinLevel, double insulinOnBoard) :
    battery(battery),
    insulinLevel(insulinLevel),
    insulinOnBoard(insulinOnBoard)
{
    currGlucoseLevel = 0;
    bolusCalculator = new BolusCalculator();
    profileManager = new ProfileManager();
}


InsulinPump::~InsulinPump(){
    delete bolusCalculator;
    delete profileManager;
}
void InsulinPump::initailizeBolus(double totalCarbs, double currentBG){
    if(profileManager->getActiveProfile() != nullptr){//when theres an active profile
        bolusCalculator->calculateBolus(totalCarbs, currentBG, profileManager->getActiveProfile());
    }
}
void InsulinPump::initailizeExtended(int now, int later, int duration, double totalCarbs, double currentBG){
    if(profileManager->getActiveProfile() != nullptr){//when theres an active profile
        bolusCalculator->calculateBolus(totalCarbs, currentBG, profileManager->getActiveProfile());
        bolusCalculator->calculateExtended(now, later, duration);
    }
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
BolusCalculator* InsulinPump::getBolusCalculator(){
    return bolusCalculator;
}

// Should be implemented by functions returning an error
// void InsulinPump::raiseError(){

// }
