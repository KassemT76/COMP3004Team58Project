#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

class ScreenProfileSetup;
#include "personalprofile.h"
#include <QObject>


class ProfileManager {

public:
    explicit ProfileManager(ScreenProfileSetup* profileSetupScreen);
    ~ProfileManager();
    void addProfile(QString, double, double, double, double, int, int);
    void removeProfile();
    void editProfile();
    void selectProfile();
    PersonalProfile* getProfile(QString);

private:
    ScreenProfileSetup* profileSetupScreen;
    QVector<PersonalProfile*> profiles;
    PersonalProfile* activeProfile;

};

#endif // PROFILEMANAGER_H
