#ifndef ALPHASENSE_NO2_HANDLER_H
#define ALPHASENSE_NO2_HANDLER_H

#include <Adafruit_ADS1015.h>

// Create an instance of the ADS1115
Adafruit_ADS1115 ads;

// Constants for Alphasense NO2 sensor
const int OP1NO2_PIN = 0; // ADS1115 channel 0
const int OP2NO2_PIN = 1; // ADS1115 channel 1

// Calibration constants for the NO2 sensor
const double WE1NO2 = 0.230;
const double AUX1NO2 = 0.230;
const double SENSINO2 = 0.165;

// Initialize the ADS1115 for Alphasense NO2 sensor
bool initAlphasenseNO2() {
    ads.setGain(GAIN_TWOTHIRDS); // Gain of 2/3 for +-6.144V
    if (!ads.begin()) {
        Serial.println("Failed to initialize ADS1115 for Alphasense NO2 sensor!");
        return false;
    }
    Serial.println("ADS1115 initialized successfully for Alphasense NO2 sensor");
    return true;
}

// Read NO2 level from the Alphasense sensor
double readNO2Level() {
    int16_t datoNO2 = ads.readADC_SingleEnded(OP1NO2_PIN);
    double WENO2 = ((datoNO2 * 3.2) / 4096) - WE1NO2;

    int16_t dato1NO2 = ads.readADC_SingleEnded(OP2NO2_PIN);
    double AUXNO2 = ((dato1NO2 * 3.2) / 4096) - AUX1NO2;

    double ppbNO2 = (WENO2 - AUXNO2) / SENSINO2;
    return ppbNO2;
}

#endif
