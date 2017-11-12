#include "stockchart.h"

//#include <QtCharts/QChartView>
//#include <QtNetwork>

#include <QtCore/QJsonObject>

//QT_CHARTS_USE_NAMESPACE

//Q_DECLARE_METATYPE(QAbstractSeries *)
//Q_DECLARE_METATYPE(QAbstractAxis *)

StockChart::StockChart(QObject *parent) : QObject(parent),
    m_StartDate(QDate::currentDate().addDays(-10).toString("yyyy-MM-dd")),
    m_EndDate(QDate::currentDate().toString("yyyy-MM-dd")),
    m_yAxisMin(0),
    m_yAxisMax(1500)
{
//    qRegisterMetaType<QAbstractSeries *>();
//    qRegisterMetaType<QAbstractAxis *>();
}

/**
 * @brief StockChart::startDate
 * @return
 */
QString StockChart::startDate() const {
    return m_StartDate;
}

/**
 * @brief StockChart::setStartDate
 * @param date
 */
void StockChart::setStartDate(const QString &date){
    m_StartDate = date;
}

/**
 * @brief StockChart::endDate
 * @return
 */
QString StockChart::endDate() const {
    return m_EndDate;
}

/**
 * @brief StockChart::setEndDate
 * @param date
 */
void StockChart::setEndDate(const QString &date){
    m_EndDate = date;
}

/**
 * @brief StockChart::yAxisMin
 * @return
 */
float StockChart::yAxisMin() const {
    return m_yAxisMin;
}

/**
 * @brief StockChart::setYAxisMin
 * @param value
 */
void StockChart::setYAxisMin(float value){
    m_yAxisMin = value;
}



/**
 * @brief StockChart::yAxisMax
 * @return
 */
float StockChart::yAxisMax() const {
    return m_yAxisMax;
}



/**
 * @brief StockChart::setYAxisMax
 * @param value
 */
void StockChart::setYAxisMax(float value){
    m_yAxisMin = value;
}



/**
 * @brief StockChart::setLineSeries
 * @param lineSeries
 */
void StockChart::setLineSeries(QLineSeries *lineSeries)
{
//    qDebug() << this->className << " -> " << "setLineSeries";

    QStringList timeSeriesKeys = this->timeSeries.keys();
    setStartDate(timeSeries[timeSeriesKeys[0]].toString());
    emit startDateChanged(timeSeriesKeys[0]);

    setEndDate(timeSeries[timeSeriesKeys[timeSeriesKeys.length() - 1]].toString());
    emit endDateChanged(timeSeriesKeys[timeSeriesKeys.length() - 1]);

    QDateTime xAxisValue;
    QList<float> list;

    foreach(QString date, timeSeriesKeys){
        QJsonObject timeSeriesOHLC = timeSeries[date].toObject();

        list.append(timeSeriesOHLC["4. close"].toString().toDouble());

        xAxisValue.setDate(QDate::fromString(date, "yyyy-MM-dd"));
        lineSeries->append(xAxisValue.toMSecsSinceEpoch(), timeSeriesOHLC["4. close"].toString().toDouble());
    }

//    // Find the maximum and minimum values in the list
//    qDebug() << *std::min_element(list.begin(), list.end());
//    qDebug() << *std::max_element(list.begin(), list.end());

    // Sort the list in ascending order, then, first element is min and last element is max
    std::sort(list.begin(), list.end());
    emit yAxisMinChanged(list.first() - list.first()*0.01);
    emit yAxisMaxChanged(list.last() + list.first()*0.01);
}



/**
 * @brief StockChart::getStockData
 * @param stockID
 */
void StockChart::getStockData(const QString &stockID)
{

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // Connect QNetworkAccessManager's finished signal to StockChart's replyFinished slot
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    // Send the newtork request
    QString requestUrl = "https://www.alphavantage.co/query?";
    requestUrl += "function=TIME_SERIES_DAILY";
    requestUrl += "&symbol=" + stockID;
    requestUrl += "&apikey=KFQCEU5ZSFDTIOGW";

    manager->get(QNetworkRequest(QUrl(requestUrl)));
}



///**
// * @brief addXAxis
// * @param qmlObject
// */
//void addXAxis(const QObject &qmlObject){
//    qmlObject.dumpObjectInfo();
//}



///**
// * @brief addYAxis
// * @param qmlObject
// */
//void addYAxis(const QObject &qmlObject){
//   qmlObject.dumpObjectInfo();
//}



/**
 * @brief StockChart::replyFinished
 * @param reply
 */
void StockChart::replyFinished(QNetworkReply *reply)
{
    QByteArray jsonData;
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument;
    QJsonObject jsonObject;

    if(reply->error())
    {
        qDebug() << "ERROR!!!" << reply->errorString();
    }
    else
    {
        jsonData = reply->readAll();
    }

    jsonDocument = QJsonDocument::fromJson(jsonData, &jsonParseError);
    jsonObject = jsonDocument.object();
    QJsonObject timeSeries = jsonObject.value("Time Series (Daily)").toObject();

//    QStringList timeSeriesKeys = timeSeries.keys();

//    foreach(QString date, timeSeriesKeys){
//        QJsonObject timeSeriesOHLC = timeSeries[date].toObject();
//    }

    // Set private variable (this->timeSeries)
    this->timeSeries = timeSeries;

//    emit addStockChartTimeSeries(timeSeries);
    emit timeSeriesReady();

    // Make sure to delete the network reply
    reply->deleteLater();
}

//void QChartView::mouseMoveEvent(QMouseEvent *event){
//    qDebug() << event;
//}
