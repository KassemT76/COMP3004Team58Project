#ifndef INSULINPUMP_H
#define INSULINPUMP_H


class InsulinPump
{
public:
    InsulinPump(int battery=100, double insulinLevel=0, double insulinOnBoard=0);
    void giveBolus(int, double);
    void startBasalDelievery();
    void stopBasalDelievery();
    void raiseError();
    int getBattery();
    void setBattery(int);
    double getInsulinLevel();
    void setgetInsulinLevel(double);
    double getInsulinOB();
    void setInsulinOB(double);
private:
    int battery;
    double insulinLevel;
    double insulinOnBoard;
};

#endif // INSULINPUMP_H
