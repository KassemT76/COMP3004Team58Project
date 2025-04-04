#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QChart>
#include <QVBoxLayout>
#include <QValueAxis>
#include <QLineSeries>


using namespace QtCharts;

namespace Ui {
class chart;
}

class chart : public QWidget
{
    Q_OBJECT

public:
    explicit chart(QWidget *parent = nullptr);
    ~chart();

private:
    Ui::chart *ui;
};

#endif // CHART_H
