#ifndef SCREENADDPROFILE_H
#define SCREENADDPROFILE_H

#include <QWidget>

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

private slots:
    void goToProfile();
};

#endif // SCREENADDPROFILE_H
