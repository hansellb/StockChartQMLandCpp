#ifndef STOCKCHART_H
#define STOCKCHART_H

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QCategoryAxis>
#include <QDateTime>
#include <QtQuick/QQuickPaintedItem>
#include <QColor>
#include <QObject>
#include <QtNetwork>
#include <QtCore>

QT_CHARTS_USE_NAMESPACE

class StockChart : public QObject
{
    Q_OBJECT

    // QML accessible (C++ exported) properties.

    // startDate is used to set the Chart's X axis origin/start value
    Q_PROPERTY(QString startDate READ startDate WRITE setStartDate NOTIFY startDateChanged)
    // endDate is used to set the Chart's X axis final/last value
    Q_PROPERTY(QString endDate READ endDate WRITE setEndDate NOTIFY endDateChanged)
    // yAxisMin is used to set the Chart's Y axis origin/start value
    Q_PROPERTY(float yAxisMin READ yAxisMin WRITE setYAxisMin NOTIFY yAxisMinChanged)
    // yAxisMax is used to set the Chart's Y axis final/end value
    Q_PROPERTY(float yAxisMax READ yAxisMax WRITE setYAxisMax NOTIFY yAxisMaxChanged)

public:
    explicit StockChart(QObject *parent = 0);

    // Get/Read & Set/Write m_StartDate/startDate
    QString startDate() const;
    void setStartDate(const QString &);

    // Get/Read & Set/Write m_EndDate/endDate
    QString endDate() const;
    void setEndDate(const QString &);

    // Get/Read & Set/Write m_yAxisMin/yAxisMin
    float yAxisMin() const;
    void setYAxisMin(float);

    // Get/Read & Set/Write m_yAxisMax/yAxisMax
    float yAxisMax() const;
    void setYAxisMax(float);


    Q_INVOKABLE void setLineSeries(QLineSeries *lineSeries);

    // Sends a request to retrieve
    Q_INVOKABLE void getStockData(const QString &stockID);

public slots:
    // Used to catch QNetworkAccessManager's reply
    void replyFinished(QNetworkReply *reply);

signals:
    void timeSeriesReady(QString stockID);
    void startDateChanged(const QString &date);
    void endDateChanged(const QString &date);
    void yAxisMinChanged(float value);
    void yAxisMaxChanged(float value);

private:
    // Chart's X & Y axis Min & Max values
    QString m_StartDate;
    QString m_EndDate;
    double m_yAxisMin;
    double m_yAxisMax;

    QJsonObject timeSeries;

};

#endif // STOCKCHART_H
