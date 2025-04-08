#include "chart.h"
#include "ui_chart.h"

chart::chart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chart)
{
    ui->setupUi(this);
    //Create the Axis
    QValueAxis* axisX = new QValueAxis();
    QValueAxis* axisY = new QValueAxis();

    axisX->setRange(0, 5);
    axisX->setLabelFormat("%d");

    axisY->setRange(2, 18); // adjust based on your glucose values

    QFont axisFont;
    axisFont.setPointSize(8); // or any size you want

    axisX->setLabelsFont(axisFont);
    axisY->setLabelsFont(axisFont);

    axisX->setVisible(false);

    //Create the Scatter Series
    QScatterSeries *series = new QScatterSeries();
    series->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    series->setMarkerSize(8); // optional: adjust size

    series->append(1, 4);
    series->append(2, 8);
    series->append(3, 3);
    series->append(4, 7);



    //Create the chart and add the series + axis
    QChart *chart = new QChart();

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignRight);

    //Threshold lines
    QLineSeries* thresholdLineTop = new QLineSeries();
    thresholdLineTop->append(0, 10);        // start of line
    thresholdLineTop->append(5, 10);     // end of line (adjust maxX to fit your range)

    QLineSeries* thresholdLineBottom = new QLineSeries();
    thresholdLineBottom->append(0, 3.9);        // start of line
    thresholdLineBottom->append(5, 3.9);     // end of line (adjust maxX to fit your range)

    QPen pen(Qt::SolidLine);
    pen.setWidth(3);
    pen.setColor(Qt::yellow);
    thresholdLineTop->setPen(pen);
    pen.setColor(Qt::red);
    thresholdLineBottom->setPen(pen);

    chart->addSeries(thresholdLineTop);
    thresholdLineTop->attachAxis(axisX);
    thresholdLineTop->attachAxis(axisY);

    chart->addSeries(thresholdLineBottom);
    thresholdLineBottom->attachAxis(axisX);
    thresholdLineBottom->attachAxis(axisY);

    //Add the scatter Series
    chart->addSeries(series);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    //Hides the legend
    chart->legend()->hide();

    //Put the chart in a chart view
    QChartView *chartView = new QChartView(chart);

    //Use layout to show it
    QVBoxLayout *layout = new QVBoxLayout(this);
    //remove padding
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(chartView);
    setLayout(layout);
}

chart::~chart()
{
    delete ui;
}
