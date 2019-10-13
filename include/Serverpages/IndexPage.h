#include <avr/pgmspace.h>

const char index_html[] PROGMEM =
{

"<!doctype html><html lang=\"en\"> <head> <meta charset=\"utf-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\"> <link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\" integrity=\"sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T\" crossorigin=\"anonymous\"> <link rel=\"stylesheet\" href=\"css/station.css\"> <title>OctoPrint Monitor | Dashboard</title> </head> <body> %NAVBAR% <div class=\"container-fluid\" style=\"margin-top:80px\"> <h3 id=\"dashboardTitle\">Dashboard - not connected</h3> <table class=\"table\" style=\"background-color: white\"> <thead class=\"thead-light\"> <tr> <th>Print Monitor Info</th> </tr></thead> <tbody> <tr> <td> <ul id=\"monitorInfoList\" class=\"list-group\"> <li class=\"list-group-item\">Waiting...</li></ul> </td></tr></tbody> </table> <table class=\"table\" style=\"background-color: white\"> <thead class=\"thead-light\"> <tr> <th>Internet current weather</th> </tr></thead> <tbody> <tr> <td> <ul id=\"internetWeatherList\" class=\"list-group\"> <li class=\"list-group-item\">Waiting...</li></ul> </td></tr></tbody> </table> </div><script src=\"https://code.jquery.com/jquery-3.3.1.slim.min.js\" integrity=\"sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo\" crossorigin=\"anonymous\"></script> <script src=\"https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js\" integrity=\"sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1\" crossorigin=\"anonymous\"></script> <script src=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js\" integrity=\"sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM\" crossorigin=\"anonymous\"></script> <script src=\"js/station.js\"></script> </body></html>"

};

const char station_js[] PROGMEM =
{

"var websocket;function init(){openWebSocket();}function updateInternetCurrent(messageData){var current=messageData.currentReadings; var currentValue; var observedTime; $(\"#internetWeatherList\").empty(); if(current.metric){currentValue=current.temp.toFixed(1) + \"C - \" + current.description;}else{currentValue=current.temp.toFixed(1) + \"F - \" + current.description;}$(\"#internetWeatherList\").append('<li class=\"list-group-item\">' + currentValue + '</li>'); currentValue=\"Humidity: \" + current.humidity + \"%\"; $(\"#internetWeatherList\").append('<li class=\"list-group-item\">' + currentValue + '</li>'); currentValue=\"Wind speed: \" + current.windSpeed + \"m/s from \" + current.windDirection + \"&#176\"; $(\"#internetWeatherList\").append('<li class=\"list-group-item\">' + currentValue + '</li>'); observedTime=new Date(current.time * 1000); currentValue=\"Observed at: \" + observedTime.toLocaleTimeString(\"en-GB\") + \" on \" + observedTime.toLocaleDateString(\"en-GB\"); $(\"#internetWeatherList\").append('<li class=\"list-group-item\">' + currentValue + '</li>');}function updateMonitorInfo(messageData){$(\"#monitorInfoList\").empty(); if(messageData.enabled){if(messageData.validPrintData){$(\"#monitorInfoList\").append('<li class=\"list-group-item\">' + 'Printer state: ' + messageData.printState + '</li>');}else{$(\"#monitorInfoList\").append('<li class=\"list-group-item\">' + 'No valid data received.' + '</li>');}}else{$(\"#monitorInfoList\").append('<li class=\"list-group-item\">' + 'Monitor not enabled.' + '</li>');}}function openWebSocket(){websocket=new WebSocket('ws://' + document.location.host + '/ws'); websocket.onopen=function(evt){onOpen(evt)}; websocket.onclose=function(evt){onClose(evt)}; websocket.onmessage=function(evt){onMessage(evt)}; websocket.onerror=function(evt){onError(evt)};}function onOpen(evt){$(\"#dashboardTitle\").html(\"Dashboard - connected\");}function onClose(evt){$(\"#dashboardTitle\").html(\"Dashboard - not connected\");}function onMessage(evt){console.log(evt.data); var messageData=JSON.parse(evt.data); switch(messageData.type){case \"currentWeather\": updateInternetCurrent(messageData); break; case \"monitorInfo\": updateMonitorInfo(messageData); break;}}function onError(evt){}function doSend(message){websocket.send(message);}window.addEventListener(\"load\", init, false);"

};