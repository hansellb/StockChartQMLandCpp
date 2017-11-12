# StockChartQMLandCpp
Basic application that shows multiple time series in a chart (using Qt QML and C++)

This program demonstrates the use of:

- Qt QNetworkAccessManager to make and receive http requests
- Design a basic UI/front-end using Qt QML
- Implement the backend logic in C++
- Integration of C++ in QML (two-way communication between Qt QML and C++)

How it works:

The program will retrieve stock information from Alpha Vantage by using their APIs (https://www.alphavantage.co/documentation/, https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=MSFT&apikey=demo). The stock data is a time series with the stock's open, high, low, close prices and volume information.

The UI has one ComboBox, two Buttons and one ChartView. The ComboBox contains a predefined set of "symbol"s or stock IDs (e.g., Amazon is AMZN, Google is GOOG, Apple is AAPL, etc.). The first element in the ComboBox is AMZN, therefore, when the program starts, the Amazon stock data will be retrieved. When the user selects another stock ID from the combo box, the stock data from that ID will be added and displayed on the chart. After the time series is added to the chart, the program will automatically adjust the Y axis scale to fit the recently retrieved stock data.

The button "Delete Stock" in the UI will delete the stock time series or stock data corresponding to the name in the ComboBox, thus, if the combo box has AMZN displayed, when the "Delete Stock" button is clicked, the AMZN chart plot will be removed.

The burron "Fit ALL" will adjust the Y axis of the chart to have values between the maximum and minimum values amongst all time series in the chart.
