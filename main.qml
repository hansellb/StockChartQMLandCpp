/*! \file main.qml
 *  \brief QML file containing the application's Front end / GUI implementation
 */
import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtCharts 2.2

import StockChart 1.0
import QtQuick.Templates 2.2
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2

/*!
 * Doxygen, class & sequence diagram, theme and zoom
 */
ApplicationWindow
{
  id: applicationWindow
  objectName: "applicationWindow"
  visible: true
  width: 640
  height: 480
  title: qsTr("Stocks")

  function lineSeriesClicked(lineSeriesPoint)
  {
    console.log(JSON.stringify(this));
    console.log(lineSeriesPoint);
  }

  function lineSeriesHovered(lineSeriesPoint, isHovered)
  {
    if(isHovered)
    {
      var date = new Date(lineSeriesPoint.x);
      console.log(date.getFullYear() + "-" + (((date.getMonth()+1) < 10) ? ("0" + (date.getMonth()+1).toString()) : (date.getMonth()+1)) + "-" + (((date.getDate()) < 10) ? ("0" + (date.getDate()).toString()) : (date.getDate())) + " -> " + lineSeriesPoint.y);
    }
  }

  StockChart
  {
    id: stockChart
    objectName: "stockChart"
//    startDate: "2016-01-01"
//    endDate: "2016-12-31"

    onTimeSeriesReady:
    {
      // Create a new empty AbstractSeries/XYSeries/LineSeries to be plotted in the chart
      // stockID is sent from C++ when the timeSeriesReady signal is emitted
      var chartViewSeries = chartView.createSeries(ChartView.SeriesTypeLine, stockID, dateTimeAxis_chartView_xAxis, valueAxis_chartView_yAxis);

      // Set chartViewSeries (AbstractSeries/LineSeries) properties
      chartViewSeries.objectName = stockID;
      chartViewSeries.capStyle = Qt.RoundCap;
//      chartViewSeries.width = 2.75;
      chartViewSeries.onClicked.connect(lineSeriesClicked);
      chartViewSeries.onHovered.connect(lineSeriesHovered);

      stockChart.setLineSeries(chartViewSeries);
    }

    onStartDateChanged: { dateTimeAxis_chartView_xAxis.min = date; }

    onEndDateChanged: { dateTimeAxis_chartView_xAxis.max = date; }

    onYAxisMinChanged: { valueAxis_chartView_yAxis.min = value; }

    onYAxisMaxChanged: { valueAxis_chartView_yAxis.max = value; }
  } // StockChart

  ColumnLayout
  {
    id: columnLayout
    objectName: "columnLayout"
    width: parent.width
    height: parent.height

    RowLayout
    {
      id: rowLayout
      objectName: "rowLayout"
      height: 50

      ComboBox
      {
        id: comboBox_stockID
        objectName: "comboBox_stockID"
        textRole: "key"
        Layout.maximumWidth: 90

        model: ListModel
        {
          ListElement { key: "ATVI"; value: 1 }
          ListElement { key: "ADBE"; value: 2 }
          ListElement { key: "AKAM"; value: 3 }
          ListElement { key: "GOOG"; value: 4 }
          ListElement { key: "AMZN"; value: 5 }
          ListElement { key: "AAPL"; value: 6 }
          ListElement { key: "ADSK"; value: 7 }
          ListElement { key: "BIDU"; value: 8 }
          ListElement { key: "CSCO"; value: 9 }
          ListElement { key: "COST"; value: 10 }
          ListElement { key: "DISH"; value: 11 }
          ListElement { key: "DLTR"; value: 12 }
          ListElement { key: "EBAY"; value: 13 }
          ListElement { key: "EA"; value: 14 }
          ListElement { key: "INTC"; value: 15 }
          ListElement { key: "MAT"; value: 16 }
          ListElement { key: "MXIM"; value: 17 }
          ListElement { key: "MSFT"; value: 18 }
          ListElement { key: "NFLX"; value: 19 }
          ListElement { key: "NVDA"; value: 20 }
          ListElement { key: "NXPI"; value: 21 }
          ListElement { key: "PYPL"; value: 22 }
          ListElement { key: "QCOM"; value: 23 }
//                    ListElement { key: "SNDK"; value: 24 }
          ListElement { key: "SBUX"; value: 25 }
          ListElement { key: "SYMC"; value: 26 }
          ListElement { key: "TSLA"; value: 27 }
          ListElement { key: "KHC"; value: 28 }
          ListElement { key: "PCLN"; value: 29 }
          ListElement { key: "TRIP"; value: 30 }
          ListElement { key: "FOX"; value: 31 }
//                    ListElement { key: "WFM"; value: 32 }
        }

        onCurrentTextChanged:
        {
          if(chartView.series(comboBox_stockID.currentText) === null)
          {
            stockChart.getStockData(comboBox_stockID.currentText);
          }else { console.log("Stock already in the chart!!!"); }
        }
      }// ComboBox

      Button
      {
        id: button_removeSeries
        objectName: "button_removeSeries"
        anchors.left: comboBox_stockID.right
        anchors.leftMargin: 10
        text: qsTr("Delete\nStock")
        Layout.maximumWidth: 50

        onClicked:
        {
          if(chartView.count > 0)
          {
            chartView.removeSeries(chartView.series(comboBox_stockID.currentText));
          }else { dialogError.open(); }
        }
      }// Button

      Button
      {
        id: button_fitAll
        objectName: "button_fitAll"
        text: qsTr("Fit\nALL")
        anchors.left: button_removeSeries.right
        anchors.leftMargin: 10
        Layout.maximumWidth: 50

        onClicked:
        {
          var maxY = 0;
          var minY = 10000;

          for(var i=0; i < chartView.count; i++)
          {
            var series = chartView.series(i);
            for(var j=0; j < series.count; j++)
            {
              if(series.at(j).y > maxY){ maxY = series.at(j).y; }
              if(series.at(j).y < minY){ minY = series.at(j).y; }
            }
          }
          valueAxis_chartView_yAxis.min = minY - minY * 0.01;
          valueAxis_chartView_yAxis.max = maxY + minY * 0.01;
        }
      }// Button

      Button
      {
        id: button_removeAllSeries
        objectName: "button_removeAllSeries"
        text: qsTr("Delete\nALL")
        anchors.left: button_fitAll.right
        anchors.leftMargin: 10
        Layout.maximumWidth: 50

        onClicked:
        {
          chartView.removeAllSeries();
        }
      }// Button

      Button
      {
        id: button_zoomIn
        objectName: "button_zoomIn"
        text: qsTr("Zoom\nIn")
        anchors.left: button_removeAllSeries.right
        anchors.leftMargin: 10
        Layout.maximumWidth: 50

        onClicked:
        {
          chartView.zoomIn();
        }
      }// Button

      Button
      {
        id: button_zoomOut
        objectName: "button_zoomOut"
        text: qsTr("Zoom\nOut")
        anchors.left: button_zoomIn.right
        anchors.leftMargin: 10
        Layout.maximumWidth: 50

        onClicked:
        {
//          console.log( typeof(stockChart.startDate) + " | " + typeof(JSON.stringify(dateTimeAxis_chartView_xAxis.min).slice(1, 11)));
          // DateTimeAxis.min is a QDateTime object, therefore, DateTimeAxis.min.toString((const QString &format) is possible (https://doc.qt.io/qt-5/qdatetime.html)
          if(stockChart.startDate == JSON.stringify(dateTimeAxis_chartView_xAxis.min).slice(1,11))
          {}else{ chartView.zoomOut(); }
        }
      }// Button

      ComboBox
      {
        id: comboBox_changeTheme
        objectName: "comboBox_changeTheme"
        textRole: "key"
        anchors.left: button_zoomOut.right
        anchors.leftMargin: 10
        width: 10
        Layout.minimumWidth: 125

        model: ListModel
        {
          ListElement { key: "Light"; value: 1 }
          ListElement { key: "BlueCerulean"; value: 2 }
          ListElement { key: "Dark"; value: 3 }
          ListElement { key: "BrownSand"; value: 4 }
          ListElement { key: "BlueNcs"; value: 5 }
          ListElement { key: "HighContrast"; value: 6 }
          ListElement { key: "BlueIcy"; value: 7 }
          ListElement { key: "Qt"; value: 8 }
        }

        onCurrentTextChanged:
        {
          if(comboBox_changeTheme.currentText == "Light")
          {
            chartView.theme = ChartView.ChartThemeLight;
          }else if(comboBox_changeTheme.currentText == "BlueCerulean")
          {
            chartView.theme = ChartView.ChartThemeBlueCerulean;
          }else if(comboBox_changeTheme.currentText == "Dark")
          {
            chartView.theme = ChartView.ChartThemeDark;
          }else if(comboBox_changeTheme.currentText == "BrownSand")
          {
            chartView.theme = ChartView.ChartThemeBrownSand;
          }else if(comboBox_changeTheme.currentText == "BlueNcs")
          {
            chartView.theme = ChartView.ChartThemeBlueNcs;
          }else if(comboBox_changeTheme.currentText == "HighContrast")
          {
            chartView.theme = ChartView.ChartThemeHighContrast;
          }else if(comboBox_changeTheme.currentText == "BlueIcy")
          {
            chartView.theme = ChartView.ChartThemeBlueIcy;
          }else if(comboBox_changeTheme.currentText == "Qt")
          {
            chartView.theme = ChartView.ChartThemeQt;
          }
        }
      }// Button
    }// RowLayout

    ChartView
    {
      id: chartView
      objectName: "chartView"
      Layout.fillWidth: true
      Layout.fillHeight: true
      anchors.top: rowLayout.bottom
      antialiasing: true
      theme: ChartView.ChartThemeDark

      DateTimeAxis
      {
        id: dateTimeAxis_chartView_xAxis
        objectName: "dateTimeAxis_chartView_xAxis"
        format: "yyyy-MM-dd"
        min: stockChart.startDate
        max: stockChart.endDate
        tickCount: 12
        labelsAngle: 90
      }

      ValueAxis
      {
        id: valueAxis_chartView_yAxis
        objectName: "valueAxis_chartView_yAxis"
        min: 900
        max: 1200
        tickCount: 10
      }
    }// ChartView
  }// ColumnLayout
}// ApplicationWindow
