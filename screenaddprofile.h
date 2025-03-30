#ifndef SCREENADDPROFILE_H
#define SCREENADDPROFILE_H

#include <QWidget>
#include <screenprofilesetup.h>

namespace Ui {
class ScreenAddProfile;
}

class ScreenAddProfile : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenAddProfile(QWidget *parent = nullptr);
    ~ScreenAddProfile();

private:
    Ui::ScreenAddProfile *ui;
    ScreenProfileSetup profileSetup;
signals:
    void sendToProfile();

private slots:
    void goToProfile();
    void gatherInfo();
};

#endif // SCREENADDPROFILE_H
