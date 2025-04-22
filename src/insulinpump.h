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
 * @authors Ariz Kazani and Hollen Lo
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

    /**
     * @brief This method is a wrapper class that is used for logging, it calls 
     * 
     * @param currTime The current time in minutes.
     * @return QString A message indicating the result of the operation.
     */
    QString giveBasal(int);

    /**
     * @brief This method stops the basal delivery.
     * 
     * @return QString A message indicating the result of the operation.
     */
    QString stopBasal();

    /**
     * @brief This method updates the CGM (Continuous Glucose Monitor) based on the current time.
     * 
     * @param currTime The current time in minutes.
     * @return QString A message indicating the result of the operation.
     */
    QString updateCGM(int);

    /**
     * @brief This method retrieves the current glucose level.
     * 
     * @return double The current glucose level.
     */
    double getCurrentGlucose() {return glucoseLevel;}

    /**
     * @brief This method sets the current glucose level.
     * 
     * @param inGluc The new glucose level to be set.
     */
    void setCurrentGlucose(double inGluc){glucoseLevel = inGluc;}

    /**
     * @brief This method retrieves the current insulin level.
     * 
     * @return double The current insulin level.
     */
    bool getInsulinActive() {return insulinActive;}

    /**
     * @brief This method sets the insulin active status.
     * 
     * @param insulin The new insulin active status to be set.
     */
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
     * @brief This method starts and stops the basal and bolus delivery.
     * 
     * @note These methods are used to control the insulin delivery process.
     */
    void startBasalDelievery();

    /**
     * @brief This method stops the basal delivery.
     * 
     * @note This method is used to stop the insulin delivery process.
     */
    void stopBasalDelievery();

    /**
     * @brief This method starts and stops the bolus delivery.
     * 
     * @note These methods are used to control the insulin delivery process.
     */
    void startBolusDelievery();

    /**
     * @brief This method stops the bolus delivery.
     * 
     * @note This method is used to stop the insulin delivery process.
     */
    void stopBolusDelievery();

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

    /**
     * @brief This method retrieves the current insulin on board (IOB) level.
     * 
     * @note IOB is the amount of insulin that is still active in the body.
     * 
     * @return double The current insulin on board level.
     */
    double getInsulinOB();

    /**
     * @brief This method retrieves the current immediate bolus level.
     * 
     * @return double The current immediate bolus level.
     */
    bool getBasalActive();

    /**
     * @brief This method retrieves the current bolus active status.
     * 
     * @return bool The current bolus active status.
     */
    bool getBolusActive();

    /**
     * 
     * @brief This method retrieves if basiz
     */
    bool getBasalDeActive() {return basalDeActive;}

    /**
     * @brief This method retrieves the current glucose level.
     * 
     * @return double The current glucose level.
     */
    double getGlucoseLevel();

    /**
     * @brief This method retrieves the current bolus calculator.
     * 
     * @return BolusCalculator* A pointer to the current bolus calculator.
     */
    ProfileManager* getProfileManager();

    /**
     * @brief This method retrieves the current bolus calculator.
     * 
     * @return BolusCalculator* A pointer to the current bolus calculator.
     */
    BolusCalculator* getBolusCalculator();
    
    /**
     * @brief This method sets the battery percentage.
     * 
     * @param newBattery The new battery percentage to be set.
     */
    void setBattery(int);

    /**
     * @brief This method sets the insulin level.
     * 
     * @param newLevel The new insulin level to be set.
     */
    void setInsulinLevel(double);

    /**
     * @brief This method sets the insulin on board (IOB) level.
     * 
     * @param newOB The new insulin on board level to be set.
     */
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
     * @brief This method increases the glucose level by the given amount.
     * 
     * @param g The amount to increase the glucose level by.
     */
    void increaseGlucoseLevel(double);

    /**
     * @brief This method decreases the glucose level by the given amount.
     * 
     * @param g The amount to decrease the glucose level by.
     */
    void decreaseGlucoseLevel(double);

private:
    int battery;                     // the battery percentage (out of 100)
    int batteryUsage;                // the number of times useBattery() has been called
    int batteryOffset;               // the number of times the battery can be used before battery % goes down by 1

    double insulinLevel;             // the amount of insulin in the pump
    double insulinOnBoard;           // the amount of insulin on board (IOB)

    double immediateBolus;           // the amount of immediate bolus to be given

    bool basalActive;                // true if basal delivery is active
    bool bolusActive;                // true if bolus delivery is active
    bool bolusImmediateActive;       // true if immediate bolus needs to be given
    bool basalDeActive;              // true if basal delivery needs to be stopped, due to low glucose
    bool runningInsulin;             // true if insulin is being delivered


    double bolusDecayRate;           // rate at which the bolus decays

    std::queue<double> insulinQueue; // que to store insulin values

    BolusCalculator* bolusCalculator;// pointer to the bolus calculator
    ProfileManager* profileManager;  // pointer to the profile manager
    int timeInHours;                 // the time in hours
    double currGlucoseLevel;         // the current glucose level
    double glucoseLevel;             // 
    bool insulinActive;              // true if insulin is active
};

#endif // INSULINPUMP_H
