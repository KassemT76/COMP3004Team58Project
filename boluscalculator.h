#ifndef BOLUSCALCULATOR_H
#define BOLUSCALCULATOR_H


#include "personalprofile.h"
// #include "QObject"
// #include "QVector"

class BolusCalculator
{
public:
    // Constructors
    BolusCalculator();

    // Getters for the private members
    double getFoodBolus() const { return foodBolus; }
    double getCorrectionBolus() const { return correctionBolus; }
    double getTotalRequiredBolus() const { return totalRequiredBolus; }
    double getFinalBolus() const { return finalBolus; }
    double getImmediateBolus() const { return immediateBolus; }
    double getExtendedBolus() const { return extendedBolus; }
    double getBolusRatePerHour() const { return bolusRatePerHour; }

    /**
     * @brief Calculate the bolus insulin required based on the given parameters.
     * 
     * @param totalCarbs Total carbohydrates in grams.
     * @param currentBG Current blood glucose level.
     * @return A BolusData object containing the total, immediate, and extended insulin doses.
     */
    void calculateBolus(int totalCarbs, double currentBG, PersonalProfile* profile);

private:
    double foodBolus;
    double correctionBolus;
    double totalRequiredBolus;
    double finalBolus;
    double immediateBolus;
    double extendedBolus;
    double bolusRatePerHour;
};

#endif // BOLUSCALCULATOR_H
