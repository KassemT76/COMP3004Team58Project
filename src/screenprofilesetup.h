#ifndef SCREENPROFILESETUP_H
#define SCREENPROFILESETUP_H

/**
 * @file screenprofilesetup.h
 * @brief This file contains the ScreenProfileSetup class which is used to create the profile setup screen of the insulin pump application.
 * @details The ScreenProfileSetup class is a QWidget that displays the profile setup screen for the insulin pump application.
 * It provides buttons to navigate to the settings and add profile screens, and to remove or edit existing profiles.
 * 
 * @author Hollen Lo
 */

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
    void addProfile(QString, double, double, double, double, int, int);
    bool nameExists(QString);
    void updateActiveProfile(PersonalProfile*);
private:
    Ui::ScreenProfileSetup *ui;
    QVector<QString> names;

signals:
    void sendToSettings();
    void sendToAddProfile();
    void sendRemoveProfile(QString);
    void sendEditProfile(int, QString, QString);
    void sendSelectProfile(QString);
private slots:
    void goToSettings();
    void goToAddProfile();
    void removeProfile();
    void editProfile();
    void selectProfile();
};

#endif // SCREENPROFILESETUP_H
