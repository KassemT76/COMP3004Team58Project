#include "boluscalculator.h"

BolusCalculator::BolusCalculator()
{

}
QVector<double> BolusCalculator::calculateBolus(int totalCarbs, double currentBG, double insulinOB, double immediateBolusFraction){
    /*
    rough format for calculating bolus:
    units from profile:
    insulinToCarbRatio;
    correctionFactor;
    targetBG;
    distributionTime;
     */
    QVector<double> allValues;
    //for total insulin adminstered:
    double carbBolus = totalCarbs/profile.getCarbRatio();
    double correctionBolus = (currentBG - profile.getTargetBG())/profile.getCorrectionFactor();
    double totalBolusRequired = carbBolus + correctionBolus;
    double finalBolus = totalBolusRequired - insulinOB;
    allValues.append(finalBolus);
    //immediate insulin dose:
    double immediateBolus = immediateBolusFraction * finalBolus;
    allValues.append(immediateBolus);
    //extended insulin delivery:
    double extendedBolus = ((1-immediateBolusFraction) * finalBolus)/profile.getTime();
    //might need to round to 2 decimals
    allValues.append(extendedBolus);
    return allValues;
}
QVector<double> BolusCalculator::getCharData(){
    QVector<double> charData;

    return charData;
}
