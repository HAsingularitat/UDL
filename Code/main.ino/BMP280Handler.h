#ifndef BMP280_HANDLER_H
#define BMP280_HANDLER_H

#include <Adafruit_BMP280.h>

// Create an instance of the BMP280 sensor
Adafruit_BMP280 bmp;

// Initialize the BMP280 sensor
bool initBMP280() {
    // Initialize I2C communication and check if the sensor is connected
    if (!bmp.begin()) {
        Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
        return false;
    }

    // Set sensor sampling settings
    bmp.setSampling(Adafruit_BMP280::MODE_FORCED,     /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_X2,     /* Temperature oversampling */
                    Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

    Serial.println(F("BMP280 sensor initialized successfully"));
    return true;
}

// Read data from BMP280 and return as a comma-separated string
String getBMP280Data() {
    // Take a forced measurement
    if (!bmp.takeForcedMeasurement()) {
        Serial.println("Forced measurement failed!");
        return "Error";
    }

    // Read the temperature, pressure, and approximate altitude
    float temperature = bmp.readTemperature();
    float pressure = bmp.readPressure();
    float altitude = bmp.readAltitude(1013.25); // Standard atmospheric pressure

    // Create a comma-separated string of all measurement data
    String dataString = String(temperature) + "," + String(pressure) + "," + String(altitude);

    return dataString;
}

#endif
