#ifndef SPS30_HANDLER_H
#define SPS30_HANDLER_H

#include <sps30.h>
#include <Wire.h>

// Initialize the SPS30 sensor
bool initSPS30() {
    int16_t ret;
    uint8_t auto_clean_days = 4;

    sensirion_i2c_init();

    // Probe the sensor until it is found
    while (sps30_probe() != 0) {
        Serial.println("SPS sensor probing failed");
        delay(500);
    }

    Serial.println("SPS sensor probing successful");

    // Set fan auto-cleaning interval
    ret = sps30_set_fan_auto_cleaning_interval_days(auto_clean_days);
    if (ret) {
        Serial.print("Error setting the auto-clean interval: ");
        Serial.println(ret);
        return false;
    }

    // Start measurement
    ret = sps30_start_measurement();
    if (ret < 0) {
        Serial.println("Error starting measurement");
        return false;
    }

    Serial.println("Measurements started");
    return true;
}

// Read data from SPS30 and return as a comma-separated string
String getSPS30Data() {
    struct sps30_measurement m;
    uint16_t data_ready;
    int16_t ret;

    // Check if data is ready
    ret = sps30_read_data_ready(&data_ready);
    if (ret < 0) {
        Serial.print("Error reading data-ready flag: ");
        Serial.println(ret);
        return "Error";
    }
    if (!data_ready) {
        Serial.println("Data not ready, no new measurement available");
        return "NoData";
    }

    // Read measurement data
    ret = sps30_read_measurement(&m);
    if (ret < 0) {
        Serial.println("Error reading measurement");
        return "Error";
    }

    // Create a comma-separated string of all measurement data
    String dataString = String(m.mc_1p0) + "," + String(m.mc_2p5) + "," + String(m.mc_4p0) + "," + String(m.mc_10p0) + "," +
                        String(m.nc_0p5) + "," + String(m.nc_1p0) + "," + String(m.nc_2p5) + "," + String(m.nc_4p0) + "," +
                        String(m.nc_10p0) + "," + String(m.typical_particle_size);

    return dataString;
}

#endif
