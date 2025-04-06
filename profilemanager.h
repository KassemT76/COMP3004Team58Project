#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

class ScreenProfileSetup;
#include "personalprofile.h"
#include <QObject>


class ProfileManager {

public:
    explicit ProfileManager();
    ~ProfileManager();
    void addProfile(QString, double, double, double, double, int, int);
    void removeProfile(QString);
    void editProfile(int, QString, QString);
    void selectProfile(QString);
    PersonalProfile* getActiveProfile();
    PersonalProfile* getProfile(QString);
private:
    QVector<PersonalProfile*> profiles;
    PersonalProfile* activeProfile;

};

#endif // PROFILEMANAGER_H
