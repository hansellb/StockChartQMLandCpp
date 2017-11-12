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
    QApplication app(argc, argv);

    qmlRegisterType<StockChart>("StockChart", 1, 0, "StockChart");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
