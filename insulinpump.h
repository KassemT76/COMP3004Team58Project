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

    void initailizeBolus(double, double);
    void initailizeExtended(int, int, double, double, double);
    QString giveBolus(int, int, double, double, double); // return true if successful
    QString distributeInsulin();// to be called every tick
    void startBasalDelievery();
    void stopBasalDelievery();
    void startBolusDelievery();
    void stopBolusDelievery();
    // void raiseError();

    // getters
    int getBattery();
    double getInsulinLevel();
    double getInsulinOB();
    bool getBasalActive();
    bool getBolusActive();
    ProfileManager* getProfileManager();
    BolusCalculator* getBolusCalculator();
    // setters
    void setBattery(int);
    void setInsulinLevel(double);
    void setInsulinOB(double);


private:
    int battery;
    double insulinLevel;
    double insulinOnBoard;
    bool basalActive;
    bool bolusActive;
    BolusCalculator* bolusCalculator;
    ProfileManager* profileManager;
    int timeInHours;
    double currGlucoseLevel;
};

#endif // INSULINPUMP_H
