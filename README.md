The main goal of this project is to offer a way to access Home IR devices through the internet. To meet this objective, we have created a project which consists of two main parts:

<b>Arduino Project:</b>

Responsable for exposing Arduino Microcontroller Board as a Web service, so it can receive HTTP requests and translate it into IR signals for all Home devices located near the IR Led Emitter. The image below ilustrates how the eletronic components are conencted together with arduino Board.

![alt tag](https://github.com/lferst/HouseAutomations/blob/master/arduinoProject/Arduino.png)

<b>Web Application (SpringBoot/Spring REST/AngularJS):</b>

This next part of the project contains the Web application to deal with Arduino exposed Web Services. It was done using SpringBoot and so among some other advantages, it has an embedded tomcat instance in it removing the dependency of having an environment pre-setup with a specific web server.   


![alt tag](https://github.com/lferst/HouseAutomations/blob/master/screens.jpg)



















