#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QWidget>

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();

signals:
    void profileSaved();

private:
    Ui::SecondWindow *ui;

private slots:
    void onSaveClicked();

};


#endif // SECONDWINDOW_H
