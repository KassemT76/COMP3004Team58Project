#ifndef INSULINPUMP_H
#define INSULINPUMP_H

#include "error.h"
#include "boluscalculator.h"
#include "profilemanager.h"
#include "screenprofilesetup.h"
# include <cmath>
#include <random>

/**
 * @brief The current glucose level and insulin active status are stored in this class.
 */

class InsulinPump
{
public:
    InsulinPump(int battery=100, double insulinLevel=0, double insulinOnBoard=0, double inGluc=0, bool insulin=false);
    ~InsulinPump();

    void initailizeBolus(double, double);
    void initailizeExtended(int, int, int, int, int, double, double);
    QString giveBolus(int, int, int, int, int, double, double); // return true if successful
    QString giveBasal(int);
    QString stopBasal();
    QString updateCGM(int);
    void initailizeExtended(int, int, double, double, double);
    QString giveBolus(int, int, double, double, double); // return true if successful
    double getCurrentGlucose() {return glucoseLevel;}
    void setCurrentGlucose(double inGluc){glucoseLevel = inGluc;}
    bool getInsulinActive() {return insulinActive;}
    void setInsulin(bool insulin){insulinActive = insulin;}

    /**
     * @brief This method distributes insulin based on the current time step. It uses a sinusoidal function to calculate
     * the amount of insulin to be distributed.
     * s
     * @param timeStep The current time step.
     * @return InsulinInformation* A pointer to an InsulinInformation object containing the result of the distribution.
     */
     QString distributeInsulin(int timeStep);


    /**
     * @brief This method initializes the bolus calculator with the given profile and carbs. This method should be called
     * every time the user changes the profile or starts a bolus.
     * 
     * @param profile The personal profile of the user.
     * @param totalCarbs The total carbs to be calculated.
     * @param currentBG The current blood glucose level.
     */
    void initailizeBolus(PersonalProfile* profile, int totalCarbs, double currentBG);

    Error giveBolus(); // return true if successful
    void startBasalDelievery();
    void stopBasalDelievery();
    void startBolusDelievery();
    void stopBolusDelievery();
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
     * @param offset The offset to be set. It should be greater than 0.
     * 
     * @return true if the offset is set successfully, false otherwise.
     */
    bool setBatteryOffset(int offset);

    /**
     * @brief This method retrieves the current battery percentage.
     * 
     * @return int The current battery percentage.
     */
    int getBattery();


    double getInsulinLevel();
    double getInsulinOB();
    bool getBasalActive();
    bool getBolusActive();

    /**
     * 
     * @brief This method retrieves if basiz
     */
    bool getBasilDeActive() {return basilDeActive;}


    /**
     * @deprecated This method is deprecated, use rechargeBattery() instead.
     * 
     * @brief This method retrieves the bolus calculator.
     * 
     * @return BolusCalculator* The bolus calculator.
     */

    double getGlucoseLevel();
    ProfileManager* getProfileManager();
    BolusCalculator* getBolusCalculator();
    // setters

    void setBattery(int);


    void setInsulinLevel(double);
    void setInsulinOB(double);
    void setGlucoseLevel(double);


private:
    int battery;
    int batteryUsage;

    // the number of times the battery can be used before battery % goes down by 1
    int batteryOffset; 

    double insulinLevel;
    double insulinOnBoard;
    bool basalActive;
    bool bolusActive;

    bool basilDeActive;

    BolusCalculator* bolusCalculator;
    ProfileManager* profileManager;
    int timeInHours;
    double currGlucoseLevel;
    double glucoseLevel;
    bool insulinActive;
};

#endif // INSULINPUMP_H
