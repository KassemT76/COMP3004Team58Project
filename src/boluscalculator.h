#ifndef BOLUSCALCULATOR_H
#define BOLUSCALCULATOR_H

/**
 * @file boluscalculator.h
 * @brief This file contains the BolusCalculator class which is used to calculate the insulin bolus required for a given amount of carbohydrates and current blood glucose level.
 * @details The BolusCalculator class contains methods to calculate the food bolus, correction bolus, total required bolus, final bolus, immediate bolus, extended bolus, and the bolus rate per hour.
 * @author Ariz Kazani and Hollen Lo
 */

#include "personalprofile.h"
#include <cmath>

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
     * @param profile Pointer to the PersonalProfile object containing user-specific information.
     * @param iobOnBoard Insulin on board (IOB) in units.
     * @return A BolusData object containing the total, immediate, and extended insulin doses.
     */
    void calculateBolus(double, double, PersonalProfile*, double);

    /**
     * @brief Calculate the immediate and extended bolus insulin required based on the given parameters.
     * 
     * @param now The percentage of the bolus to be given immediately.
     * @param later The percentage of the bolus to be given later.
     * @param durHr Duration of the extended bolus in hours.
     * @param durMin Duration of the extended bolus in minutes.
     * @param currTime Current time in minutes.
     * 
     * @return The correction bolus in units.
     */
    void calculateExtended(int, int, int, int, int);

private:
    double bolus;              // Food bolus (carb bolus)
    double correctionBolus;    // Correction bolus
    double totalRequiredBolus; // Total required bolus
    double finalBolus;         // Final bolus after considering insulin on board
    double immediateBolus;     // Immediate bolus (to be given right away)
    double extendedBolus;      // Extended bolus (to be given over time)
    double bolusRatePerHour;   // Bolus rate per hour (for extended bolus)
    int endTime;               // End time for the extended bolus (in minutes)
};

#endif // BOLUSCALCULATOR_H
