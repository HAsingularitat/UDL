#ifndef NTC_HANDLER_H
#define NTC_HANDLER_H

#include <Wire.h>
#include <Adafruit_ADS1015.h>

// Create an instance of the ADS1115
Adafruit_ADS1115 ads;

// Constants for NTC thermistors
const double SERIES_RESISTOR = 100000.0; // 100k Ohm
const double NOMINAL_RESISTANCE = 100000.0; // 100k Ohm at 25 degrees C
const double NOMINAL_TEMPERATURE = 25.0; // 25 degrees C
const double BETA_COEFFICIENT = 3950.0; // Beta coefficient for the thermistor
const double KELVIN_OFFSET = 273.15; // Conversion from Celsius to Kelvin

// Uncomment these lines to activate specific NTC channels
#define USE_NTC1
#define USE_NTC2
//#define USE_NTC3
//#define USE_NTC4

// Define the ADS1115 channels for each NTC thermistor
const int NTC1_CHANNEL = 0; // Channel 0
const int NTC2_CHANNEL = 1; // Channel 1
const int NTC3_CHANNEL = 2; // Channel 2
const int NTC4_CHANNEL = 3; // Channel 3

// Initialize the ADS1115 for NTC thermistors
bool initNTC() {
    ads.setGain(GAIN_TWOTHIRDS); // Gain of 2/3 for +-6.144V
    if (!ads.begin()) {
        Serial.println("Failed to initialize ADS1115 for NTC thermistors!");
        return false;
    }
    Serial.println("ADS1115 initialized successfully for NTC thermistors");
    return true;
}

// Calculate temperature from ADC value
double calculateTemperature(int16_t adcValue) {
    double voltage = adcValue * 3.3 / 4096.0;
    double resistance = SERIES_RESISTOR / (3.3 / voltage - 1.0);
    double steinhart;
    
    steinhart = resistance / NOMINAL_RESISTANCE; // (R/Ro)
    steinhart = log(steinhart); // ln(R/Ro)
    steinhart /= BETA_COEFFICIENT; // 1/B * ln(R/Ro)
    steinhart += 1.0 / (NOMINAL_TEMPERATURE + KELVIN_OFFSET); // + (1/To)
    steinhart = 1.0 / steinhart; // Invert
    steinhart -= KELVIN_OFFSET; // Convert to Celsius

    return steinhart;
}

// Read temperatures from connected NTC thermistors and return as a comma-separated string
String readNTCTemperatures() {
    String temperatureString = "";

#ifdef USE_NTC1
    int16_t adcValue1 = ads.readADC_SingleEnded(NTC1_CHANNEL);
    double temperature1 = calculateTemperature(adcValue1);
    temperatureString += String(temperature1);
#endif

#ifdef USE_NTC2
    if (!temperatureString.isEmpty()) temperatureString += ",";
    int16_t adcValue2 = ads.readADC_SingleEnded(NTC2_CHANNEL);
    double temperature2 = calculateTemperature(adcValue2);
    temperatureString += String(temperature2);
#endif

#ifdef USE_NTC3
    if (!temperatureString.isEmpty()) temperatureString += ",";
    int16_t adcValue3 = ads.readADC_SingleEnded(NTC3_CHANNEL);
    double temperature3 = calculateTemperature(adcValue3);
    temperatureString += String(temperature3);
#endif

#ifdef USE_NTC4
    if (!temperatureString.isEmpty()) temperatureString += ",";
    int16_t adcValue4 = ads.readADC_SingleEnded(NTC4_CHANNEL);
    double temperature4 = calculateTemperature(adcValue4);
    temperatureString += String(temperature4);
#endif

    return temperatureString;
}

#endif
