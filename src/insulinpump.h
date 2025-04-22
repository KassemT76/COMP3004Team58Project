#ifndef INSULINPUMP_H
#define INSULINPUMP_H

#include "error.h"
#include "boluscalculator.h"
#include "profilemanager.h"
#include "screenprofilesetup.h"
#include <cmath>
#include <random>
#include <queue>


/**
 * @brief The InsulinPump class represents an insulin pump that manages insulin delivery and glucose levels.
 * 
 * @details The InsulinPump class is designed to simulate the behavior of an insulin pump in a diabetes management system.
 * It includes methods for initializing bolus and basal delivery, distributing insulin based on glucose levels, 
 * and managing battery usage. The class also interacts with a BolusCalculator and ProfileManager to calculate
 * the required insulin doses based on user profiles and carbohydrate intake.
 * 
 * @note The class uses a sinusoidal function (representing the CGM)to simulate glucose level changes over time, and 
 * it includes error handling for low insulin levels, low battery, and other conditions. The insulin delivery is managed 
 * through a queue system to keep track of insulin on board (IOB) and ensure that the insulin levels are within safe limits.
 * 
 * @warning This class is intended for educational and simulation purposes only and should not be used for actual medical
 * treatment or diagnosis.
 * 
 * @author Ariz Kazani and Hollen Lo
 */


class InsulinPump
{
public:
    InsulinPump(int battery=100, double insulinLevel=0, double insulinOnBoard=0, double inGluc=0, bool insulin=false);
    ~InsulinPump();

    /**
     * @brief This method initializes the bolus calculator with the given total carbs and current blood glucose level.
     * 
     * @param totalCarbs The total carbs to be calculated.
     * @param currentBG The current blood glucose level.
     * 
     * @note This method should be called every time the user changes the profile or starts a bolus.
     */
    void initailizeBolus(double, double);

    /**
     * @brief This method initializes the extended bolus calculator with the given parameters.
     * 
     * @param now The current time.
     * @param later The time when the bolus should be given.
     * @param durHr The duration in hours.
     * @param durMin The duration in minutes.
     * @param currTime The current time in minutes.
     * @param totalCarbs The total carbs to be calculated.
     * @param currentBG The current blood glucose level.
     * 
     * @note This method should be called every time the user changes the profile or starts a bolus.
     */
    void initailizeExtended(int, int, int, int, int, double, double);

    /**
     * @brief This method gives a bolus based on the given parameters.
     * 
     * @param now The current time.
     * @param later The time when the bolus should be given.
     * @param durHr The duration in hours.
     * @param durMin The duration in minutes.
     * @param currTime The current time in minutes.
     * @param totalCarbs The total carbs to be calculated.
     * @param currentBG The current blood glucose level.
     * 
     * @return QString A message indicating the result of the operation.
     */
    QString giveBolus(int, int, int, int, int, double, double);
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

    /**
     * @brief This method retrieves the current insulin level.
     * 
     * @return double The current insulin level.
     */
    double getInsulinLevel() {return insulinLevel;}

    /**
     * @brief This method retrieves the current insulin on board (IOB) level.
     * 
     * @return double The current insulin on board level.
     */
    void rechargeInsulin() {insulinLevel = 20;}


    double getInsulinOB();
    bool getBasalActive();
    bool getBolusActive();

    /**
     * 
     * @brief This method retrieves if basiz
     */
    bool getBasalDeActive() {return basalDeActive;}

    double getGlucoseLevel();
    ProfileManager* getProfileManager();
    BolusCalculator* getBolusCalculator();
    // setters

    void setBattery(int);


    void setInsulinLevel(double);
    void setInsulinOB(double);

    /**
     * @deprecated This function does not actually manipulate the glucose level,
     * the glucose level is automatically updated by the CGM. To update the glucose level,
     * use increaseGlucoseLevel() or decreaseGlucoseLevel().
     * 
     * @param inGluc The new glucose level to be set.
     * @return void
     */
    void setGlucoseLevel(double);

    /**
     * This function increases the glucose level by the given amount of carbs.
     */
    void increaseGlucoseLevel(double);
    void decreaseGlucoseLevel(double);

private:
    int battery;
    int batteryUsage;

    // the number of times the battery can be used before battery % goes down by 1
    int batteryOffset; 

    // the amount of insulin in the pump
    double insulinLevel;

    // the amount of insulin on board
    double insulinOnBoard;

    // the amound of bolus to distribute immediately
    double immediateBolus;

    
    bool basalActive;
    bool bolusActive;
    bool bolusImmediateActive;
    bool basalDeActive;
    bool runningInsulin;


    double bolusDecayRate; // rate at which the bolus decays

    std::queue<double> insulinQueue; // que to store insulin values

    BolusCalculator* bolusCalculator;
    ProfileManager* profileManager;
    int timeInHours;
    double currGlucoseLevel;
    double glucoseLevel;
    bool insulinActive;
};

#endif // INSULINPUMP_H
