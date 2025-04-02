#ifndef SCREENPROFILESETUP_H
#define SCREENPROFILESETUP_H

#include <QWidget>
#include <QVector>
#include <personalprofile.h>
#include <QTableWidgetItem>
#include <QVBoxLayout>
namespace Ui {
class ScreenProfileSetup;
}

class ScreenProfileSetup : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenProfileSetup(QWidget *parent = nullptr);
    ~ScreenProfileSetup();
    void removeProfile();
    void editProfile();
    void selectProfile();
    PersonalProfile& getProfile(QString);
    void addProfile(QString, double, double, double, double, int, int);

private:
    Ui::ScreenProfileSetup *ui;
    QVector<QTableWidgetItem*> cells;
    //profile manager:
    QVector<PersonalProfile> profiles;
    PersonalProfile activeProfile;
    QVBoxLayout *profileLayout;

signals:
    void sendToHome();
    void sendToAddProfile();
private slots:
    void goToHome();
    void goToAddProfile();
};

#endif // SCREENPROFILESETUP_H
