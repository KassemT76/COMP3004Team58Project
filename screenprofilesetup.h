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
    void addProfile(QString, double, double, double, double, int, int);
    bool nameExists(QString);
private:
    Ui::ScreenProfileSetup *ui;
    QVector<QString> names;

signals:
    void sendToHome();
    void sendToAddProfile();
    void sendRemoveProfile(QString);
    void sendEditProfile(int, QString, QString);
    void sendSelectProfile(QString);
private slots:
    void goToHome();
    void goToAddProfile();
    void removeProfile();
    void editProfile();
    void selectProfile();
};

#endif // SCREENPROFILESETUP_H
