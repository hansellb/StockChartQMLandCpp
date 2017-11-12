//https://stackoverflow.com/questions/38467769/add-c-qabstractseries-to-qml-chartview
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
    qDebug() << "main";
    QApplication app(argc, argv);

    qmlRegisterType<StockChart>("StockChart", 1, 0, "StockChart");

//    QQmlEngine qmlEngine;
//    QQmlComponent qmlComponent(&engine, QUrl("qrc:/main.qml"));
//    StockChart *stockChart = qobject_cast<StockChart *>(qmlComponent.create());

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    StockChart stockChart;

//    QObject *qmlElement = engine.rootObjects().at(0)->findChild<QObject *>(QString("applicationWindow"));
//    qDebug() << qmlElement;
//    QObject::connect(&stockChart, SIGNAL(addStockChartTimeSeries(QJsonObject)), qmlElement, SLOT(test(QJsonObject)));

    //https://doc.qt.io/qt-5/qtqml-cppintegration-interactqmlfromcpp.html
//    // Using QQmlComponent
//    QQmlEngine engine;
//    QQmlComponent component(&engine, QUrl::setUrl("main.qml"));
//    QObject *object = component.create();
//    object->setProperty("width", 500);
//    QQmlProperty(object, "width").write(500);
////    delete object;

//    // Using QQuickView
//    QQuickView view;
//    view.setSource(QUrl(QStringLiteral("MyItem.qml")));
//    view.show();
////    QObject *object = view.rootObject();
//    *object = view.rootObject();
//    QQuickItem *item = qobject_cast<QQuickItem*>(object);
//    item->setWidth(500);

//    QObject *rect = object->findChild<QObject*>("rect");

//    delete object;

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
