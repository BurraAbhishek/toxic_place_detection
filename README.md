# toxic_place_detection
A simple Arduino-based Gas Leak Detection Device that can warn users about toxic environments, including abnormally high carbon dioxide levels

## Required hardware components:
<ul>
  <li> MQ-135 Air quality sensor </li>
  <li> Any or none of the following air quality and gas sensor modules: 
  <ul>
    <li> MQ-2 (Methane, butane, LPG, smoke sensor)</li>
    <li> MQ-5 (Natural gas, LPG sensor)</li>
    <li> MQ-9 (Carbon monoxide sensor)</li>
    <li> MQ-136 (Hydrogen sulphide sensor)</li>
    <li> MQ-137 (Ammonia sensor)</li>
  </ul>
  <li> Arduino UNO board, </li> 
  <li> Arduino-compatible USB cable, </li> 
  <li> Breadboard, </li>
  <li> Breadboard wires, </li>
  <li> Red, Green, and Yellow (Optional) LEDs, </li>
  <li> Buzzer </li>
  <li> Resistors </li>
  <li> 2 batteries, each 1.5 V </li>
</ul>

## Required software:
Arduino IDE. Available on https://www.arduino.cc/en/software.

## Some basic algorithms:
Each of these sensors show high reading in hazardous environments and low reading in safe environments.
The basic algorithm to determine if an environment is safe is as follows:
```
BEGIN
if ((sensor_1 OR sensor_2 OR sensor_3 OR ... sensor_n) == HIGH) then
    // Hazardous environment
else:
    // Safe environment
end if
END
```

## Module Diagram
<img src="modulediagram/Module Diagram.png" alt="Module Diagram" title="Module Diagram, created using Tinkercad">
NOTE: This module diagram was created on Tinkercad and is licensed under Creative Commons Public Domain (CC BY 3.0)

- The breadboard above the Arduino UNO contains the LEDs and buzzers. The LEDs should be visible and the buzzer should be audible.
- The breadboard below the Arduino UNO contains the MQ Gas sensors. For neatness, the connections to the sensors are not shown. The connections are as follows:
  - Red wire: +5V
  - Black wire: GND (Ground)
  - Brown wires: A0, A1, A2, A3, A4 and/or A5, any of the analog pin(s) can be used. Each pin connects to Analog Output pin of the Gas sensor.

### NOTE: This project is still under development. We will release the Arduino code on or before 8 May 2021.
