#include <OneWire.h>
#include <DallasTemperature.h>

// **Temperature Sensor (DS18B20) Setup**
const int oneWireBus = 23;   // DS18B20 data pin
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

// **Turbidity Sensor Setup**
#define TURBIDITY_SENSOR_PIN 34  // Turbidity sensor connected to ADC1 (GPIO 34)

// **pH Sensor Setup**
#define PH_SENSOR_PIN 35  // pH sensor connected to ADC1 (GPIO 35)
float neutralVoltage = 2.5;  // Voltage at pH 7.0
float acidVoltage = 2.0;      // Voltage at pH 4.0
float baseVoltage = 3.5;      // Voltage at pH 10.0

void setup() {
  Serial.begin(115200);
  
  // Initialize the DS18B20 temperature sensor
  sensors.begin();
  
  // Ensure ADC reads full range for pH sensor
  analogSetPinAttenuation(PH_SENSOR_PIN, ADC_11db);
}

void loop() {
  // **Read Temperature**
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);

  // **Read Turbidity**
  int turbidityValue = analogRead(TURBIDITY_SENSOR_PIN);
  float turbidityVoltage = turbidityValue * (3.3 / 4095.0);

  int adcCleanWater = 2500;  // ADC value for 0 NTU (clear water)
  int adcMaxTurbid = 1000;   // ADC value for 15 NTU (high turbidity)
  float turbidityNTU = map(turbidityValue, adcMaxTurbid, adcCleanWater, 15, 0);
  turbidityNTU = constrain(turbidityNTU, 0, 15);

  // **Read pH Sensor**
  int phSensorValue = analogRead(PH_SENSOR_PIN);
  float phVoltage = phSensorValue * (3.3 / 4095.0);

  if (phVoltage < 0.1) {
    Serial.println("⚠️ pH Sensor not detected or faulty! Check connections.");
  } else {
    float slope = (10.0 - 9) / (baseVoltage - acidVoltage);
    float phValue = 7.0 - (neutralVoltage - phVoltage) * slope;
    phValue = constrain(phValue, 0, 14);
  
    // **Print Data**
    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.println(" °C");

    Serial.print("Turbidity ADC Value: ");
    Serial.println(turbidityValue);
    Serial.print("Turbidity Voltage: ");
    Serial.print(turbidityVoltage, 3);
    Serial.println(" V");
    Serial.print("Turbidity: ");
    Serial.print(turbidityNTU);
    Serial.println(" NTU");

    Serial.print("pH Raw ADC Value: ");
    Serial.println(phSensorValue);
    Serial.print("pH Voltage: ");
    Serial.print(phVoltage, 3);
    Serial.println(" V");
    Serial.print("Calibrated pH: ");
    Serial.println(phValue, 2);
  }

  Serial.println("----------------------");
  delay(5000);  // Small delay before next reading
}
