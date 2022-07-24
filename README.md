# Borewell Motor Monitoring and Overcoming Motor Failure Using Internet of Things
## Introduction
Groundwater is the mainstay of irrigated agriculture in India. As agriculture cannot flourish without judicious use of water, most of the farmers in India use groundwater irrigation. But when underground water is not available, the motor pumps which depend on groundwater run dry and thus get damaged. This causes huge loss to the farmer as it takes few months to get the motor repaired. As the crop lacks irrigation facility during this period, it withers thus causing the farmer’s effort to go vain.

## Problem Statement
To design and implement a system for measuring the depth of water and the health of motor in a functioning borewell using IoT application.

## Objective
To design and implement Borewell Motor Monitoring system

•	To collect the various parameters of borewell and motor <br />
•	Real time monitoring of borewell and motor<br />
•	To analyse and indicate the fault in motor<br />
•	To gather data of various borewell<br />
•	To predict the water level of the region<br />

## Pain points of farmer

•	High load(voltage) causes the short circuit and motor gets damaged<br />
•	Farmers don’t know the water level of borewell and motor runs in dry<br />
•	If borewell motor fails(damaged) it takes few months to get the motor repaired.<br />
•	Cost of repairing the motor is around 2000 to 3000 RS<br />
•	Require labours to take the damaged motor out from the borewell<br />
•	Labour charges<br />
•	Takes around 4 to 5 hours to take the motor out from the borewell. If the depth of borewell is more than 600 feet then it takes longer time.<br />
•	Accident may occur while taking the motor out from the borewell<br />
•	As the borewell is not working farmer is not able to provide the water to the farm (crops also get affected)<br />
•	Repairing shop of motor is at the distance place, difficult to move the motor from one place to another<br />
<br />
## Initial Level Block Diagram
<img src="https://user-images.githubusercontent.com/56119880/180648171-55e223dd-d698-4143-9de3-d8a3905b6787.png" width="600" height="500"/><br />
<br />
## Final Idea Detailed Sketch
<img src="https://user-images.githubusercontent.com/56119880/180647921-4fcc2cd4-290a-43de-ba44-813f6dd232c5.png" width="700" height="500"/><br />
<br />
## Flow of System
<img src="https://user-images.githubusercontent.com/56119880/180648080-4024d3a1-b920-4cef-b620-ed9e7a8e6dc9.png" width="500" height="550"/><br />

## Design of the system
## What is Layer 3 Architecture

A three-layer architecture is the common and generally known structure.
In Layer 3 architecture data gets collected from the end device through sensors and actuators then the data collected from sensors and actuators is redirected to Gateway using WIFI or Zigbee protocol, Gateway uniquely identify the data for each end device and then from Gateway data is redirected to the cloud using IP Protocol.
<br />
## Layer 3 Architecture Design
<img src="https://user-images.githubusercontent.com/56119880/180648305-66a6ee0a-dce8-475d-be7f-e20a9d616fba.png" width="700" height="500"/><br />
<br />
## MQTT Protocol

## Explanation and Justification for using MQTT Protocol
Here the End Devices are connected to the Bluetooth and WIFI Module (ESP32) using this ESP32, I am going to connect the End device to the Gateway (Rasberry pi) and to redirect the data from ESP32 to the Gateway (Rasberry pi) I use MQTT protocol for data exchange between constrained devices and server applications.
MQTT keeps bandwidth requirements to an absolute minimum, handles unreliable networks. I have used MQTT over HTTP because MQTT is 93 times faster than HTTP's. MQTT can connect many thousands or even millions of devices. Besides the scalability, it is simple to use. It has low system requirements and high compatibility with Internet-connected applications
## Advantages of MQTT

•	Efficient data transmission.<br />
•	Quick to implement as it is a lightweight protocol.<br />
•	Low network usage due to minimization of data packets.<br />
•	Fast and efficient message delivery.<br />
•	Uses very small amounts of power, which is good especially for the wireless devices.<br />
•	Reduction of network bandwidth in communication.

## Communication Architecture Design

<img src="https://user-images.githubusercontent.com/56119880/180648458-6ba02b6b-c945-4db6-b8ae-13cd2d57b71d.png" width="700" height="500"/><br />
<br />
