#ifndef PERSONALPROFILE_H
#define PERSONALPROFILE_H
#include <QObject>
#include <QTableWidgetItem>

/**
 * @brief This file contains the PersonalProfile class which is used to manage the personal profile of an insulin pump user.
 * @details The PersonalProfile class contains information about the user's insulin delivery settings,
 * including basal rate, insulin-to-carb ratio, correction factor, target blood glucose level, and time range.
 * It provides methods to get and set these values, as well as to display the time in a user-friendly format.
 * @authors Hollen Lo
 */

class PersonalProfile
{
public:
    PersonalProfile(QString name="default", double basalRate=0, double insulinToCarbRatio=1, double correctionFactor=1, double targetBG=0, int startTime=0, int endTime=0);
    
    /**
     * @brief This method retrieves the name of the profile.
     * 
     * @return The name of the profile as a QString.
     */
    QString getName();

    /**
     * @brief This method sets the name of the profile.
     * 
     * @param newName The new name to be set.
     */
    void setName(QString);

    /**
     * @brief This method retrieves the basal rate of the profile.
     * 
     * @return The basal rate of the profile as a double.
     */
    double getBasalRate();

    /**
     * @brief This method sets the basal rate of the profile.
     * 
     * @param newRate The new basal rate to be set.
     */
    void setBasalRate(double);

    /**
     * @brief This method retrieves the insulin-to-carb ratio of the profile.
     * 
     * @return The insulin-to-carb ratio of the profile as a double.
     */
    double getCarbRatio();

    /**
     * @brief This method sets the insulin-to-carb ratio of the profile.
     * 
     * @param newRatio The new insulin-to-carb ratio to be set.
     */
    void setCarbRatio(double);

    /**
     * @brief This method retrieves the correction factor of the profile.
     * 
     * @return The correction factor of the profile as a double.
     */
    double getCorrectionFactor();

    /**
     * @brief This method sets the correction factor of the profile.
     * 
     * @param newFactor The new correction factor to be set.
     */
    void setCorrectionFactor(double);

    /**
     * @brief This method retrieves the target blood glucose level of the profile.
     * 
     * @return The target blood glucose level of the profile as a double.
     */
    double getTargetBG();

    /**
     * @brief This method sets the target blood glucose level of the profile.
     * 
     * @param newTarget The new target blood glucose level to be set.
     */
    void setTargetBG(double);

    /**
     * @brief This method retrieves the start time of the profile.
     * 
     * @return The start time of the profile as an int.
     */
    int getStartTime();

    /**
     * @brief This method sets the start time of the profile.
     * 
     * @param time The new start time to be set.
     */
    void setStartTime(int);

    /**
     * @brief This method retrieves the end time of the profile.
     * 
     * @return The end time of the profile as an int.
     */
    int getEndTime();

    /**
     * @brief This method sets the end time of the profile.
     * 
     * @param time The new end time to be set.
     */
    void setEndTime(int);

    /**
     * @brief This method retrieves the insulin on board (IOB) of the profile.
     * 
     * @return The insulin on board of the profile as a double.
     */
    double getInsulinOB();

    /**
     * @brief This method sets the insulin on board (IOB) of the profile.
     * 
     * @param insulinOB The new insulin on board to be set.
     */
    void setInsulinOB(double insulinOB);

    /**
     * @brief This method retrieves the display time in a user-friendly format.
     * 
     * @param time The time to be displayed.
     * @return The display time as a QString. in the format of HH:MM
     */
    QString getDisplayTime(int);
    
private:
    QString name;              // name of the profile
    double basalRate;          // basal rate in units per hour
    double insulinToCarbRatio; // insulin-to-carb ratio
    double correctionFactor;   // correction factor for blood glucose level
    double targetBG;           // target blood glucose level
    int startTime;             // start time in hours
    int endTime;               // end time in hours
    double insulinOB;          // insulin on board
};

#endif // PERSONALPROFILE_H
