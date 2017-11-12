////https://stackoverflow.com/questions/38467769/add-c-qabstractseries-to-qml-chartview
#include "stockchart.h"

#include <QtCharts/QChartView>
#include <QtNetwork>

#include <QtCore/QJsonObject>

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)

StockChart::StockChart(QObject *parent) : QObject(parent), m_StartDate("2017-11-06"), m_EndDate("2017-11-07")
{
    qRegisterMetaType<QAbstractSeries *>();
    qRegisterMetaType<QAbstractAxis *>();
}

QString StockChart::startDate() const {
    return m_StartDate;
}

void StockChart::setStartDate(const QString &date){
    m_StartDate = date;
}

QString StockChart::endDate() const {
    return m_EndDate;
}

void StockChart::setEndDate(const QString &date){
    m_EndDate = date;
}

float StockChart::yAxisMin() const {
    return m_yAxisMin;
}

void StockChart::setYAxisMin(float value){
    m_yAxisMin = value;
}

float StockChart::yAxisMax() const {
    return m_yAxisMax;
}

void StockChart::setYAxisMax(float value){
    m_yAxisMin = value;
}

//QAbstractSeries *StockChart::setLineSeries()
void StockChart::setLineSeries(QLineSeries *lineSeries)
{
    qDebug() << this->className << " -> " << "setLineSeries";

//    QLineSeries *lineSeries = new QLineSeries();

//    QPen penLineSeries;
//    penLineSeries.setColor(QColor(34,102,102));
//    penLineSeries.setWidth(5);

    QStringList timeSeriesKeys = this->timeSeries.keys();
    setStartDate(timeSeries[timeSeriesKeys[0]].toString());
    emit startDateChanged(timeSeriesKeys[0]);
//    qDebug() << timeSeriesKeys[timeSeriesKeys.length() - 1];
    setEndDate(timeSeries[timeSeriesKeys[timeSeriesKeys.length() - 1]].toString());
    emit endDateChanged(timeSeriesKeys[timeSeriesKeys.length() - 1]);

    QDateTime xAxisValue;
//    QPointF pointF;
    QList<float> list;

    foreach(QString date, timeSeriesKeys){
        QJsonObject timeSeriesOHLC = timeSeries[date].toObject();
//        qDebug() << date << timeSeriesOHLC.value("1. open").toString() << timeSeriesOHLC["4. close"].toString();
//        qDebug() << QDateTime::fromString(date, "yyyy-MM-dd").toString();
        list.append(timeSeriesOHLC["4. close"].toString().toDouble());
//        qDebug() << QDate::fromString(date, "yyyy-MM-dd").toString() << timeSeriesOHLC["4. close"].toString().toDouble();
        xAxisValue.setDate(QDate::fromString(date, "yyyy-MM-dd"));
        lineSeries->append(xAxisValue.toMSecsSinceEpoch(), timeSeriesOHLC["4. close"].toString().toDouble());
    }

    qDebug() << "Min: " << list.first() << " | Max: " << list.last();
    emit yAxisMinChanged(list.first() - list.last()*0.1);
    emit yAxisMaxChanged(list.last() + list.last()*0.1);


//    QDateTime xValue;
//    xValue.setDate(QDate(2017, 11, 06));
//    xValue.setTime(QTime(0, 0));
//    lineSeries->append(xValue.toMSecsSinceEpoch(), 192.6);

//    xValue.setTime(QTime(7,0));
//    lineSeries->append(xValue.toMSecsSinceEpoch(), 89);

//    xValue.setTime(QTime(9,0));
//    lineSeries->append(xValue.toMSecsSinceEpoch(), 100);

//    xValue.setTime(QTime(12,0));
//    lineSeries->append(xValue.toMSecsSinceEpoch(), 50);

//    xValue.setTime(QTime(14,0));
//    lineSeries->append(xValue.toMSecsSinceEpoch(), 250);

//    xValue.setTime(QTime(18,0));
//    lineSeries->append(xValue.toMSecsSinceEpoch(), 140);

//    xValue.setTime(QTime(21,0));
//    lineSeries->append(xValue.toMSecsSinceEpoch(), 80);

//    xValue.setTime(QTime(23,30));
//    lineSeries->append(xValue.toMSecsSinceEpoch(), 200);

//    xValue.setDate(QDate(2011, 11, 07));
//    xValue.setTime(QTime(0,0));
//    lineSeries->append(xValue.toMSecsSinceEpoch(), 192.6);

//    lineSeries->setPen(penLineSeries);

//    return lineSeries;
}

void StockChart::getStockData()
{
////    QUrl url;
////    url.setQuery("https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=MSFT&apikey=demo");
//    QNetworkAccessManager networkAccessManager;
//    QNetworkRequest networkRequest(QUrl(QStringLiteral("https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=MSFT&apikey=demo")));
//    QNetworkReply *networkReply = networkAccessManager.get(networkRequest);

//    qDebug() << networkReply->readAll();

//    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
//    QNetworkRequest request;
//    request.setUrl(QUrl("http://qt-project.org"));
////    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");

//    QNetworkReply *reply = manager->get(request);
////    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
////    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));
//    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(getRequestResponse(QNetworkReply *)));

    // http://doc.qt.io/qt-5/qnetworkaccessmanager.html
    // A simple download off the network could be accomplished with:
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    manager->get(QNetworkRequest(QUrl("https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=AMZN&apikey=KFQCEU5ZSFDTIOGW")));

//    // A more involved example, assuming the manager is already existent, can be:
//    QNetworkRequest request;
//    request.setUrl(QUrl("http://qt-project.org"));
//    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");

//    QNetworkReply *reply = manager->get(request);
//    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
//    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));
//    connect(reply, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(slotSslErrors(QList<QSslError>)));
}

void StockChart::replyFinished(QNetworkReply *reply)
{
    QByteArray jsonData;
    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument;
    QJsonObject jsonObject;

    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    }
    else
    {
//        qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
//        qDebug() << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();;
//        qDebug() << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
//        qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
//        qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();

        jsonData = reply->readAll();

        QFile *file = new QFile("D:/Qt/downloaded.txt");
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
//    QJsonValue timeSeries = jsonObject["Time Series (Daily)"];
//    QJsonValue timeSeries = jsonObject.value("Time Series (Daily)");
    QJsonObject timeSeries = jsonObject.value("Time Series (Daily)").toObject();

//    qDebug() << timeSeries;

    QStringList timeSeriesKeys = timeSeries.keys();

    foreach(QString date, timeSeriesKeys){
        QJsonObject timeSeriesOHLC = timeSeries[date].toObject();
//        qDebug() << date << timeSeriesOHLC.value("1. open").toString() << timeSeriesOHLC["4. close"].toString();
    }

    this->timeSeries = timeSeries;

    emit addStockChartTimeSeries(timeSeries);

    reply->deleteLater();
}
