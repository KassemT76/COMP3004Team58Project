#ifndef INSULINPUMP_H
#define INSULINPUMP_H

#include "error.h"

class InsulinPump
{
public:
    InsulinPump(int battery=100, double insulinLevel=0, double insulinOnBoard=0);
    ~InsulinPump();

    Error giveBolus(int, double); // return true if successful
    void startBasalDelievery();
    void stopBasalDelievery();
    // void raiseError();

    // getters
    int getBattery();
    double getInsulinLevel();
    double getInsulinOB();

    // setters
    void setBattery(int);
    void setInsulinLevel(double);
    void setInsulinOB(double);


private:
    int battery;
    double insulinLevel;
    double insulinOnBoard;
};

#endif // INSULINPUMP_H
