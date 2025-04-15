#ifndef INSULINPUMP_H
#define INSULINPUMP_H

#include "error.h"
#include "boluscalculator.h"
#include "profilemanager.h"
#include "screenprofilesetup.h"

class InsulinPump
{
public:
    InsulinPump(int battery=100, double insulinLevel=0, double insulinOnBoard=0);
    ~InsulinPump();

    void initailizeBolus(PersonalProfile* profile, int totalCarbs, double currentBG);
    Error giveBolus(); // return true if successful
    void startBasalDelievery();
    void stopBasalDelievery();
    // void raiseError();

    // getters
    int getBattery();
    double getInsulinLevel();
    double getInsulinOB();
    double getGlucoseLevel();
    ProfileManager* getProfileManager();
    // setters
    void setBattery(int);
    void setInsulinLevel(double);
    void setInsulinOB(double);
    void setGlucoseLevel(double);


private:
    int battery;
    double insulinLevel;
    double insulinOnBoard;
    bool basalDeliveryActive;
    BolusCalculator* bolusCalculator;
    ProfileManager* profileManager;
    int timeInHours;
    double currGlucoseLevel;
};

#endif // INSULINPUMP_H
