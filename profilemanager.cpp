#include "profilemanager.h"
#include <QDebug>
#include "screenprofilesetup.h"

ProfileManager::ProfileManager(ScreenProfileSetup* profileSetupScreen) :
   profileSetupScreen(profileSetupScreen)
{
    profileSetupScreen->setProfileManager(this);
    activeProfile = nullptr;
}

ProfileManager::~ProfileManager(){
    for(PersonalProfile* profile : profiles){
        delete profile;
    }
}
void ProfileManager::addProfile(QString inName, double inBasalRate, double inCarbRatio, double inCorrectionFactor, double inTargetBG, int inStartTime, int inEndTime){
    PersonalProfile *newProfile = new PersonalProfile(inName, inBasalRate, inCarbRatio, inCorrectionFactor, inTargetBG, inStartTime, inEndTime);
    profiles.append(newProfile);
}
void ProfileManager::removeProfile(){

}
void ProfileManager::editProfile(){

}
void ProfileManager::selectProfile(){

}
PersonalProfile* ProfileManager::getProfile(QString profileName){
    for(PersonalProfile* profile: profiles){
        if(profile->getName() == profileName){
            return profile;
        }
    }
    return nullptr;
}
