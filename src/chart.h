#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include <QDebug>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QValueAxis>

#include <QVBoxLayout>
#include <QPen>

using namespace QtCharts;

namespace Ui {
class Chart;
}

class Chart : public QWidget
{
    Q_OBJECT

public:
    explicit Chart(QWidget *parent = nullptr);
    ~Chart();

    void addPoint(double);
    void shadeArea();
    void updateShadedArea();
private:
    Ui::Chart *ui;
    QChart* chart;
    QScatterSeries* series;
    QLineSeries* thresholdLineTop;
    QLineSeries* thresholdLineBottom;

    QValueAxis* axisX;
    QValueAxis* axisY;

    QAreaSeries *shadedArea;

    QLineSeries *leftBoundary;
    QLineSeries *rightBoundary;

    QList<QAreaSeries*> shadedAreas;


    int currentX;

    bool isShading;
};

#endif // CHART_H
