import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtCharts 2.2

import StockChart 1.0
import QtQuick.Templates 2.2
import QtQuick.Controls 2.2

ApplicationWindow {
    id: applicationWindow
    objectName: "applicationWindow"
    visible: true
    width: 640
    height: 480
    title: qsTr("Stocks")

    function lineSeriesClicked(lineSeriesPoint){
        console.log(lineSeriesPoint);
    }

    function lineSeriesHovered(lineSeriesPoint, isHovered){
//        console.log("x: " + lineSeriesPoint.x + " | y: " + lineSeriesPoint.y + " | hovering Point? " + isHovered);
        if(isHovered){
            var date = new Date(lineSeriesPoint.x);
            console.log(date.getFullYear() + "-" + (date.getMonth()+1) + "-" + date.getDate());
        }
    }

    StockChart {
        id: stockChart
        objectName: "stockChart"
//        onAddStockChartTimeSeries: {
        onTimeSeriesReady: {
            // Create a new empty AbstractSeries to be plotted in the chart
            var chartViewSeries = chartView.createSeries(ChartView.SeriesTypeLine, comboBox_stockID.currentText, dateTimeAxis_chartView_xAxis, valueAxis_chartView_yAxis);

            // Set chartViewSeries (AbstractSeries/LineSeries) properties
            chartViewSeries.objectName = comboBox_stockID.currentText;
            chartViewSeries.capStyle = Qt.RoundCap;
            chartViewSeries.width = 2.75;
            chartViewSeries.onClicked.connect(lineSeriesClicked);
            chartViewSeries.onHovered.connect(lineSeriesHovered);

//            console.log(chartViewSeries.count); // 0
            stockChart.setLineSeries(chartViewSeries);
//            console.log(chartViewSeries.count); // 100
//            chartView.title = stockID.currentText

//            lineSeries_stockOpenPrice.name = comboBox_stockID.currentText;
//            stockChart.setLineSeries(lineSeries_stockOpenPrice);
        }

        onStartDateChanged: { dateTimeAxis_chartView_xAxis.min = date; }

        onEndDateChanged: { dateTimeAxis_chartView_xAxis.max = date; }

        onYAxisMinChanged: { valueAxis_chartView_yAxis.min = value; }

        onYAxisMaxChanged: { valueAxis_chartView_yAxis.max = value; }
    } // StockChart

    function addSeries()
    {
        //Define the ChartView's Axes
//        stockChart.addXAxis(chartView_xAxis);
//        stockChart.addYAxis(chartView_yAxis);

        stockChart.getStockData(comboBox_stockID.currentText);

//        var mySeries = chartView.createSeries(ChartView.SeriesTypeLine, "Line", chartView_xAxis, chartView_yAxis);

        //Delete not needed series (only created because second y-Axis
//        chartView.removeSeries(mySeries);
    }

    ColumnLayout {
        id: columnLayout
        objectName: "columnLayout"
        width: parent.width
        height: parent.height
//        anchors.fill: parent

//        Rectangle {
//            id: infoArea1
//            color: "green"
//            width: 50
//            height: 50

//            MouseArea{
//                anchors.fill: parent
//                onClicked: addSeries()
//            }
//        }

        RowLayout {
            id: rowLayout
            objectName: "rowLayout"
            height: 50

            ComboBox {
                id: comboBox_stockID
                objectName: "comboBox_stockID"
                textRole: "key"

                model: ListModel {
                    ListElement { key: "AMZN"; value: 1 }
                    ListElement { key: "AAPL"; value: 2 }
                    ListElement { key: "GOOG"; value: 3 }
                    ListElement { key: "NFLX"; value: 4 }
                    ListElement { key: "NVDA"; value: 5 }
                    ListElement { key: "TSLA"; value: 6 }
    //                ListElement { key: "YHOO"; value: 7 }
                }

                onCurrentTextChanged: {
    //                addSeries()
                    stockChart.getStockData(comboBox_stockID.currentText)
                }
            }// ComboBox

            Button {
                id: button_removeSeries
                objectName: "button_removeSeries"
                anchors.left: comboBox_stockID.right
                anchors.leftMargin: 10
                text: qsTr("Button")

                onClicked: {
                    valueAxis_chartView_yAxis.min = 0;
                    valueAxis_chartView_yAxis.max = 1200;
//                    chartView.removeSeries(chartView.series("AMZN"));
//                    console.log("plotArea: " + chartView.plotArea + "x:" + chartView.plotArea.x + " | y: " + chartView.plotArea.y);
                }
            }// Button

            Rectangle {
                id: container
                anchors.left: button_removeSeries.right
                anchors.leftMargin: 10
                Layout.fillWidth: true; height: parent.height

                Rectangle {
                    id: rect
                    width: 50; height: 50
                    color: "red"
                    opacity: (600.0 - rect.x) / 600

                    MouseArea {
                        anchors.fill: parent
                        drag.target: rect
                        drag.axis: Drag.XAxis
                        drag.minimumX: 0
                        drag.maximumX: container.width - rect.width
                    }
                }
            }// Rectangle

        }// RowLayout

        ChartView {
            id: chartView
            objectName: "chartView"
//            title: "Stocks"
            Layout.fillWidth: true
            Layout.fillHeight: true
            anchors.top: rowLayout.bottom
            antialiasing: true
            theme: ChartView.ChartThemeDark

//            MouseArea {
//                id: mouseArea_chartView
//                objectName: "mouseArea_chartView"
//                anchors.fill: parent
//                hoverEnabled: true

//                onClicked: {
//                    console.log(mouseArea_chartView.mouseX);
////                    chartView_yAxis.min = 0;
////                    chartView_yAxis.max = 1500;
//                }

//                onWheel: {
//                    if(wheel.angleDelta.y > 0){
//                        chartView.zoomIn();
//                    }else{
//                        chartView.zoomOut();
//                    }
//                }
//            }

//            LineSeries {
//                id: lineSeries_stockOpenPrice
//                objectName: "lineSeries_stockOpenPrice"
//                axisX: dateTimeAxis_chartView_xAxis
//                axisY: valueAxis_chartView_yAxis

//                onClicked: {
//                    console.log("clicked on lineseries");
//                }
//            }

            DateTimeAxis {
                id: dateTimeAxis_chartView_xAxis
                objectName: "dateTimeAxis_chartView_xAxis"
                format: "yyyy-MM-dd"
                min: stockChart.startDate
                max: stockChart.endDate
                tickCount: 12
                labelsAngle: 90
            }

            ValueAxis {
                id: valueAxis_chartView_yAxis
                objectName: "valueAxis_chartView_yAxis"
                min: 900
                max: 1200
                tickCount: 10
            }
        }// ChartView
    }// ColumnLayout
}// ApplicationWindow
