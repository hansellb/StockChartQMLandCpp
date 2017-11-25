/*! \file main.cpp
 * \brief This file contains the "main" function. Inside, the class StockChart is registered as a QML type object for it can be used inside a QML file
 *
 */
 
/*! \mainpage VIAUMA09 Homework assignment - Time Series Chart Application
 *
 * \section intro_sec Introduction
 *
 * Basic application that shows multiple time series in a chart (using Qt QML and C++)
 * This program demonstrates the use of:
 * \li Qt QNetworkAccessManager to make and receive http requests
 * \li Design a basic UI/front-end using Qt QML
 * \li Implement the backend logic in C++
 * \li Integration of C++ in QML (two-way communication between Qt QML and C++)
 * \n \n \n
 * \section how_sec How it works:
 * The program will retrieve stock information from Alpha Vantage by using one of their APIs
 * \li \c https://www.alphavantage.co/documentation/
 * \li \c https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=MSFT&apikey=demo
 *
 * The stock data retrieved, is JSON object containing time series with the stock's open, high, low, close prices and volume information.
 * \n \n \n
 * \section gui_sec The GUI / Front end
 * The UI is entirely built using QML. It has two ComboBoxes, four Buttons and one ChartView.
 * The following screenshot shows the application displaying three time series / stocks / plot lines on the chart (the last stock added was NVidia or NVDA as seen in the leftmost ComboBox) with the "BlueCerulean" theme applied.
 * \image html "screenshot.jpg" "Application screeshot"
 * \n \n
 * \subsection comboboxes ComboBoxes
 * The first ComboBox contains a predefined set of "symbol"s or stock IDs (e.g., Amazon is \b AMZN, Google is \b GOOG, Apple is \b AAPL, etc.).
 *
 * The first element in the ComboBox is ATVI, therefore, when the program starts, the Activision Blizzard, Inc. stock data will be retrieved.
 * When the user selects another stock ID from the combo box, the stock data for that ID will be added and displayed on the chart.
 * After the time series is added to the chart, the program will automatically adjust the Y axis scale to fit the recently retrieved stock data.
 *
 * The second ComboBox lets the user change the chart's visual style, e.g., how the chart looks.
 * These visual changes are based on themes already available for the ChartView QML type
 * \n \n
 * \subsection buttons Buttons
 * There are five (5) buttons in the UI that create a better user experience:
 * \n
 * \subsubsection button1 "Delete Stock"
 * This button will delete the stock time series or stock data, from the chart, corresponding to the name currently visible in the ComboBox, thus, if the combo box has AMZN displayed, when the button is clicked, the AMZN chart plot will be removed.
 * \n
 * \subsubsection button2 "Fit ALL"
 * This button will adjust the Y axis of the chart to have values between the maximum and minimum values amongst all time series in the chart.
 * For example, suppose there is one plot line in the chart with values between 60 and 200. If another plot line with values between 800 and 1000 is added, then the first line will not be visible as the application will adjust the chart to perfectly visualize the newly added plot line.
 * Clicking the "Fit ALL" button will adjust the chart to be able to display values between 60 and 1000.
 * \n
 * \subsubsection button3 "Delete ALL"
 * This button removes/deletes ALL plot lines in the chart
 * \n
 * \subsubsection button4 "Zoom In"
 * This buttons zooms in the center of the chart
 * \n
 * \subsubsection button5 "Zoom Out"
 * This buttons zooms out until the original view of the plot line, that is, the button does not allow the line series to be smaller than the chart's plot area.
 * \n \n \n
 * \section diagrams_sec UML Diagrams
 * \subsection class_diag Class diagram
 * \image html class_diagram.png "StockChart Class Diagram"
 * \n \n
 * \subsection sequence_diag Sequence diagram
 * \image html sequence_diagram.png "StockChart Sequence Diagram"
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
