#ifndef EEPROM_HANDLER_H
#define EEPROM_HANDLER_H

#include <EEPROM.h>

// Define the structure to store in EEPROM
struct ModuleConfig {
  char subBoardId[9];   // 8 characters + null terminator
  char version[8];      // Version string
  uint8_t uartPins[2];  // UART pins: [rx, tx]
  uint8_t adcPins[4];   // ADC pins: [pin1, pin2], or 99 if not used
  char sensorList[50];  // Comma-separated list of sensors
  char macList[850];    // Comma-separated list of MAC addresses (50 * 17)
};

// Address where the configuration is stored
const int CONFIG_ADDRESS = 0;

// Initialize EEPROM with a specific size
void initEEPROM(int size) {
  EEPROM.begin(size);
}

// Read module configuration from EEPROM
ModuleConfig readModuleConfig() {
  ModuleConfig config;
  EEPROM.get(CONFIG_ADDRESS, config);
  return config;
}

// Write module configuration to EEPROM
void writeModuleConfig(const ModuleConfig& config) {
  EEPROM.put(CONFIG_ADDRESS, config);
  EEPROM.commit();
}

// Function to display module configuration for debugging
void printModuleConfig(const ModuleConfig& config) {
  Serial.println("Module Configuration:");
  Serial.print("SubBoard ID: ");
  Serial.println(config.subBoardId);
  Serial.print("Version: ");
  Serial.println(config.version);
  Serial.print("UART Pins: RX=");
  Serial.print(config.uartPins[0]);
  Serial.print(", TX=");
  Serial.println(config.uartPins[1]);
  Serial.print("ADC Pins: ");
  for (int i = 0; i < 4; i++) {
      Serial.print(config.adcPins[i]);
      if (i < 3) Serial.print(", ");
  }
  Serial.println();
  Serial.print("Sensor List: ");
  Serial.println(config.sensorList);
  Serial.print("MAC List: ");
  Serial.println(config.macList);
}

#endif
