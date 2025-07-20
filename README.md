# temperature-based-heater
This project is a smart heater controller based on the DS18B20 temperature sensor. It automatically turns a heater ON/OFF based on the current ambient temperature, displays the real-time data on an OLED screen, and alerts the user through a buzzer in case of overheating.

This embedded system project uses:
A DS18B20 digital temperature sensor to monitor temperature.
A transistor or MOSFET to switch the heater ON/OFF.
A buzzer to alert in case of overheating.
An OLED display to show temperature, status, and heater state.
A status LED to indicate heater status.


| Component                                   | Quantity |
| ------------------------------------------- | -------- |
| Esp32                                       | 1        |
| DS18B20 temperature sensor                  | 1        |
| Adafruit SSD1306 OLED (128x64)              | 1        |
| Transistor or MOSFET (e.g., IRF540N)        | 1        |
| Buzzer (active/passive)                     | 1        |
| LED (for heater indication)                 | 1        |
| 4.7kΩ resistor (for DS18B20)                | 1        |
| Jumper wires & Breadboard                   | -        |
| Heater (low-voltage resistive type)         | 1        |
| Power Supply (5V/12V as required by heater) | 1        |

circuit connections

| Arduino Pin | Component        |                        
| ----------- | ---------------- |
| D4          | DS18B20 Data Pin | 
| D5          | Heater Control   | 
| D14         | Heater LED       | 
| D15         | Buzzer           | 
| SDA, SCL    | OLED Display     | 
| GND, 5V     | All components   | 

The system reads temperature and responds based on preset ranges
| Temperature (°C) | Heater | Buzzer | Status Message |
| ---------------- | ------ | ------ | -------------- |
| < 15.0           | OFF    | OFF    | IDLE           |
| 15.0 – 17.9      | ON     | OFF    | HEATING        |
| 18.0 – 21.9      | ON     | OFF    | STABILIZING    |
| 22.0 – 24.9      | ON     | OFF    | TARGET REACHED |
| ≥ 25.0           | OFF    | ON     | OVERHEAT!      |
note: temperature ranges can be customised according to our requirements

out put
Temp: Displays current temperature in °C
Status: Shows current system state (e.g., HEATING, OVERHEAT!)
Heater: ON/OFF


