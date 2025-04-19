#include "insulinpump.h"
InsulinPump::InsulinPump(int battery, double insulinLevel, double insulinOnBoard, double inGluc, bool insulin) :
    battery(battery),
    insulinLevel(insulinLevel),
    insulinOnBoard(insulinOnBoard),
    glucoseLevel(inGluc),
    insulinActive(insulin)
{
    bolusCalculator = new BolusCalculator();
    batteryUsage = 0;
    batteryOffset = 5;
    currGlucoseLevel = 0;
    profileManager = new ProfileManager();
    basalActive = false;
    bolusActive = false;
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
void InsulinPump::initailizeExtended(int now, int later, int durHr, int durMin, int currTime, double totalCarbs, double currentBG){
    if(profileManager->getActiveProfile() != nullptr){//when theres an active profile
        bolusCalculator->calculateBolus(totalCarbs, currentBG, profileManager->getActiveProfile(), insulinOnBoard);
        bolusCalculator->calculateExtended(now, later, durHr, durMin, currTime);
    }
}
QString InsulinPump::updateCGM(int currTime){//checks if current basal has finished its delivery period
    QString message = "";
    //Bolus:
    if(bolusActive){//if bolus is active and extended, check if it is finished
        if(bolusCalculator->getEndTime() < currTime){
            message += " | bolus has finished, changing to: ";
            stopBolusDelievery();
            profileManager->updateActiveProfile(currTime);
            if(profileManager->getActiveProfile() == nullptr){//profile DNE
                message += "NONE";
                stopBasalDelievery();
            }
            else{//profile exists
                message += profileManager->getActiveProfile()->getName();
                startBasalDelievery();
            }
        }
    }
    else{//Basal:
        if(profileManager->getActiveProfile() == nullptr && !basalActive){//if no active profile
            profileManager->updateActiveProfile(currTime);
            if(profileManager->getActiveProfile() != nullptr){//if theres an available profile
                message += " | starting basal delivery from: "+profileManager->getActiveProfile()->getName();
                startBasalDelievery();
            }
        }
        else if(profileManager->getActiveProfile()->getEndTime() < currTime && basalActive){//if active profile has expired
            message += " | "+profileManager->getActiveProfile()->getName()+" has expired, changing to: ";
            profileManager->updateActiveProfile(currTime);
            if(profileManager->getActiveProfile() == nullptr){//profile DNE
                message += "NONE";
                stopBasalDelievery();
            }
            else{//profile exists
                message += profileManager->getActiveProfile()->getName();
                startBasalDelievery();
            }
        }
    }
    return message;
}

QString InsulinPump::giveBolus(int now, int later, int durHr, int durMin, int currTime, double totalCarbs, double currentBG){
    Error error;
    if(profileManager->getActiveProfile() == nullptr){
        return " | No profiles selected, a profile is needed as to assess bolus delivery";
    }
    //initialize bolus calc if hadn't already(ie didn't view calculations or units)
    if(now < 0){//when immediate, now, later, durHr, durMin are set to -1(aka invalid)
        initailizeBolus(totalCarbs, currentBG);
    }
    else{//when extended, all values are valid are intialized
        initailizeExtended(now, later, durHr, durMin, currTime, totalCarbs, currentBG);
    }
    //check if there is enough insulin
    if(insulinLevel < getBolusCalculator()->getTotalRequiredBolus()){
        return error.getErrorMessage(ErrorType::LOW_INSULIN_BOLUS);
    }
    //startextended bolus if nedeed
    stopBasalDelievery();
    startBolusDelievery();
    return " | Bolus Activated";
}
QString InsulinPump::giveBasal(int currTime){
    if(profileManager->getActiveProfile() == nullptr){//when no active profile
        return "";
    }
    if(profileManager->getActiveProfile()->getEndTime() < currTime){//when profile is not within the current time period
        return " | time range for profile has expired, choose another profile";
    }
    startBasalDelievery();
    stopBolusDelievery();
    return " | starting basal delivery from: "+profileManager->getActiveProfile()->getName();
}
QString InsulinPump::stopBasal(){
    if(profileManager->getActiveProfile() == nullptr || !basalActive){//when no active profile
        return "";
    }
    stopBasalDelievery();
    return " | stopping basal delivery from: "+profileManager->getActiveProfile()->getName();
}


/*
TODO add an error message if the user tries to give a bolus when the pump is already giving a bolus

caclculate how much insulin to give

if the glucose is under X then give higher bolus

if the glucose is over X then stop giving bolus

get the glucose from sinosodial function for a test and make that function
*/
QString InsulinPump::distributeInsulin(int timeStep){
    Error error;
    QString message = "";
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
    else if(currGlucoseLevel > 10){
        message += " | "+ error.getErrorMessage(ErrorType::HIGH_GLUCOSE);
    }

    if(basalActive){
     //get stats from: profileManager->getActiveProfile()->
    }
    else{//bolusActive
     //get stats from: bolusCalculator->
    }
    //Natural Body

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);
    double randomValue = dis(gen);

    auto sinosoidalFunction = [](double x){
        return 3.05 * cos((3.0) * x) + 6.95;
    };

    insulinActive = false;

    double rad = timeStep * (M_PI / 180.0);
    double result = sinosoidalFunction(rad);

    double predictedRad = (timeStep + 30) * (M_PI / 180.0);
    double predictedResult = sinosoidalFunction(predictedRad);

    glucoseLevel = result + randomValue;
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
