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
    Q_PROPERTY(QString startDate READ startDate WRITE setStartDate NOTIFY startDateChanged)
    Q_PROPERTY(QString endDate READ endDate WRITE setEndDate NOTIFY endDateChanged)
    Q_PROPERTY(float yAxisMin READ yAxisMin WRITE setYAxisMin NOTIFY yAxisMinChanged)
    Q_PROPERTY(float yAxisMax READ yAxisMax WRITE setYAxisMax NOTIFY yAxisMaxChanged)

public:
    explicit StockChart(QObject *parent = 0);

    QString startDate() const;
    void setStartDate(const QString &);

    QString endDate() const;
    void setEndDate(const QString &);

    float yAxisMin() const;
    void setYAxisMin(float);

    float yAxisMax() const;
    void setYAxisMax(float);

//    Q_INVOKABLE QAbstractSeries *setLineSeries();
    Q_INVOKABLE void setLineSeries(QLineSeries *lineSeries);
    Q_INVOKABLE void getStockData();

public slots:
    void replyFinished(QNetworkReply *reply);

signals:
    void addStockChartTimeSeries(QJsonObject timeSeries);
    void startDateChanged(const QString &date);
    void endDateChanged(const QString &date);
    void yAxisMinChanged(float value);
    void yAxisMaxChanged(float value);

private:
    QString className = "StockChart";
    QString m_StartDate;
    QString m_EndDate;
    double m_yAxisMin;
    double m_yAxisMax;
    QJsonObject timeSeries;

};

#endif // STOCKCHART_H
