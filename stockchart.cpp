#include "stockchart.h"

#include <QtCore/QJsonObject>



StockChart::StockChart(QObject *parent) : QObject(parent),
    m_StartDate(QDate::currentDate().addDays(-10).toString("yyyy-MM-dd")),
    m_EndDate(QDate::currentDate().toString("yyyy-MM-dd")),
    m_yAxisMin(0),
    m_yAxisMax(1500)
{
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
    // Get the keys (dates) from the time series
    QStringList timeSeriesKeys = this->timeSeries.keys();

    setStartDate(timeSeries[timeSeriesKeys[0]].toString());
    emit startDateChanged(timeSeriesKeys[0]);

    setEndDate(timeSeries[timeSeriesKeys[timeSeriesKeys.length() - 1]].toString());

    emit endDateChanged(timeSeriesKeys[timeSeriesKeys.length() - 1]);

    // Stores temporarily the date of the current element in the time series
    QDateTime xAxisValue;

    // Holds ALL close price values
    QList<float> list;

    // Add data (stock's close price) to the ChartView's line series
    foreach(QString date, timeSeriesKeys){
        QJsonObject timeSeriesOHLC = timeSeries[date].toObject();

        // Add price value to the list
        list.append(timeSeriesOHLC["4. close"].toString().toDouble());

        xAxisValue.setDate(QDate::fromString(date, "yyyy-MM-dd"));

        // Add the point (x is a date, y is a value) to the line series
        lineSeries->append(xAxisValue.toMSecsSinceEpoch(), timeSeriesOHLC["4. close"].toString().toDouble());
    }

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

    // Set & send the newtork request
    QString requestUrl = "https://www.alphavantage.co/query?";
    requestUrl += "function=TIME_SERIES_DAILY";
    requestUrl += "&symbol=" + stockID;
    requestUrl += "&apikey=KFQCEU5ZSFDTIOGW";

    manager->get(QNetworkRequest(QUrl(requestUrl)));
}



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

    // Get the stockID from the request url
    QString stockID = (reply->url().toString()).replace("https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=", "").replace("&apikey=KFQCEU5ZSFDTIOGW","");

    // Check if there were any errors
    if(reply->error())
    {
        qDebug() << "ERROR!!!" << reply->errorString();
    }
    else
    {
        jsonData = reply->readAll();

        // Store requested data in a file
        QFile *file = new QFile(QDir::currentPath() + "\\" + stockID + ".txt");
        if(file->open(QFile::Append))
        {
            file->write(jsonData);
            file->flush();
            file->close();
        }
        delete file;
    }

    jsonDocument = QJsonDocument::fromJson(jsonData, &jsonParseError);
    jsonObject = jsonDocument.object();
    QJsonObject timeSeries = jsonObject.value("Time Series (Daily)").toObject();

    // Set private variable (this->timeSeries)
    this->timeSeries = timeSeries;

    emit timeSeriesReady(stockID);

    // Make sure to delete the network reply
    reply->deleteLater();
}
