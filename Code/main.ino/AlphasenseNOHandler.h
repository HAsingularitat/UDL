#ifndef ALPHASENSE_NO_HANDLER_H
#define ALPHASENSE_NO_HANDLER_H

#include <Adafruit_ADS1015.h>

// Create an instance of the ADS1115
Adafruit_ADS1115 ads;

// Constants for Alphasense NO sensor
const int OP1NO_PIN = 2; // ADS1115 channel 2
const int OP2NO_PIN = 3; // ADS1115 channel 3

// Calibration constants for the NO sensor
const double WE1NO = 0.270;
const double AUX1NO = 0.270;
const double SENSINO = 0.432;

// Initialize the ADS1115 for Alphasense NO sensor
bool initAlphasenseNO() {
    ads.setGain(GAIN_TWOTHIRDS); // Gain of 2/3 for +-6.144V
    if (!ads.begin()) {
        Serial.println("Failed to initialize ADS1115 for Alphasense NO sensor!");
        return false;
    }
    Serial.println("ADS1115 initialized successfully for Alphasense NO sensor");
    return true;
}

// Read NO level from the Alphasense sensor
double readNOLevel() {
    int16_t datoNO = ads.readADC_SingleEnded(OP1NO_PIN);
    double WENO = ((datoNO * 3.2) / 4096) - WE1NO;

    int16_t dato1NO = ads.readADC_SingleEnded(OP2NO_PIN);
    double AUXNO = ((dato1NO * 3.2) / 4096) - AUX1NO;

    double ppbNO = (WENO - AUXNO) / SENSINO;
    return ppbNO;
}

#endif
