# Hydroponics-System
Arduino | IOT | pH | turbidity | Temp

This is a simple hydroponics system Arduino code which will measure pH, Turbidity and Temperature for monitoring of water.

Project Overview: 
This project is an ESP32-based system that reads data from three different sensors:
✅ DS18B20 – Temperature Sensor (OneWire Protocol)
✅ Turbidity Sensor – Measures water clarity (analog input)
✅ pH Sensor – Measures the pH level of water (analog input)
✅ esp32 Sensor - Which will connect all three sensors to measure the data

The ESP32 collects sensor data, processes it, and outputs the calibrated results through the serial monitor. The code is designed for real-time water quality monitoring, making it suitable for hydroponics, aquaponics, and water treatment applications.

Hardware Requirements: 
Sensor	Pin Connection	Protocol	Notes
1) DS18B20 Temperature Sensor	GPIO 23	OneWire	Requires 4.7kΩ pull-up resistor
2) Turbidity Sensor	GPIO 34	Analog (ADC1)	Outputs voltage based on turbidity
3) pH Sensor	GPIO 35	Analog (ADC1)	Outputs voltage based on pH level

Calibration: 
✅ Turbidity Calibration
adcCleanWater → ADC value for 0 NTU
adcMaxTurbid → ADC value for 15 NTU
✅ pH Calibration
neutralVoltage → Voltage at pH 7.0
acidVoltage → Voltage at pH 4.0
baseVoltage → Voltage at pH 10.0
⚠️ Manually adjust these values based on actual sensor output for accurate calibration.
