#include "boluscalculator.h"

BolusCalculator::BolusCalculator(PersonalProfile* profile) : profile(profile), foodBolus(0), correctionBolus(0), totalRequiredBolus(0), finalBolus(0), immediateBolus(0), extendedBolus(0), bolusRatePerHour(0) {}
BolusCalculator::BolusCalculator(PersonalProfile* profile, int totalCarbs, double currentBG) : profile(profile), foodBolus(0), correctionBolus(0), totalRequiredBolus(0), finalBolus(0), immediateBolus(0), extendedBolus(0), bolusRatePerHour(0) {
    calculateBolus(totalCarbs, currentBG);
}

void BolusCalculator::calculateBolus(int totalCarbs, double currentBG){
    this.foodBolus = totalCarbs / profile->getCarbRatio();
    this.correctionBolus = (currentBG - profile->getTargetBG()) / profile->getCorrectionFactor();
    this.totalRequiredBolus = this.foodBolus + this.correctionBolus;
    this.finalBolus = this.totalRequiredBolus - profile->getInsulinOB();
    
    // TODO: the percentages should be retrieved from the profile
    // For now, we will use hardcoded values
    this.immediateBolus = 0.6 * this.finalBolus; // 60% immediate bolus
    this.extendedBolus = 0.4 * this.finalBolus; // 40% extended bolus

    // TODO: the "3" should be replaced with the bolus duration from the profile when added
    this.bolusRatePerHour = this.extendedBolus / 3; // rate per hour for extended bolus
}
