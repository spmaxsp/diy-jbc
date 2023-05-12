# DIY-JBC Station

## Introduction
My Interpretation of a Soldering Station for the T245 Handle and C245 Cartridge. The schematics are based on the [DIY-JBC-T245-Station](https://github.com/Muny/DIY-JBC-T245-Station) project.

---
**!Project is still in development!(some things may not be implemented yet)**

---
## Project Structure
Because I have not been able to fit my complete code on one Atmega328P I decided to split the project into two parts. The first part is the main controller for the station itself. The second part is the userinterface. The userinterface is a separate PCB with a Atmega328P and a 128x64 OLED Display. The two parts communicate via I2C.

The Project is compiled with the [PlatformIO](https://platformio.org/) IDE,  but it should also be possible to compile it with the Arduino IDE. (I try to keep the code as compatible as possible)

## Features
- PID Control
- Sleep Mode (sensing if the handle is in the stand)
- Standby Mode
- Serial Interface
- WS2812B RGB LED (for status/temperature indication)
- OLED Display (display current temperature, set temperature and power; settings menu; plot temperature graph)

### Serial Interface
The Station listen to the serial interface for commands. 
The commands are in the following format:

- "SET" Command: "SET <command> <value>" 

    "TEMP"
    "KP"
    "KI"
    "KD"
    "TC_A"
    "TC_B"
    "TC_C"
    "T_SLEEP"
    "T_HIBERNATE"
    "TMP_SLEEP"
    "TMP_HIBERNATE" 

- "ENABLE" Command: \
Enables the heating element

- "DISABLE" Command: \
Disables the heating element

- "SAVE" Command: \
Saves the current settings to the EEPROM

- "SETTINGS" Command: \
Prints the current settings to the serial interface

- "START" Command: \
Starts outputting the current temperature to the serial interface

- "STOP" Command: \
Stops outputting the current temperature to the serial interface

### Settings
- PID Settings  
- Temperature Calibration 
   (t_c = TC_A * t^2 + TC_B * t + TC_C)

- Sleep Temperature
- Standby Temperature
- Sleep Time
- Standby Time

## Hardware
- Atmega328P
- 128x64 OLED Display
- WS2812B RGB LED
- Encoder with Pushbutton
- Temperature Sensor (MAX6675)
- Power Control (Triac BTB26-600BRG)
- The Iron is powered by a 24V AC Transformer an the Logic is powered by a 5V DC PCB mount power supply
- The logic and the Power Control are isolated from each other

## Power Control
The Power Control is done by a Triac. The Triac is controlled by a zero-crossing detector. The software only lets a number of half-waves through, before it turns the Triac off again. Then it waits some time to get a stable temperature reading and then it turns the Triac on again, corresponding to the current PID output.

## Pinout of the Cartridge Connector
There is quite a discussion about the pinout of the cartridge connector. I firstly did some measurements like [this](http://adgd.ru/2021/01/04/jbc-soldering-cartridges-pinouts/). But there were quite a lot of people who augmented against it. Mostly because of [these pictures](https://www.eevblog.com/forum/projects/jbc-handle-cartridge-data/?action=dlattach;attach=1224739;image). 
In the end the pinout I used is the one described on this [EEVblog post](https://www.eevblog.com/forum/projects/jbc-handle-cartridge-data), because it has a plausible explanation for the contradicting measurements. (Also I tried both pinouts and both worked fine, so I don't think it really matters; if you look at the teardown of the tip, there is nothing that would prevent the tip from being plugged in the other way around)


