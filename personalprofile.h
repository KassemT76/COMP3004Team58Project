#ifndef PERSONALPROFILE_H
#define PERSONALPROFILE_H
#include <QObject>
#include <QTableWidgetItem>

class PersonalProfile
{
public:
    PersonalProfile(QString name="default", double basalRate=0, double insulinToCarbRatio=1, double correctionFactor=1, double targetBG=0, int startTime=0, int endTime=0);
    QString getName();
    void setName(QString);
    double getBasalRate();
    void setBasalRate(double);
    double getCarbRatio();
    void setCarbRatio(double);
    double getCorrectionFactor();
    void setCorrectionFactor(double);
    double getTargetBG();
    void setTargetBG(double);
    int getStartTime();
    void setStartTime(int);
    int getEndTime();
    void setEndTime(int);
    double getInsulinOB();
    void setInsulinOB(double insulinOB);

    QString getDisplayTime(int);//in the form of XX:XX (24 hr)
private:
    QString name;
    double basalRate;
    double insulinToCarbRatio;
    double correctionFactor;
    double targetBG; // target blood glucose level
    int startTime;//in hours
    int endTime;
    /**
     * TODO: this should get updated 
     */
    double insulinOB; // insulin on board
    //all of these are for the QTable in screenprofilesetup
};

#endif // PERSONALPROFILE_H
