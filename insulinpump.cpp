#include "insulinpump.h"
#include <QDebug>
InsulinPump::InsulinPump(int battery, double insulinLevel, double insulinOnBoard, double inGluc, bool insulin) :
    battery(battery),
    insulinLevel(insulinLevel),
    insulinOnBoard(insulinOnBoard),
    glucoseLevel(inGluc),
    insulinActive(insulin)
{
    immediateBolus = 0;
    bolusCalculator = new BolusCalculator();
    batteryUsage = 0;
    batteryOffset = 5;
    currGlucoseLevel = 0;
    profileManager = new ProfileManager();
    basalActive = false;
    bolusActive = false;
    bolusImmediateActive = false;
    basalDeActive = false;
    bolusDecayRate = 7;
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
        else if(profileManager->getActiveProfile() != nullptr && !bolusActive && !bolusImmediateActive && !basalActive){
            //when nothing is happening and theres an active profile
            message += " | starting basal delivery from: "+profileManager->getActiveProfile()->getName();
            startBasalDelievery();
        }
    }
    return message;
}

QString InsulinPump::giveBolus(int now, int later, int durHr, int durMin, int currTime, double totalCarbs, double currentBG){
    QString message = "";
    Error error;
    if(profileManager->getActiveProfile() == nullptr){
        return " | No profiles selected, a profile is needed as to assess bolus delivery";
    }
    if(currentBG <= 0){//when no glucose is entered, use the glucose in insulin pump
        currentBG = currGlucoseLevel;
    }
    //initialize bolus calc if hadn't already(ie didn't view calculations or units)
    if(now < 0){//when immediate, now, later, durHr, durMin are set to -1(aka invalid)
        initailizeBolus(totalCarbs, currentBG);
        //bolusCalculator->getFinalBolus();
        immediateBolus = bolusCalculator->getFinalBolus();

    }
    else{//when extended, all values are valid are intialized
        initailizeExtended(now, later, durHr, durMin, currTime, totalCarbs, currentBG);
        immediateBolus = bolusCalculator->getImmediateBolus();
        startBolusDelievery();
    }
    //check if there is enough insulin
    if(insulinLevel < getBolusCalculator()->getTotalRequiredBolus()){
        stopBolusDelievery();
        bolusImmediateActive = false;
        return error.getErrorMessage(ErrorType::LOW_INSULIN_BOLUS);
    }
    //startextended bolus if nedeed
    bolusImmediateActive = true;
    stopBasalDelievery();
    return message;
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

QString InsulinPump::distributeInsulin(int timeStep){
    QString message = "";
    Error error;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-0.5, 0.5);
    double randomValue = dis(gen);

    bolusDecayRate = std::min(7.0, bolusDecayRate + 0.2);

    auto sinosoidalFunction = [this](double x){
        return 4 * sin((1.0) * x) + bolusDecayRate;
    };
    
    double rad = timeStep * (M_PI / 180.0);
    double result = sinosoidalFunction(rad);
    
    double predictedRad = (timeStep + 30) * (M_PI / 180.0);
    double predictedResult = sinosoidalFunction(predictedRad);

    //Deliver immediate bolus
    if(predictedResult < 3.9){
        basalDeActive = true;
        message += " | "+ error.getErrorMessage(ErrorType::LOW_GLUCOSE);
        
    } else {
        basalDeActive = false;
    }
    if(predictedResult > 10){
        bolusDecayRate -= 4;
        insulinLevel -= 4;
        message += " | "+ error.getErrorMessage(ErrorType::HIGH_GLUCOSE);
    }
    double totalInsulin5Min = 0;
    if(basalActive && !basalDeActive){//when basalActive = T, there is an active profile
        if(profileManager->getActiveProfile()->getStartTime() <= timeStep){//active profile must be within the time
            double basalRate = profileManager->getActiveProfile()->getBasalRate();
            double basal5Min = (basalRate / 60.0) * 5.0; // basal rate per 5 min
            // Correction
            double correction = (currGlucoseLevel - profileManager->getActiveProfile()->getTargetBG()) / profileManager->getActiveProfile()->getCorrectionFactor();
            totalInsulin5Min = std::max((basal5Min + correction) - getInsulinOB(), 0.0);
            message += " | basal delivered: "+QString::number(totalInsulin5Min);
        }
        else{
            message += " | no basal delivered since not in delivery time";
        }
    }
    else if(bolusActive || bolusImmediateActive){//bolusActive
        if(bolusImmediateActive){//deliver immediate bolus first
            bolusImmediateActive = false;
            message += " | immediate bolus delivered: "+QString::number(immediateBolus);
            bolusDecayRate -= immediateBolus;
            insulinLevel -= immediateBolus;
        }
        else{
            double bolus5Min = bolusCalculator->getBolusRatePerHour()/60 * 5.0;
            totalInsulin5Min = std::max((bolus5Min + bolusCalculator->getCorrectionBolus()) - getInsulinOB(), 0.0);
            message += " | bolus delivered: "+QString::number(totalInsulin5Min);
        }
    }
    currGlucoseLevel = result + randomValue - totalInsulin5Min;
    
    insulinLevel -= totalInsulin5Min;

    //check if pump has enough insulin for the bolus
    // TODO : do something with this code
    if(insulinLevel <= 0){
        message += " | "+ error.getErrorMessage(ErrorType::INSULIN_OUT);

    }
    else if(insulinLevel <= 30){
        message += " | "+ error.getErrorMessage(ErrorType::LOW_INSULIN);
    }

    // this updates the battery level
    if(battery <= 0){
        message += " | "+error.getErrorMessage(ErrorType::POWER_OUT);
    }
    else if(battery <= 30){
        message += " | "+error.getErrorMessage(ErrorType::LOW_POWER);
    }

    /**
     * Que functions, this is where the insulin is added to the queue
     * add the insulin added to iob
     * check if the queue is over 3 hours, if so remove the first element
     */
    insulinQueue.push(totalInsulin5Min);
    insulinOnBoard += totalInsulin5Min;

    if (insulinQueue.size() > 24) { // 36 * 5 min = 3 hours
        insulinOnBoard -= insulinQueue.front();
        insulinQueue.pop();
    }

    for (int i = 0; i < insulinQueue.size(); i++) {
        double item = insulinQueue.front();
        insulinOnBoard -= item;
        item *= 0.7;
        insulinOnBoard += item;
        insulinQueue.push(item);
        insulinQueue.pop();
    }
    
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
