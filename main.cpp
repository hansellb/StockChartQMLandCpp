/*! \file main.cpp
 * This file contains the "main" function. Inside, the class StockChart is registered as a QML type object for it can be used inside a QML file
 *
 */



#include <QtWidgets/QMainWindow>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QApplication>

#include "stockchart.h"



/*!
 * \brief qMain Entry point of ANY C++ program
 * \param argc Number of arguments passed to the function
 * \param argv Argument vector/strings that were passed to the function
 * \return app.exec() causes the actual application to run in an endless loop
 */
int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  // Register the class as a QML object
  qmlRegisterType<StockChart>("StockChart", 1, 0, "StockChart");

  // Create an QML application engine object in order to load the QML file from C++
  QQmlApplicationEngine engine;

  // Load the QML file
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  // Check for errors after loading the QML file
  if (engine.rootObjects().isEmpty())
    return -1;

  // Execute the application and stay in an infinite loop checking for system events
  return app.exec();
}
