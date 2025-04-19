#ifndef BOLUSCALCULATOR_H
#define BOLUSCALCULATOR_H


#include "personalprofile.h"
#include <cmath>
// #include "QObject"
// #include "QVector"

class BolusCalculator
{
public:
    /**
     * @brief Constructor for the BolusCalculator class.
     * 
     * Initializes the bolus calculator with default values.
     */
    BolusCalculator();

    /**
     * @brief This method retrieves the food bolus (carb bolus)
     *
     * @return The food bolus in units.
     */
    double getBolus() const { return bolus; }

    /**
     * @brief This method retrieves the correction bolus
     * 
     * @return The correction bolus in units.
     */
    double getCorrectionBolus() const { return correctionBolus; }

    /**
     * @brief This method retrieves the total required bolus
     * 
     * @return The total required bolus in units.
     */
    double getTotalRequiredBolus() const { return totalRequiredBolus; }

    /**
     * @brief This method retrieves the final bolus
     * 
     * @return The final bolus in units.
     */
    double getFinalBolus() const { return finalBolus; }

    /**
     * @brief This method retrieves the immediate bolus, the bolus that should be given right away
     * 
     * @return The immediate bolus in units.
     */
    double getImmediateBolus() const { return immediateBolus; }

    /**
     * @brief This method retrieves the extended bolus, the bolus that should be given over time
     * 
     * @return The extended bolus in units.
     */
    double getExtendedBolus() const { return extendedBolus; }

    /**
     * @brief This method retrieves the bolus rate per hour, the rate at which the extended bolus should be given
     * 
     * @return The bolus rate per hour in units.
     */
    double getBolusRatePerHour() const { return bolusRatePerHour; }
    /**
     * @brief This method retrieves the end time, the time at which the extended bolus would end
     *
     * @return The end time in minutes.
     */
    int getEndTime() const { return endTime; }

    /**
     * @brief Calculate the bolus insulin required based on the given parameters.
     * 
     * @param totalCarbs Total carbohydrates in grams.
     * @param currentBG Current blood glucose level.
     * @return A BolusData object containing the total, immediate, and extended insulin doses.
     */
    void calculateBolus(double, double, PersonalProfile*, double);
    void calculateExtended(int, int, int, int, int);

private:
    double bolus;
    double correctionBolus;
    double totalRequiredBolus;
    double finalBolus;
    double immediateBolus;
    double extendedBolus;
    double bolusRatePerHour;
    int endTime;
};

#endif // BOLUSCALCULATOR_H
