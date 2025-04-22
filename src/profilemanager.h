#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

/**
 * @brief This file contains the ProfileManager class which is used to manage the personal profiles of an insulin pump user.
 * @details The ProfileManager class contains methods to add, remove, edit, and select profiles,
 * as well as to retrieve the active profile and other profiles.   
 * 
 * @author Hollen Lo
 */

class ScreenProfileSetup;
#include "personalprofile.h"
#include <QObject>

class ProfileManager {

public:
    explicit ProfileManager();
    ~ProfileManager();
    static constexpr int MAXTIME = 9999;//equivalent to 9999 minutes

    /**
     * @brief This method retrieves the active profile.
     * 
     * @param name The name of the profile.
     * @param basalRate The basal rate of the profile.
     * @param insulinToCarbRatio The insulin-to-carb ratio of the profile.
     * @param correctionFactor The correction factor of the profile.
     * @param targetBG The target blood glucose level of the profile.
     * @param startTime The start time of the profile.
     * @param endTime The end time of the profile.
     * 
     * @return The active profile as a PersonalProfile pointer.
     */
    void addProfile(QString, double, double, double, double, int, int);

    /**
     * @brief This method removes a profile with the given name.
     * 
     * @param name The name of the profile to be removed.
     */
    void removeProfile(QString);

    /**
     * @brief This method edits a profile with the given index and name.
     * 
     * @param index The index of the profile to be edited.
     * @param input The new value to be set.
     * @param rowName The name of the profile to be edited.
     */
    void editProfile(int, QString, QString);

    /**
     * @brief This method activates a profile with the given name.
     * 
     * @param name The name of the profile to be selected.
     */
    void selectProfile(QString);

    /**
     * @brief This method retrieves the active profile.
     * 
     * @return The active profile as a PersonalProfile pointer.
     */
    void updateActiveProfile(int);

    /**
     * @brief This method retrieves the active profile.
     * 
     * @return The active profile as a PersonalProfile pointer.
     */
    PersonalProfile* getActiveProfile();

    /**
     * @brief This method retrieves a profile with the given name.
     * 
     * @param name The name of the profile to be retrieved.
     * 
     * @return The profile as a PersonalProfile pointer.
     */
    PersonalProfile* getProfile(QString);

private:
    QVector<PersonalProfile*> profiles; // vector of profiles
    PersonalProfile* activeProfile;     // pointer to the active profile

};

#endif // PROFILEMANAGER_H
