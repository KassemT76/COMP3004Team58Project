#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "screenhome.h"
#include "screenbolus.h"
#include "screenprofilesetup.h"
#include "screenlock.h"
#include "screenaddprofile.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    ScreenHome* screenHome = nullptr;
    ScreenBolus* screenBolus = nullptr;
    ScreenLock* screenLock = nullptr;
    ScreenProfileSetup* screenProfileSetup = nullptr;
    ScreenAddProfile* screenAddProfile = nullptr;

private:

    Ui::MainWindow *ui;

private slots:
    void goToHome();
    void goToLock();
    void goToBolus();
    void goToProfile();
    void goToAddProfile();
};

#endif // MAINWINDOW_H
