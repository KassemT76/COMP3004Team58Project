#ifndef SCREENPROFILESETUP_H
#define SCREENPROFILESETUP_H

#include <QWidget>
#include <QVector>
#include <personalprofile.h>

namespace Ui {
class ScreenProfileSetup;
}

class ScreenProfileSetup : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenProfileSetup(QWidget *parent = nullptr);
    ~ScreenProfileSetup();
    void addProfile(QString, double, double, double, double, int, int);
    void removeProfile(QString);
    PersonalProfile& getProfile(QString);

private:
    Ui::ScreenProfileSetup *ui;
    //profile manager:
    QVector<PersonalProfile> profiles;
    PersonalProfile activeProfile;
signals:
    void sendToHome();
    void sendToAddProfile();

private slots:
    void goToHome();
    void goToAddProfile();

};

#endif // SCREENPROFILESETUP_H
