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


For the sensors which show low reading in hazardous environments and high reading in safe environments:
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
1. Either download this repository or git clone using 
   ```
   $ git clone https://github.com/BurraAbhishek/toxic_place_detection.git
   ```
3. The source code is in [src/toxicdetection.ino](https://github.com/BurraAbhishek/toxic_place_detection/blob/main/src/toxicdetection.ino). Open it using an Arduino IDE.
4. Connect the Arduino board to your local machine using an Arduino-compatible USB Cable.
5. Set the appropriate port number in the Arduino IDE (One port will be displayed, for example, `COM1`)
6. Compile the program and run it.
7. To use battery power instead of USB power, shift the jumper in the Arduino board from USB to EXT (External power). The jumper is located next to the USB slot.


## Test Simulation
A simulation of the above is hosted on [Tinkercad](https://www.tinkercad.com/). To see a demo of how this program runs, check https://www.tinkercad.com/things/28n51KBNIkE, a functional version (remix) of the [above prototype](https://github.com/BurraAbhishek/toxic_place_detection#module-diagram). 

NOTE: The code on Tinkercad is different from the code in this repository. This is because Tinkercad supports only one kind of gas sensor which has a different interfacing code.

Testing:
1. Go to https://www.tinkercad.com/things/28n51KBNIkE.
2. Click on the 'Simulate' button and wait for the program to load.
3. To test the working, click on 'Start Simulation'.
4. Wait for 20 seconds. Then, click on the sensor. Black gas clouds should be visible somewhere in the test area.
5. To experiment with hazardous environment, drag the gas clouds closer to the sensor.

## LICENSE

- The source code in this repository is licensed under the Terms of the [MIT License](https://github.com/BurraAbhishek/toxic_place_detection/blob/main/LICENSE).

## References

[[1] Doukas, Charalampos & Maglogiannis, Ilias. (2012). Bringing IoT and Cloud Computing towards Pervasive Healthcare. Proceedings - 6th International Conference on Innovative Mobile and Internet Services in Ubiquitous Computing, IMIS 2012. 922-926. 10.1109/IMIS.2012.26.](https://www.researchgate.net/publication/261431852_Bringing_IoT_and_Cloud_Computing_towards_Pervasive_Healthcare)

[[2]Kinnera, Bharath Kumar Sai & Subbareddy, Somula & Luhach, Ashish. (2019). IOT based Air Quality Monitoring System Using MQ135 and MQ7 with Machine Learning Analysis. Scalable Computing: Practice and Experience. 20. 599-606. 10.12694/scpe.v20i4.1561.](https://www.researchgate.net/publication/337780520_IOT_based_Air_Quality_Monitoring_System_Using_MQ135_and_MQ7_with_Machine_Learning_Analysis)

[[3]Kinnera, Bharath Kumar Sai & Mukherjee, Subhaditya & Sultana, Parveen. (2019). Low Cost IoT Based Air Quality Monitoring Setup Using Arduino and MQ Series Sensors With Dataset Analysis. Procedia Computer Science. 165. 322-327. 10.1016/j.procs.2020.01.043.](https://www.researchgate.net/publication/339543962_Low_Cost_IoT_Based_Air_Quality_Monitoring_Setup_Using_Arduino_and_MQ_Series_Sensors_With_Dataset_Analysis)

[[4]fs4-howmuch2.pdf (osha.gov)](https://www.osha.gov/sites/default/files/2019-03/fs4-howmuch2.pdf)

[[5]Sampling and Analytical Methods | Carbon Monoxide In Workplace Atmospheres (Direct-Reading Monitor) | Occupational Safety and Health Administration (osha.gov)](https://www.osha.gov/dts/sltc/methods/inorganic/id209/id209.html)

[[6]CDC - Immediately Dangerous to Life or Health Concentrations (IDLH): L.P.G. - NIOSH Publications and Products](https://www.cdc.gov/niosh/idlh/68476857.html)
