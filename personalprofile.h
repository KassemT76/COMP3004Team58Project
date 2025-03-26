#ifndef PERSONALPROFILE_H
#define PERSONALPROFILE_H
#include <QObject>

class PersonalProfile
{
public:
    PersonalProfile(QString name="default", double basalRate=0, double insulinToCarbRatio=1, double correctionFactor=1, double targetBG=0, int distributionTime=0);
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
    int getTime();
    void setTime(int);
private:
    QString name;
    double basalRate;
    double insulinToCarbRatio;
    double correctionFactor;
    double targetBG;
    int distributionTime;//in hours

};

#endif // PERSONALPROFILE_H
