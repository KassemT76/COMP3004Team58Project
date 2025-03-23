#ifndef SCREENHOME_H
#define SCREENHOME_H

#include <QWidget>

namespace Ui {
class ScreenHome;
}

class ScreenHome : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenHome(QWidget *parent = nullptr);
    ~ScreenHome();

private:
    Ui::ScreenHome *ui;

signals:
    void sendToBolus();
    void sendToProfile();

private slots:
    void goToProfile();
    void goToBolus();
};

#endif // SCREENHOME_H
