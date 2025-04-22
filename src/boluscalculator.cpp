#include "boluscalculator.h"

/**
 * @file boluscalculator.cpp
 * @brief This file contains the implementation of the BolusCalculator class which is used to calculate the insulin bolus required for a given amount of carbohydrates and current blood glucose level.
 * @details The BolusCalculator class contains methods to calculate the food bolus, correction bolus, total required bolus, final bolus, immediate bolus, extended bolus, and the bolus rate per hour.
 * @author Ariz Kazani and Hollen Lo
 */

BolusCalculator::BolusCalculator() : bolus(0), correctionBolus(0), totalRequiredBolus(0), finalBolus(0), immediateBolus(0), extendedBolus(0), bolusRatePerHour(0), endTime(0) {}

void BolusCalculator::calculateBolus(double totalCarbs, double currentBG, PersonalProfile* profile, double iobOnBoard) {
    profile->setInsulinOB(iobOnBoard);
    bolus = totalCarbs / profile->getCarbRatio();
    correctionBolus = (currentBG - profile->getTargetBG()) / profile->getCorrectionFactor();
    totalRequiredBolus = bolus + correctionBolus;
    finalBolus = std::max(totalRequiredBolus - profile->getInsulinOB(), 0.0);
}

void BolusCalculator::calculateExtended(int now, int later, int durHr, int durMin, int currTime) {
    immediateBolus = round(now * finalBolus)/100; //round all values to 2 decimal
    extendedBolus = round(later * finalBolus)/100;
    double duration = durHr + durMin/60; // ! this line looks off maybe need to be changed?
    endTime = currTime + durHr*60 + durMin;
    bolusRatePerHour = round(100*(extendedBolus / duration))/100;
}
