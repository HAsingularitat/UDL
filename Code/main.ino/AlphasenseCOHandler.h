#ifndef ALPHASENSE_CO_HANDLER_H
#define ALPHASENSE_CO_HANDLER_H

#include <Adafruit_ADS1015.h>

// Create an instance of the ADS1115
Adafruit_ADS1115 ads;

// Constants for Alphasense CO sensor
const int OP1CO_PIN = 0; // ADS1115 channel 0
const int OP2CO_PIN = 1; // ADS1115 channel 1

// Calibration constants for the CO sensor
const double WE1CO = 0.330;
const double AUX1CO = 0.340;
const double SENSICO = 0.336;

// Initialize the ADS1115 for Alphasense CO sensor
bool initAlphasenseCO() {
    ads.setGain(GAIN_TWOTHIRDS); // Gain of 2/3 for +-6.144V
    if (!ads.begin()) {
        Serial.println("Failed to initialize ADS1115 for Alphasense CO sensor!");
        return false;
    }
    Serial.println("ADS1115 initialized successfully for Alphasense CO sensor");
    return true;
}

// Read CO level from the Alphasense sensor
double readCOLevel() {
    int16_t datoCO = ads.readADC_SingleEnded(OP1CO_PIN);
    double WECO = ((datoCO * 3.2) / 4096) - WE1CO;

    int16_t dato1CO = ads.readADC_SingleEnded(OP2CO_PIN);
    double AUXCO = ((dato1CO * 3.2) / 4096) - AUX1CO;

    double ppbCO = (WECO - AUXCO) / SENSICO;
    return ppbCO;
}

#endif
