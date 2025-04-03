#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

class ScreenProfileSetup;
#include "personalprofile.h"
#include <QObject>


class ProfileManager {

public:
    explicit ProfileManager(ScreenProfileSetup* profileSetupScreen);
    ~ProfileManager();
    void removeProfile();
    void editProfile();
    void selectProfile();
private:
    ScreenProfileSetup* profileSetupScreen;
    QVector<PersonalProfile*> profiles;
    PersonalProfile* activeProfile;

};

#endif // PROFILEMANAGER_H
