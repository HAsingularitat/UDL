#ifndef AHT20_HANDLER_H
#define AHT20_HANDLER_H

#include <Wire.h>
#include "AHT20.h"

// Create an instance of the AHT20 sensor
AHT20 aht;

// Initialize the AHT20 sensor
bool initAHT20() {
    // Initialize the sensor and check if it is connected
    if (!aht.begin()) {
        Serial.println("Failed to initialize AHT20 sensor, check wiring!");
        return false;
    }
    
    Serial.println("AHT20 sensor initialized successfully");
    return true;
}

// Read data from AHT20 and return as a comma-separated string
String getAHT20Data() {
    float humidity, temperature;

    // Get sensor data
    int ret = aht.getSensor(&humidity, &temperature);

    // Check if data retrieval was successful
    if (ret) {
        // Create a comma-separated string of all measurement data
        String dataString = String(humidity * 100) + "," + String(temperature);
        return dataString;
    } else {
        Serial.println("Failed to get data from AHT20 sensor");
        return "Error";
    }
}

#endif
