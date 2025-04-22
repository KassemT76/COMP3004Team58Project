#ifndef SCREENADDPROFILE_H
#define SCREENADDPROFILE_H

#include <QWidget>
#include <screenprofilesetup.h>
#include <QObject>

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
signals:
    void sendToProfile();
    void sendProfile(QString, double, double, double, double,int,int);

    void sendProfile(QString, double, double, double, double,int,int);
private slots:
    void gatherInfo();
    void goToProfile();
};

#endif // SCREENADDPROFILE_H
