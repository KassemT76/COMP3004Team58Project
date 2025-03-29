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
    void addProfile(PersonalProfile&);
    void removeProfile(QString);
    PersonalProfile& getProfile(QString);
    //profile manager:
    QVector<PersonalProfile> profiles;
    QString activeProfileName;
private:
    Ui::ScreenProfileSetup *ui;

signals:
    void sendToHome();
    void sendToAddProfile();

private slots:
    void goToHome();
    void goToAddProfile();

};

#endif // SCREENPROFILESETUP_H
