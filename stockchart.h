/*! \file stockchart.h
 * \brief StockChart class file
 */


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

QT_CHARTS_USE_NAMESPACE // Namespace for QtCharts

/*! \class StockChart
 *  \brief Class StockChart. Extends QObject
 *  \details This class acts as the back end for the QML application.
 *  \author Hansell Baran
 *  \version 1.0
 *  \date 2017-11-25
 */
class StockChart : public QObject
{
    // Macro used by the Meta-Object Compiler (moc) to handle Qt's C++ extensions and produces meta-object code for the classes. This code is required for the signals & slots mechanisms.
    Q_OBJECT

    // QML accessible (C++ exported) properties.

    // startDate is used to get/set the Chart's X axis origin/start value
    Q_PROPERTY(QString startDate READ startDate WRITE setStartDate NOTIFY startDateChanged)
    // endDate is used to get/set the Chart's X axis final/last value
    Q_PROPERTY(QString endDate READ endDate WRITE setEndDate NOTIFY endDateChanged)
    // yAxisMin is used to get/set the Chart's Y axis origin/start value
    Q_PROPERTY(double yAxisMin READ yAxisMin WRITE setYAxisMin NOTIFY yAxisMinChanged)
    // yAxisMax is used to get/set the Chart's Y axis final/end value
    Q_PROPERTY(double yAxisMax READ yAxisMax WRITE setYAxisMax NOTIFY yAxisMaxChanged)





public:
    /*!
     * \brief StockChart Class Constructor - Initializes a StockChart object
     * \param parent QObject
     */
    explicit StockChart(QObject *parent = 0);



    // Get/Read & Set/Write m_StartDate/startDate
    /*!
     * \brief startDate Returns the minimum date value for the chart's X-axis.
     * \return Returns a string with the minimum date value for the chart's X-axis.
     */
    QString startDate() const;



    /*!
     * \brief setStartDate Sets the minimum date value for the chart's X-axis.
     * \param date Value to be used as startDate
     */
    void setStartDate(const QString &date);



    // Get/Read & Set/Write m_EndDate/endDate
    /*!
     * \brief endDate Returns the maximum date value for the chart's X-axis.
     * \return Returns the maximum date value for the chart's X-axis.
     */
    QString endDate() const;



    /*!
     * \brief setEndDate Sets the maximum date value for the chart's X-axis.
     * \param date
     */
    void setEndDate(const QString &date);



    // Get/Read & Set/Write m_yAxisMin/yAxisMin
    /*!
     * \brief yAxisMin Returns the minimum value for the chart's Y-axis.
     * \return Returns the minimum value for the chart's Y-axis.
     */
    double yAxisMin() const;



    /*!
     * \brief setYAxisMin Sets the minimum value for the chart's Y-axis.
     * \param value
     */
    void setYAxisMin(double value);



    // Get/Read & Set/Write m_yAxisMax/yAxisMax
    /*!
     * \brief yAxisMax Returns the maximum value for the chart's Y-axis.
     * \return Returns the maximum value for the chart's Y-axis.
     */
    double yAxisMax() const;



    /*!
     * \brief setYAxisMax Sets the maximum value for the chart's Y-axis.
     */
    void setYAxisMax(double value);



    /*!
     * \brief setLineSeries Creates the data to be shown in the chart. This data corresponds to one line plot or line series in the chart. This function can be called from a QML file since it is marked as Q_INVOKABLE.
     * \param lineSeries - Pointer to a QLineSeries object that belongs to the QML chart (ChartView) and needs to be filled with valid data in order to be displayed as a line plot in the chart
     */
    Q_INVOKABLE void setLineSeries(QLineSeries *lineSeries);

    /*!
     * \brief getStockData Sends/issues a network request to fetch the data for a particular financial instrument / security / stock from the internet <https://www.alphavantage.co/>. The data fetched is a time series <https://en.wikipedia.org/wiki/Time_series>. This function can be called from a QML file since it is marked as Q_INVOKABLE.
     * \param stockID String with the Ticker Symbol or ID assigned to a particular security / stock that is to be fetched from the internet
     */
    Q_INVOKABLE void getStockData(const QString &stockID);





public slots:
    // Used to catch QNetworkAccessManager's reply
    /*!
     * \brief replyFinished Processes the network request issued by <getStockData> when the requested data is available. This function is a Qt public SLOT
     * \param reply Pointer to a QNetworkReply object that contains the requested network data
     */
    void replyFinished(QNetworkReply *reply);





signals:
    /*!
     * \brief timeSeriesReady Qt SIGNAL used to indicate that the time series data is ready to be added to the chart
     * \param stockID
     */
    void timeSeriesReady(QString stockID);



    /*!
     * \brief startDateChanged Qt SIGNAL used to indicate that the X-axis minimum value has changed
     * \param date Value to which m_StartDate & startDate were changed
     */
    void startDateChanged(const QString &date);



    /*!
     * \brief endDateChanged Qt SIGNAL used to indicate that the X-axis maximum value has changed
     * \param date Value to which m_EndDate & endDate were changed
     */
    void endDateChanged(const QString &date);



    /*!
     * \brief yAxisMinChanged Qt SIGNAL used to indicate that the Y-axis minimum value has changed
     * \param value Value to which m_YAxisMin & yAxisMin were changed
     */
    void yAxisMinChanged(double value);



    /*!
     * \brief yAxisMaxChanged Qt SIGNAL used to indicate that the Y-axis maximum value has changed
     * \param value Value to which m_YAxisMax& yAxisMax were changed
     */
    void yAxisMaxChanged(double value);





private:
    //! Chart's X & Y axis Min & Max values

    QString m_StartDate; /*!< Minimum value of the chart's X-axis */
    QString m_EndDate; /*!< Maximum value of the chart's X-axis */
    //! Minimum value of the chart's Y-axis
    double m_yAxisMin;
    //! Maximum value of the chart's Y-axis
    double m_yAxisMax;

    QJsonObject timeSeries; /*!< Holds the processed time series data fetched from a network request */

};

#endif // STOCKCHART_H
