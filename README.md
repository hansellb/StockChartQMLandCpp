# StockChartQMLandCpp - Time Series Chart Application
## Introduction
Basic application that shows multiple time series in a chart (using Qt QML and C++)

This program demonstrates the use of:
* Qt QNetworkAccessManager to make and receive http requests
* Design a basic UI/front-end using Qt QML
* Implement the backend logic in C++
* Integration of C++ in QML (two-way communication between Qt QML and C++)



## How it works:
The program will retrieve stock information from Alpha Vantage by using one of their APIs
* <https://www.alphavantage.co/documentation/>
* <https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=MSFT&apikey=demo>

The stock data retrieved, is JSON object containing time series with the stock's open, high, low, close prices and volume information.



## The GUI / Front end
The UI is entirely built using QML. It has two ComboBoxes, four Buttons and one ChartView.
The following screenshot shows the application displaying three time series / stocks / plot lines on the chart (the last stock added was NVidia or *NVDA* as seen in the leftmost ComboBox) with the "BlueCerulean" theme applied.
![screenshot](https://github.com/hansellb/StockChartQMLandCpp/blob/master/img/screenshot.jpg "Application screenshot")


### ComboBoxes
The first ComboBox contains a predefined set of "symbol"s or stock IDs (e.g., Amazon is *AMZN*, Google is *GOOG*, Apple is *AAPL*, etc.).

The first element in the ComboBox is ATVI, therefore, when the program starts, the Activision Blizzard, Inc. stock data will be retrieved.
When the user selects another stock ID from the combo box, the stock data for that ID will be added and displayed on the chart.
After the time series is added to the chart, the program will automatically adjust the Y axis scale to fit the recently retrieved stock data.

The second ComboBox lets the user change the chart's visual style, e.g., how the chart looks.
These visual changes are based on themes already available for the ChartView QML type


### Buttons
There are five (5) buttons in the UI that create a better user experience:

#### "Delete Stock"
This button will delete the stock time series or stock data, from the chart, corresponding to the name currently visible in the ComboBox, thus, if the combo box has AMZN displayed, when the button is clicked, the AMZN chart plot will be removed.

#### "Fit ALL"
This button will adjust the Y axis of the chart to have values between the maximum and minimum values amongst all time series in the chart.
For example, suppose there is one plot line in the chart with values between 60 and 200. If another plot line with values between 800 and 1000 is added, then the first line will not be visible as the application will adjust the chart to perfectly visualize the newly added plot line.
Clicking the "Fit ALL" button will adjust the chart to be able to display values between 60 and 1000.

#### "Delete ALL"
This button removes/deletes ALL plot lines in the chart

#### "Zoom In"
This buttons zooms in the center of the chart

#### "Zoom Out"
This buttons zooms out until the original view of the plot line, that is, the button does not allow the line series to be smaller than the chart's plot area.



## UML Diagrams
### Class diagram
![class diagram](https://github.com/hansellb/StockChartQMLandCpp/blob/master/img/class_diagram.png "Class Diagram")

### Sequence diagram
![sequence diagram](https://github.com/hansellb/StockChartQMLandCpp/blob/master/img/sequence_diagram.png "Sequence Diagram")
