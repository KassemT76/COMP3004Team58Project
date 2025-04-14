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
        bolusCalculator->calculateBolus(totalCarbs, currentBG, profileManager->getActiveProfile(), insulinOnBoard);
    }
}
void InsulinPump::initailizeExtended(int now, int later, double duration, double totalCarbs, double currentBG){
    if(profileManager->getActiveProfile() != nullptr){//when theres an active profile
        bolusCalculator->calculateBolus(totalCarbs, currentBG, profileManager->getActiveProfile(), insulinOnBoard);
        bolusCalculator->calculateExtended(now, later, duration);
    }
}
QString InsulinPump::giveBolus(int now, int later, double duration, double totalCarbs, double currentBG){
    Error error;
    QString message = "";
    //initialize bolus calc if hadn't already(ie didn't view calculations or units)
    if(duration <= 0){
        initailizeBolus(totalCarbs, currentBG);
    }
    else{
        initailizeExtended(now, later, duration, totalCarbs, currentBG);
    }
    //check if there is enough insulin
    if(insulinLevel < getBolusCalculator()->getTotalRequiredBolus()){
        return error.getErrorMessage(ErrorType::LOW_INSULIN_BOLUS);
    }
    //startextended bolus if nedeed
    stopBasalDelievery();
    startBolusDelievery();
    return message;
}
QString InsulinPump::distributeInsulin(){
    Error error;
    QString message = "";
    battery--;
    if(!basalActive && !bolusActive){
        return message;
    }
    // Reduce battery by 1% per unit (simplified)cd
    //check battery level
    if(battery <= 0){
        message += " | "+error.getErrorMessage(ErrorType::POWER_OUT);
    }
    else if(battery <= 30){
        message += " | "+error.getErrorMessage(ErrorType::LOW_POWER);
    }
    //check if pump has enough insulin for the bolus
    if(insulinLevel <= 0){
        message += " | "+ error.getErrorMessage(ErrorType::INSULIN_OUT);
    }
    else if(insulinLevel <= 30){
        message += " | "+ error.getErrorMessage(ErrorType::LOW_INSULIN);
    }
    //Deliver immediate bolus
    if(currGlucoseLevel < 3.9){
        message += " | "+ error.getErrorMessage(ErrorType::LOW_GLUCOSE);
    }
    /*
    else if(currGlucoseLevel > CHANGE THIS TO SOME VALUE){
        message += " | "+ error.getErrorMessage(ErrorType::HIGH_GLUCOSE);
    }
    */
    return message;
}

void InsulinPump::startBasalDelievery(){
    basalActive = true;//this would start a background process that continously delivers basal insulin
}

void InsulinPump::stopBasalDelievery(){
    basalActive = false;//this would stop the basal delivey process
}
void InsulinPump::startBolusDelievery(){
    bolusActive = true;
}
void InsulinPump::stopBolusDelievery(){
    bolusActive = false;
}
int InsulinPump::getBattery(){
    return battery;
}
double InsulinPump::getInsulinLevel(){
    return insulinLevel;
}
bool InsulinPump::getBasalActive(){
    return basalActive;
}
bool InsulinPump::getBolusActive(){
    return bolusActive;
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
