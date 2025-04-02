#ifndef BOLUSCALCULATOR_H
#define BOLUSCALCULATOR_H
#include "personalprofile.h"
#include "QObject"
#include "QVector"
class BolusCalculator
{
public:
    BolusCalculator();
    QVector<double> calculateBolus(int, double, double, double);
    QVector<double> getCharData();
private:
    PersonalProfile profile;
};

#endif // BOLUSCALCULATOR_H
