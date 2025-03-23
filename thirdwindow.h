#ifndef THIRDWINDOW_H
#define THIRDWINDOW_H

#include <QWidget>

namespace Ui {
class ThirdWindow;
}

class ThirdWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ThirdWindow(QWidget *parent = nullptr);
    ~ThirdWindow();

private:
    Ui::ThirdWindow *ui;
};

#endif // THIRDWINDOW_H
