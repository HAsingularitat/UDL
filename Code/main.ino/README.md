# UDL
# UDL Project - ESP32 Networked Sensor System

## Overview

This project consists of a networked sensor system using ESP32 modules, organized in a dynamic role-based architecture inspired by chess pieces (King, Queen, Rook, Bishop, Knight, Pawn). It leverages ESP-NOW for efficient communication, managing sensor data collection, and network coordination across multiple ESP32 units.

## Files and Modules Description

### Sensor Modules
- **ADS1115Handler.h**: Manages interactions with the ADS1115 ADC module.
- **AHT20Handler.h**: Interface for the AHT20 temperature and humidity sensor.
- **Alphasense Handlers**: Modules like `AlphasenseCOHandler.h`, `AlphasenseNO2Handler.h`, and `AlphasenseNOHandler.h` interface with respective gas sensors.
- **BMP280Handler.h**: Manages BMP280 sensor for reading atmospheric pressure and temperature.
- **BatteryLevelHandler.h**: Monitors and reports battery level using a voltage divider connected to an ADC.

### Communication and Network Management
- **ESPNowSetup.h** and **ESPNowCommunication.h**: Configure ESP-NOW communication, sending, and receiving data.
- **NetworkManagement.h** and **CustomNetworkManager.h**: Manage network roles, devices, and MAC addresses.

### Utility and Handler Modules
- **EEPROMHandler.h**: Manages reading and writing configurations and data to the internal EEPROM.
- **DeepSleepHandler.h**: Controls deep sleep cycles based on predefined schedules.
- **SDHandler.h** and **SDMMCHandler.h**: Handle logging of sensor data and other information to SD cards.

### Sensor Roles
- **Roles.h**: Defines various roles (King, Queen, Knight, etc.) and behaviors within the network.
- **QueenRole.h**, **PawnRole.h**, **KnightRole.h**, **RookRole.h**: Implement specific functionalities and behaviors according to the assigned role.

### Configuration and Setup
- **Config.h**: Central configuration file that defines system-wide settings and parameters.
- **main.ino**: The main entry point of the application, designed to be minimal and flexible depending on the role assigned at compile time.

## Features

- **Dynamic Role Assignment**: Allows devices to switch roles according to network needs or in response to certain events.
- **Data Redundancy and Recovery**: Critical data such as MAC addresses are stored redundantly across devices, enhancing reliability.
- **Energy Efficiency**: Utilizes deep sleep modes to conserve energy, with specific wake-up conditions defined by network activity or scheduled tasks.
- **Real-Time Data Handling**: Capable of handling real-time sensor data transmission, processing, and logging with minimal latency.
- **Expandability**: Designed to be easily expandable with additional sensor modules and functionalities without extensive modifications to the core system.

## Limitations

- **Memory Constraints**: Each ESP32 device has limited memory, which constrains the amount of data that can be stored or processed simultaneously.
- **Network Complexity**: As the number of devices in the network increases, managing communications and ensuring timely data transmission can become challenging.
- **Hardware Dependency**: Specific functionalities are tightly coupled with certain hardware components, making it difficult to substitute sensors or other hardware without modifying the code.

## Setup and Deployment

1. **Initial Configuration**: Set up each ESP32 with the necessary firmware and configure its role and parameters.
2. **Network Initialization**: Deploy multiple devices in their respective locations and power them up. They will automatically join the network and assume their configured roles.
3. **Monitoring and Maintenance**: Monitor the system through serial outputs or connect to a central server if configured to do so.

## Conclusion

This ESP32-based sensor network project leverages modular programming, role-based architecture, and efficient communication protocols to create a robust and versatile sensor network suitable for various applications from environmental monitoring to smart home systems.
