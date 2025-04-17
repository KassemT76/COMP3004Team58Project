#ifndef INSULINPUMP_H
#define INSULINPUMP_H

#include "error.h"
#include "boluscalculator.h"
#include "profilemanager.h"
#include "screenprofilesetup.h"

class InsulinInformation
{   
    public:

        InsulinInformation();

        /**
         * @brief This method retrieves the current glucose level.
         * 
         * @return double The current glucose level.
         */
        double currentGlucose();

        /**
         * @brief This mothod returns if glucose range requires insulin to be given.
         * 
         * @return double The current insulin level.
         */
        boolean isInsulinActive();

        /**
         * @brief This method return the message to be displayed on the screen.
         * 
         * @return QString The message to be displayed on the screen.
         */
        Qstring getMessage();

    private:
        double glucoseLevel;
        boolean insulinActive;
        QString message;

};

class InsulinPump
{
public:
    InsulinPump(int battery=100, double insulinLevel=0, double insulinOnBoard=0);
    ~InsulinPump();

    void initailizeBolus(double, double);
    void initailizeExtended(int, int, double, double, double);
    QString giveBolus(int, int, double, double, double); // return true if successful
    QString distributeInsulin();// to be called every tick

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
    BolusCalculator* bolusCalculator;
    ProfileManager* profileManager;
    int timeInHours;
    double currGlucoseLevel;
};

#endif // INSULINPUMP_H
