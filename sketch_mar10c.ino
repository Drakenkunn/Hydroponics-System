#include <OneWire.h>
#include <DallasTemperature.h>

// **Temperature Sensor (DS18B20) Setup**
const int oneWireBus = 23;   // DS18B20 data pin
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

// **Turbidity Sensor Setup**
#define TURBIDITY_SENSOR_PIN 34  // Turbidity sensor connected to ADC1 (GPIO 34)

void setup() {
  Serial.begin(115200);
  
  // Initialize the DS18B20 temperature sensor
  sensors.begin();
}

void loop() {
  // **Read Temperature**
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);

  // **Read Turbidity**
  int sensorValue = analogRead(TURBIDITY_SENSOR_PIN);  
  float voltage = sensorValue * (3.3 / 4095.0);

  // **Turbidity Calibration** (Replace with actual values)
  int adcCleanWater = 2500;  // ADC value for 0 NTU (clear water)
  int adcMaxTurbid = 1000;   // ADC value for 15 NTU (high turbidity)

  float turbidityNTU = map(sensorValue, adcMaxTurbid, adcCleanWater, 15, 0);
  turbidityNTU = constrain(turbidityNTU, 0, 15);  // Ensure NTU is within range

  // **Print Data**
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  Serial.print("Turbidity ADC Value: ");
  Serial.println(sensorValue);

  Serial.print("Voltage: ");
  Serial.print(voltage, 3);
  Serial.println(" V");

  Serial.print("Turbidity: ");
  Serial.print(turbidityNTU);
  Serial.println(" NTU");

  Serial.println("----------------------");

  delay(2000);  // Small delay before next reading
}
