# Clock and Temperature Project

This project uses a DS3231 RTC module to track and display time on a 1306 OLED display. It also measures temperature using an analog temperature sensor and allows users to set an alarm using a potentiometer. When the current time matches the set alarm, a piezo buzzer activates.

## Project Information

- **Author:** Victor Huke
- **Date:** 2024-10-10
- **Description:** The project demonstrates the integration of real-time clock and temperature display on an OLED screen, with a configurable alarm.

## Table of Contents
- [Project Information](#project-information)
- [Features](#features)
- [Components](#components)
- [Wiring Diagram](#wiring-diagram)
- [Setup and Installation](#setup-and-installation)
- [Code Overview](#code-overview)
- [Functions](#functions)
- [Usage](#usage)

## Features
- **Real-Time Clock (RTC):** Displays the current time in `hh:mm:ss` format.
- **Temperature Reading:** Reads temperature using an analog temperature module and displays it in Celsius.
- **Alarm Setting:** Set a minute-specific alarm using a potentiometer.
- **Alarm Trigger:** Activates a piezo buzzer when the alarm minute matches the RTC minute.
- **OLED Display Output:** Displays time and temperature on a 1306 OLED display.

## Components
- **Arduino (compatible microcontroller)**
- **DS3231 Real-Time Clock Module**
- **1306 OLED Display**
- **Analog Temperature Sensor**
- **Potentiometer**
- **Piezo Buzzer**
- **Push Button**

## Wiring Diagram
1. **RTC DS3231 Module**:
   - SDA to Arduino SDA
   - SCL to Arduino SCL
2. **1306 OLED Display**:
   - Connect SDA and SCL lines to Arduino's SDA and SCL pins.
3. **Analog Temperature Sensor**:
   - Signal pin to A0 on Arduino.
4. **Potentiometer**:
   - Connect center pin to A1 on Arduino.
5. **Piezo Buzzer**:
   - Positive to pin 9, negative to GND.
6. **Push Button**:
   - One pin to pin 8, other pin to GND.

## Setup and Installation
1. **Libraries**:
   - Install the following Arduino libraries via the Arduino Library Manager:
     - `RTClib` for DS3231 RTC.
     - `Wire` for I2C communication.
     - `U8glib` for OLED display.

2. **Upload the Code**:
   - Connect the Arduino to your computer and upload the code.

## Code Overview
The code initializes communication with the RTC and OLED display. It reads and formats time and temperature data, and manages alarm settings and display output. 

### Key Variables
- `tmpPin` - Analog pin for temperature sensor.
- `piezoPin` - Pin for the piezo buzzer.
- `buttonPin` - Pin for page-switching button.
- `potPin` - Analog pin for potentiometer to set alarm time.

### Functions
- **`getTime()`**: Retrieves time from the DS3231 module and formats it as a `String` in `hh:mm:ss` format.
- **`getTemp()`**: Reads the analog temperature sensor and calculates temperature in Celsius.
- **`oledWrite(txt1, txt2)`**: Writes `txt1` (time) and `txt2` (temperature or alarm setting) to the OLED display.
- **`button()`**: Manages page switching for alarm settings using a debounced push button.
- **`potMeter()`**: Reads the potentiometer value to set the alarm time.

## Usage
1. **Time Display**: By default, the OLED display shows the current time in `hh:mm:ss` format and temperature in Celsius.
2. **Alarm Setting**: Press the button to enter alarm-setting mode. Use the potentiometer to select the alarm minute.
3. **Alarm Activation**: When the alarm minute matches the current RTC minute, the piezo buzzer will sound.
4. **Switch Pages**: Use the button to toggle between time/temperature display and alarm-setting pages.

## License
MIT License
