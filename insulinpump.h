#ifndef INSULINPUMP_H
#define INSULINPUMP_H

#include "error.h"
#include "boluscalculator.h"

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

    /**
     * @brief This method uses the battery and returns the remaining battery.
     * 
     * @return int The remaining battery.
     */
    int useBattery();

    /**
     * @brief This method recharges the battery to 100%.
     */
    void rechargeBattery();

    /**
     * @brief This method sets the offset for the battery. The battery offset is the number
     * of times the battery can be used before the battery percentage goes down by 1. For 
     * example, if the battery offset is 5, then the battery percentage will go down by 1 after
     * useBattery() is called 5 times.
     * 
     * @return true if the offset is set successfully, false otherwise.
     */
    bool setBatteryOffset(int offset);

    // getters
    int getBattery();
    double getInsulinLevel();
    double getInsulinOB();

    // setters
    void setBattery(int);
    void setInsulinLevel(double);
    void setInsulinOB(double);


private:
    int battery;
    int batteryUsage;

    // the number of times the battery can be used before battery % goes down by 1
    int batteryOffset; 

    double insulinLevel;
    double insulinOnBoard;
    bool basalDeliveryActive;
    BolusCalculator* bolusCalculator;
    int timeInHours;
};

#endif // INSULINPUMP_H
