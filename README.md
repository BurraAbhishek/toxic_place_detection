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
For the sensors which show high reading in hazardous environments and low reading in safe environments (e.g. MQ-135):
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


For the sensors which show low reading in hazardous environments and high reading in safe environments (e.g. MQ-9):
The basic algorithm to determine if an environment is safe is as follows:
```
BEGIN
if ((sensor_1 AND sensor_2 AND sensor_3 AND ... sensor_n) == LOW) then
    // Hazardous environment
else:
    // Safe environment
end if
END
```


Given that the implementation of both these kind of sensors exist, our approach involves the use of a hazard flag. For the following algorithm, assume that:
- A sensor S0 shows high reading in hazardous environments and low reading in safe environments
- A sensor S1 shows low reading in hazardous environments and high reading in safe environments
- The hazard flag is 1 in a hazardous environment and 0 in a safe environment

Then the approach is as follows:
```
BEGIN

int hazardflag = -1;

if (S0 == HIGH){
    set_hazardflag(1);
} else {
    set_hazardflag(0);
}

if (S1 == HIGH) {
    set_hazardflag(0);
} else {
    set_hazardflag(1);
}

function set_hazardflag(int n) {
    if (n > hazardflag) {
        return n;
    } else {
        return hazardflag;
    }
}

if (hazardflag == 1) {
    // Hazardous environment
} else {
    // Safe environment
}
```


The inference is as follows:
- If any one sensor indicates hazardous environment, then the program should run under the assumption of a hazardous environment.
- Indicate safe area only if all sensors indicate safe area.

## Module Diagram
<img src="modulediagram/Module Diagram.png" alt="Module Diagram" title="Module Diagram, created using Tinkercad">
NOTE: This module diagram was created on Tinkercad and is licensed under Creative Commons Public Domain (CC BY 3.0)

- The breadboard above the Arduino UNO contains the LEDs and buzzers. The LEDs should be visible and the buzzer should be audible.
- The breadboard below the Arduino UNO contains the MQ Gas sensors. For neatness, the connections to the sensors are not shown. The connections are as follows:
  - Red wire: +5V
  - Black wire: GND (Ground)
  - Brown wires: A0, A1, A2, A3, A4 and/or A5, any of the analog pin(s) can be used. Each pin connects to Analog Output pin of the Gas sensor.

## Usage
1. Either download this repository or git clone using `$ git clone https://github.com/BurraAbhishek/toxic_place_detection.git`.
2. The source code is in [src/toxicdetection.ino](https://github.com/BurraAbhishek/toxic_place_detection/blob/main/src/toxicdetection.ino). Open it using an Arduino IDE.
3. Connect the Arduino board to your local machine using an Arduino-compatible USB Cable.
4. Set the appropriate port number in the Arduino IDE (One port will be displayed, for example, `COM1`)
5. Compile the program and run it.
6. To use battery power instead of USB power, shift the jumper in the Arduino board from USB to EXT (External power). The jumper is located next to the USB slot.


## LICENSE

The source code is licensed under the Terms of the [MIT License](https://github.com/BurraAbhishek/toxic_place_detection/blob/main/LICENSE).
