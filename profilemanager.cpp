#include "profilemanager.h"
#include <QDebug>
#include "screenprofilesetup.h"
#include <cmath>

ProfileManager::ProfileManager(){
    activeProfile = nullptr;
}

ProfileManager::~ProfileManager(){
    for(PersonalProfile* profile : profiles){
        delete profile;
    }
}
void ProfileManager::addProfile(QString inName, double inBasalRate, double inCarbRatio, double inCorrectionFactor, double inTargetBG, int inStartTime, int inEndTime){
    if(getProfile(inName) != nullptr || profiles.length() >= 6){
        return;//if profile name exists or number of profiles exceed 6
    }
    PersonalProfile *newProfile = new PersonalProfile(inName, inBasalRate, inCarbRatio, inCorrectionFactor, inTargetBG, inStartTime, inEndTime);
    profiles.append(newProfile);
}
void ProfileManager::removeProfile(QString inName){
    PersonalProfile* gotProfile = getProfile(inName);
    if(activeProfile == gotProfile){
        activeProfile = nullptr;
    }
    profiles.removeOne(gotProfile);
    delete gotProfile;
}
void ProfileManager::editProfile(int index, QString input, QString rowName){
    PersonalProfile* profile = getProfile(rowName);
    if(index == 0){//Time
        int startHr = input.mid(0, 2).toInt();
        int startMin = input.mid(3, 2).toInt();
        int endHr = input.mid(6, 2).toInt();
        int endMin = input.mid(9, 2).toInt();
        int startTime = startHr*60 + startMin;
        int endTime = endHr*60 + endMin;
        profile->setStartTime(startTime);
        profile->setEndTime(endTime);
    }
    else if(index == 1){//Basal
        double basal = input.toDouble();
        profile->setBasalRate(basal);
    }
    else if(index == 2){//Correct
        double correct = input.toDouble();
        profile->setCorrectionFactor(correct);
    }
    else if(index == 3){//Carb
        double carb = input.toDouble();
        profile->setCarbRatio(carb);
    }
    else if(index == 4){//Target
        double target = input.toDouble();
        profile->setTargetBG(target);
    }
}
void ProfileManager::selectProfile(QString inName){
    activeProfile = getProfile(inName);
}
PersonalProfile* ProfileManager::getActiveProfile(){
    return activeProfile;
}
void ProfileManager::updateActiveProfile(int currTime){
    PersonalProfile* newProfile = nullptr;
    int closestTime = MAXTIME;
    for(PersonalProfile* profile: profiles){
        if(abs(profile->getStartTime() - currTime) < closestTime && profile->getEndTime() > currTime){//get the profile with the closest start time
            newProfile = profile;
            closestTime = abs(profile->getStartTime() - currTime);
        }
    }
    activeProfile = newProfile;
}

PersonalProfile* ProfileManager::getProfile(QString profileName){
    for(PersonalProfile* profile: profiles){
        if(profile->getName() == profileName){
            return profile;
        }
    }
    return nullptr;
}
void ProfileManager::resetActiveProfile(){
    activeProfile = nullptr;
}
