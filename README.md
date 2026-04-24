# Anti-Theft Smart Backpack System

An IoT-based anti-theft backpack system built using ESP32 and MPU6050 motion sensor to detect unauthorized movement and alert the user.

## Features
- Motion detection using MPU6050 sensor
- Real-time alert system using buzzer
- Bluetooth connectivity for mobile interaction
- Portable power system using TP4056 and MT3608 modules

## Hardware Components
- ESP32
- MPU6050 Motion Sensor
- Buzzer
- TP4056 Charging Module
- MT3608 Boost Converter
- Battery Pack

## Circuit Connections
- MPU6050 VCC → ESP32 3V3  
- MPU6050 GND → ESP32 GND  
- MPU6050 SDA → ESP32 GPIO21  
- MPU6050 SCL → ESP32 GPIO22  
- Buzzer (+) → ESP32 GPIO25  
- Buzzer (-) → ESP32 GND  
- Power via TP4056 + MT3608 module  

## Working
The MPU6050 sensor detects motion and sends data to the ESP32.  
If unusual movement is detected, the system triggers a buzzer alert and communicates with a mobile device via Bluetooth.

## Companion App
The system connects to a mobile application via Bluetooth for monitoring and interaction.

(App link available in app_link.txt)

## Tech Stack
Embedded C, Arduino IDE, ESP32, IoT

## Additional Resources
- Project Presentation: Anti-Theft-Backpack-Presentation.pptx
