////#include <QtCharts/QChartView>
//#include <QtQml/QQmlEngine>
//#include <QtQuick/QQuickView>
//#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QApplication>

#include "stockchart.h"

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
//    qDebug() << "main";
    QApplication app(argc, argv);

    qmlRegisterType<StockChart>("StockChart", 1, 0, "StockChart");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

//    //https://stackoverflow.com/questions/23177839/how-can-i-access-my-window-object-properties-from-c-while-using-qqmlapplicatio
//    // Step 1: get access to the root object
//    QObject *rootObject = engine.rootObjects().first();
//    QObject *qmlObject = rootObject->findChild<QObject*>("valueAxis_chartView_yAxis");

//    // Step 2a: set or get the desired property value for the root object
//    rootObject->setProperty("visible", true);
//    qDebug() << rootObject->property("visible");

//    // Step 2b: set or get the desired property value for any qml object
//    qmlObject->setProperty("visible", true);
//    qDebug() << qmlObject->property("visible");

    return app.exec();
}
