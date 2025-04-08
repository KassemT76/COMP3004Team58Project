#include "chart.h"
#include "ui_chart.h"

#define MAX_LENGTH 15
#define MIN_GLUCOSE 2
#define MAX_GLUCOSE 18

#define LOWER_THRESHOLD 3.9
#define UPPER_THRESHOLD 10

Chart::Chart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chart)
{
    ui->setupUi(this);

    currentX = 0;
    isShading = false;
    //Create the Axes
    axisX = new QValueAxis();
    axisY = new QValueAxis();

    //This is base
    axisX->setRange(0, 15);
    axisX->setLabelFormat("%d");

    //This stays constant cuz you know youll die if its not in between these values
    axisY->setRange(MIN_GLUCOSE, MAX_GLUCOSE);

    QFont axisFont;
    axisFont.setPointSize(8); // or any size you want

    axisX->setLabelsFont(axisFont);
    axisY->setLabelsFont(axisFont);

    axisX->setVisible(false);

    //Create the chart
    chart = new QChart();

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignRight);

    //Threshold lines
    thresholdLineTop = new QLineSeries();
    thresholdLineTop->append(0, UPPER_THRESHOLD); //start
    thresholdLineTop->append(MAX_LENGTH, UPPER_THRESHOLD); //end

    thresholdLineBottom = new QLineSeries();
    thresholdLineBottom->append(0, LOWER_THRESHOLD); //start
    thresholdLineBottom->append(MAX_LENGTH, LOWER_THRESHOLD); //end

    //Add the threshold lines to chart and attach axes
    chart->addSeries(thresholdLineTop);
    thresholdLineTop->attachAxis(axisX);
    thresholdLineTop->attachAxis(axisY);

    chart->addSeries(thresholdLineBottom);
    thresholdLineBottom->attachAxis(axisX);
    thresholdLineBottom->attachAxis(axisY);

    //Create the Scatter Series
    series = new QScatterSeries();
    series->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    series->setMarkerSize(8); // optional: adjust size

    //Add the scatter Series to the chart and attach axes
    chart->addSeries(series);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    //Hides the legend
    chart->legend()->hide();

    //Set colors
    QPen pen(Qt::SolidLine);
    pen.setWidth(3);

    pen.setColor(QColor(252, 206, 3));
    thresholdLineTop->setPen(pen);

    pen.setColor(Qt::red);
    thresholdLineBottom->setPen(pen);

    //Put the chart in a chart view
    QChartView *chartView = new QChartView(chart);

    //Use layout to show it
    QVBoxLayout *layout = new QVBoxLayout(this);

    //remove padding
    layout->setContentsMargins(0, 0, 0, 0);

    //Add the widgets
    layout->addWidget(chartView);
    setLayout(layout);
}

Chart::~Chart()
{
    delete ui;
}

void Chart::addPoint(double glucose) {
    qInfo() << glucose;
    series->append(currentX, glucose);

    // Threshold lines
    if (currentX % 15 == 0 && currentX != 0) {
        thresholdLineTop->append(currentX, UPPER_THRESHOLD);
        thresholdLineTop->append(currentX + MAX_LENGTH, UPPER_THRESHOLD);
        thresholdLineBottom->append(currentX, LOWER_THRESHOLD);
        thresholdLineBottom->append(currentX + MAX_LENGTH, LOWER_THRESHOLD);
    }

    // Sliding window
    if (series->count() == MAX_LENGTH) {
        series->remove(0);
        axisX->setRange(currentX - MAX_LENGTH + 1, currentX);
    }

    // Live shaded region (dynamic right boundary)
    if (isShading) {
        if (shadedArea) {
            chart->removeSeries(shadedArea);
            delete shadedArea;
        }

        QLineSeries* rightBoundary = new QLineSeries();
        rightBoundary->append(currentX, MIN_GLUCOSE);
        rightBoundary->append(currentX, MAX_GLUCOSE);

        shadedArea = new QAreaSeries(leftBoundary, rightBoundary);
        shadedArea->setPen(Qt::NoPen);
        shadedArea->setBrush(QBrush(QColor(255, 0, 0, 50)));

        chart->addSeries(shadedArea);
        shadedArea->attachAxis(axisX);
        shadedArea->attachAxis(axisY);
    }

    currentX++;
}

void Chart::shadeArea() {
    if (isShading) {
        qInfo() << "Stop shading";
        // Finalize the live shaded area
        if (shadedArea) {
            chart->removeSeries(shadedArea);
            delete shadedArea;
            shadedArea = nullptr;
        }

        // Create right boundary at currentX
        QLineSeries* rightBoundary = new QLineSeries();
        rightBoundary->append(currentX, MIN_GLUCOSE);
        rightBoundary->append(currentX, MAX_GLUCOSE);

        // Create final area
        QAreaSeries* permanentShadedArea = new QAreaSeries(leftBoundary, rightBoundary);
        permanentShadedArea->setPen(Qt::NoPen);
        permanentShadedArea->setBrush(QBrush(QColor(255, 0, 0, 50)));

        chart->addSeries(permanentShadedArea);
        permanentShadedArea->attachAxis(axisX);
        permanentShadedArea->attachAxis(axisY);

        // Do NOT delete leftBoundary — it's part of the permanent area now
        leftBoundary = nullptr;
        isShading = false;
    } else {
        // Begin a new shaded region
        qInfo() << "Start shading";
        leftBoundary = new QLineSeries();
        leftBoundary->append(currentX, MIN_GLUCOSE);
        leftBoundary->append(currentX, MAX_GLUCOSE);

        // Preload shadedArea to prevent freeing dangling pointer
        shadedArea = nullptr;
        isShading = true;
    }
}

