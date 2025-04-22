#ifndef CHART_H
#define CHART_H

/**
 * @file chart.h
 * @brief This file contains the Chart class which is used to create a chart for displaying glucose levels over time.
 * @details The Chart class uses Qt Charts to create a line chart with shaded areas for glucose levels above and below certain thresholds.
 * @author Kassem Taha
 */

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
    /**
     * @brief Constructor for the Chart class.
     * @param parent The parent widget.
     */
    explicit Chart(QWidget *parent = nullptr);
    ~Chart();

    /**
     * @brief Adds a new point to the chart with the given glucose value.
     * @param glucose The glucose value to add.
     */
    void addPoint(double);

    /**
     * @brief Sets the shading state of the chart.
     * @details Call the function once to enable shading and again to disable it.
     */
    void shadeArea();
private:


    Ui::Chart *ui;                     // Pointer to the UI
    QChart* chart;                     // Pointer to the chart
    QScatterSeries* series;            // Pointer to the scatter series
    QLineSeries* thresholdLineTop;     // Pointer to the top threshold line
    QLineSeries* thresholdLineBottom;  // Pointer to the bottom threshold line

    QValueAxis* axisX;                 // Pointer to the X axis
    QValueAxis* axisY;                 // Pointer to the Y axis

    QAreaSeries *shadedArea;           // Pointer to the shaded area

    QLineSeries *leftBoundary;         // Pointer to the left boundary line
    QLineSeries *rightBoundary;        // Pointer to the right boundary line

    QList<QAreaSeries*> shadedAreas;   // List of shaded areas


    int currentX;                      // Current X position

    bool isShading;                    // Flag to indicate if shading is enabled
};

#endif // CHART_H
