import QtQuick 2.6
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import QtCharts 2.2

import StockChart 1.0

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")


    StockChart {
        id: stockChart
        onAddStockChartTimeSeries: {
//            console.log("addStockChartTimeSeries: ", JSON.stringify(timeSeries));
            Object.keys(timeSeries).forEach(function callback(currentValue, index, array){
//                console.log(index + " -> " + currentValue);
//                console.log(timeSeries[currentValue]["1. open"]);
            });

            var mySeries = chartView.createSeries(ChartView.SeriesTypeLine, "Line", xTime, yValues);
            stockChart.setLineSeries(mySeries);
        }

        onStartDateChanged: {
//            console.log("onStartDateChanged");
//            console.log(date);
            xTime.min = date;
        }

        onEndDateChanged: {
//            console.log("onEndDateChanged");
//            console.log(date);
            xTime.max = date;
        }

        onYAxisMinChanged: {
            console.log("yAxis Min: " + typeof(value) + value);
            yValues.min = value;
        }

        onYAxisMaxChanged: {
            console.log("yAxis Max: " + value);
            yValues.max = value;
        }
    } // StockChart

//    function addSeries()
//    {
//        // var xyz = diabetesView.setLineSeries();

//        var series = chartView.createSeries(ChartView.SeriesTypeLine, "Test", chartView.axisX(lineseries), chartView.axisY(lineseries));
//        series.append(0,50);
//        series.append(4,130);

//        series = stockChart.setLineSeries();

//        chartView.update();
//    }

	//https://stackoverflow.com/questions/38467769/add-c-qabstractseries-to-qml-chartview
    function addSeries()
    {
        //Define Axes of the ChartView
//        stockChart.getAxisYDescription(yDescription);
//        stockChart.getAxisXTime(xTime);
//        stockChart.getAxisYValues(yValues);

        stockChart.getStockData();

        // Create new LineSeries with 3 Axes (Two-Y-Axis, One-X-Axis)
        var mySeries = chartView.createSeries(ChartView.SeriesTypeLine, "Line", xTime, yValues);
        var mySeries2 = chartView.createSeries(ChartView.SeriesTypeLine, "Overview", xTime, yDescription);

//        // Define series on specific wishes
//        stockChart.setLineSeries(mySeries);

        //Delete not needed series (only created because second y-Axis
        chartView.removeSeries(mySeries);
        chartView.removeSeries(mySeries2);
    }

    Column {
        Rectangle {
            id: infoArea1
            color: "green"
            width: applicationWindow.width
            height: applicationWindow.height *0.25

            MouseArea{
                anchors.fill: parent
                onClicked: addSeries()
            }
        }

//        ChartView{
//            id: chartView
//            width: applicationWindow.width
//            height: applicationWindow.height *0.75
//            title: "Line"

//            antialiasing: true

//            ValueAxis{
//                id: vlaueAxisX
//                min: 0
//                max: 24
//                tickCount: 12
//                labelFormat: "%2.0f:00"
//            }
//            ValueAxis{
//                id: valueAxisY
//                min:0
//                max: 500
////                tickCount: 50
//                tickCount: 12
//            }

//            LineSeries {
//                id: lineseries
//                axisX: vlaueAxisX
//                axisY: valueAxisY
//                name: "LineSeries"
//                XYPoint { id: zero; x: 0; y: 192.6}
//                XYPoint { id: first; x: 7; y: 89 }
//                XYPoint { x: 9; y: 80 }
//                XYPoint { x: 12; y: 30 }
//                XYPoint { x: 14; y: 150 }
//                XYPoint { x: 18; y: 40 }
//                XYPoint { x: 21; y: 280 }
//                XYPoint { id: last; x: 23.5; y: 200 }
//                XYPoint { id: twentyfour; x: 24; y: 192.6}
//            }
//        }

        ChartView {
            id: chartView
            title: "Stock XYZ"
            width: applicationWindow.width * 0.78
            height: applicationWindow.height * 0.66
            antialiasing: true
//            backgroundColor: "grey"

            CategoryAxis {
                id: yDescription
                min: 0
                max: 500
//                tickCount: 12
            }

            DateTimeAxis {
                id: xTime
//                format: "yyyy-MM-dd hh:mm:ss"
                format: "yyyy-MM-dd"
                min: stockChart.startDate
                max: stockChart.endDate
                tickCount: 12
                labelsAngle: 90
            }

            ValueAxis {
                id: yValues
                min: stockChart.yAxisMin
                max: stockChart.yAxisMax
                tickCount: 5
            }

//            CategoryAxis {
//                id: yValues
//                min: 0
//                max: 1500
//                tickCount: 12

////                CategoryRange {
////                    label: "critical"
////                    endValue: 50
////                }

////                CategoryRange {
////                    label: "low"
////                    endValue: 80
////                }

////                CategoryRange {
////                    label: "normal"
////                    endValue: 120
////                }

////                CategoryRange {
////                    label: "high"
////                    endValue: 160
////                }

////                CategoryRange {
////                    label: "extremely high"
////                    endValue: 200
////                }
//            }
        }
    }
}
