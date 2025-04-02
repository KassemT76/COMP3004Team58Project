#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

class ScreenProfileSetup;

#include <QObject>


class ProfileManager {

public:
    explicit ProfileManager(ScreenProfileSetup* profileSetupScreen);
    ~ProfileManager();

private:
    ScreenProfileSetup* profileSetupScreen;


};

#endif // PROFILEMANAGER_H
