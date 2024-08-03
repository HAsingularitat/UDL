#ifndef INTERNAL_EEPROM_HANDLER_H
#define INTERNAL_EEPROM_HANDLER_H

#include <EEPROM.h>

// Define the size of the internal EEPROM
const int INTERNAL_EEPROM_SIZE = 100;

// Define the structure to store in internal EEPROM
struct InternalConfig {
  char macAddress[18];  // MAC address of the ESP32 (17 characters + null terminator)
  char id[9];           // ID of the ESP32
  char version[6];      // Version string
  uint8_t uartPins[2];  // UART pins: [rx, tx]
  uint8_t adcPins[4];   // ADC pins: [pin1, pin2], or 99 if not used
  char sensorList[50];  // Comma-separated list of sensors
};

// Address where the configuration is stored
const int INTERNAL_CONFIG_ADDRESS = 0;

// Initialize internal EEPROM with a specific size
void initInternalEEPROM() {
  EEPROM.begin(INTERNAL_EEPROM_SIZE);
}

// Read internal configuration from EEPROM
InternalConfig readInternalConfig() {
  InternalConfig config;
  EEPROM.get(INTERNAL_CONFIG_ADDRESS, config);
  return config;
}

// Write internal configuration to EEPROM
void writeInternalConfig(const InternalConfig& config) {
  EEPROM.put(INTERNAL_CONFIG_ADDRESS, config);
  EEPROM.commit();
}

// Function to display internal configuration for debugging
void printInternalConfig(const InternalConfig& config) {
  Serial.println("Internal Configuration:");
  Serial.print("MAC Address: ");
  Serial.println(config.macAddress);
  Serial.print("ID: ");
  Serial.println(config.id);
  Serial.print("Version: ");
  Serial.println(config.version);
  Serial.print("UART Pins: RX=");
  Serial.print(config.uartPins[0]);
  Serial.print(", TX=");
  Serial.println(config.uartPins[1]);
  Serial.print("ADC Pins: ");
  Serial.print(config.adcPins[0]);
  Serial.print(", ");
  Serial.println(config.adcPins[1]);
  Serial.print("Sensor List: ");
  Serial.println(config.sensorList);
}

#endif
