#include "boluscalculator.h"

BolusCalculator::BolusCalculator() : bolus(0), correctionBolus(0), totalRequiredBolus(0), finalBolus(0), immediateBolus(0), extendedBolus(0), bolusRatePerHour(0) {}

void BolusCalculator::calculateBolus(double totalCarbs, double currentBG, PersonalProfile* profile) {
    bolus = totalCarbs / profile->getCarbRatio();
    if(currentBG <= 0){//if no BG was selected in bolus screen
        correctionBolus = (profile->getTargetBG() - profile->getTargetBG()) / profile->getCorrectionFactor();
    }
    else{
        correctionBolus = (currentBG - profile->getTargetBG()) / profile->getCorrectionFactor();
    }
    totalRequiredBolus = bolus + correctionBolus;
    finalBolus = totalRequiredBolus - profile->getInsulinOB();
}
void BolusCalculator::calculateExtended(int now, int later, double duration) {
    immediateBolus = round(now * finalBolus)/100; //rounded to 2 decimal
    extendedBolus = round(later * finalBolus)/100;

    bolusRatePerHour = extendedBolus / duration; // rate per hour for extended bolus
    // Calculate extended bolus rate (units per hour)
    //double duriation = profile->getExtendedBolusDuration();
    //this->bolusRatePerHour = ((duration >0) ? this ->extenttedBolus / duration:0;
}
