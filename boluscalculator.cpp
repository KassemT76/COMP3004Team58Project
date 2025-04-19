#include "boluscalculator.h"

BolusCalculator::BolusCalculator() : bolus(0), correctionBolus(0), totalRequiredBolus(0), finalBolus(0), immediateBolus(0), extendedBolus(0), bolusRatePerHour(0), endTime(0) {}

void BolusCalculator::calculateBolus(double totalCarbs, double currentBG, PersonalProfile* profile, double iobOnBoard) {
    profile->setInsulinOB(iobOnBoard);
    bolus = totalCarbs / profile->getCarbRatio();
    if(currentBG <= 0){//if no BG was selected in bolus screen
        correctionBolus = profile->getTargetBG() / profile->getCorrectionFactor();
    }
    else{
        correctionBolus = (currentBG - profile->getTargetBG()) / profile->getCorrectionFactor();
    }
    totalRequiredBolus = bolus + correctionBolus;
    finalBolus = totalRequiredBolus - profile->getInsulinOB();
}
void BolusCalculator::calculateExtended(int now, int later, int durHr, int durMin, int currTime) {
    immediateBolus = round(now * finalBolus)/100; //round all values to 2 decimal
    extendedBolus = round(later * finalBolus)/100;
    double duration = durHr + durMin/60;
    endTime = currTime + durHr*60 + durMin;
    bolusRatePerHour = round(100*(extendedBolus / duration))/100;
}
