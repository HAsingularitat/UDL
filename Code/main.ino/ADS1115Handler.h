#ifndef ADS1115_HANDLER_H
#define ADS1115_HANDLER_H

#include <Wire.h>
#include <Adafruit_ADS1015.h>

// Create an instance of the ADS1115
Adafruit_ADS1115 ads;

// Initialize the ADS1115
bool initADS1115() {
    ads.setGain(GAIN_TWOTHIRDS);  // Set gain to +-6.144V (1 bit = 0.1875mV)
    if (!ads.begin()) {
        Serial.println("Failed to initialize ADS1115, check wiring!");
        return false;
    }
    
    Serial.println("ADS1115 initialized successfully");
    return true;
}

// Read data from a specific ADS1115 channel (0-3)
int16_t readADS1115Channel(uint8_t channel) {
    if (channel > 3) {
        Serial.println("Invalid ADS1115 channel!");
        return 0;
    }

    // Read the analog input from the specified channel
    int16_t adcValue = ads.readADC_SingleEnded(channel);
    Serial.print("ADS1115 Channel ");
    Serial.print(channel);
    Serial.print(": ");
    Serial.println(adcValue);

    return adcValue;
}

#endif
