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
QString InsulinPump::giveBasal(){
    if(profileManager->getActiveProfile() == nullptr){//when no active profile
        return "";
    }
    QString message = " | starting basal delivery from: "+profileManager->getActiveProfile()->getName();
    startBasalDelievery();
    stopBolusDelievery();
    return message;
}
QString InsulinPump::stopBasal(){
    if(profileManager->getActiveProfile() == nullptr){//when no active profile
        return "";
    }
    QString message = " | stopping basal delivery from: "+profileManager->getActiveProfile()->getName();
    stopBasalDelievery();
    return message;
}

/*
TODO add an error message if the user tries to give a bolus when the pump is already giving a bolus

caclculate how much insulin to give

if the glucose is under X then give higher bolus

if the glucose is over X then stop giving bolus

get the glucose from sinosodial function for a test and make that function
*/

InsulinInformation InsulinPump::distributeInsulin(){
    Error error;
    QString message = "";
    InsulinInformation info;
    if(!basalActive && !bolusActive){
        return info;
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

    if(basalActive){

    }
    else{//bolusActive

    }
    return info;
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

double InsulinPump::getGlucoseLevel(){return currGlucoseLevel;}

void InsulinPump::setGlucoseLevel(double g){currGlucoseLevel = g;}

// Should be implemented by functions returning an error
// void InsulinPump::raiseError(){

// }
