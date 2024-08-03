#ifndef NETWORK_MANAGEMENT_H
#define NETWORK_MANAGEMENT_H

#include <vector>
#include <Arduino.h>
#include "Roles.h"
#include "EEPROMHandler.h"

struct Device {
    uint8_t mac[6];
    Role role;
};

class NetworkManager {
private:
    std::vector<Device> devices;
    ModuleConfig config;

public:
    NetworkManager() {
        initEEPROM(1024);  // Inicializar EEPROM con un tamaño adecuado
        config = readModuleConfig();  // Leer configuración existente
    }

    // Añadir un dispositivo a la red
    void addDevice(const uint8_t *mac, Role role) {
        if (!isDeviceInNetwork(mac)) {
            devices.push_back({{mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]}, role});
            saveMacToEEPROM(mac);
            Serial.println("Device added to network manager");
        }
    }

    // Actualizar el rol de un dispositivo
    void updateDeviceRole(const uint8_t *mac, Role newRole) {
        for (auto &device : devices) {
            if (memcmp(device.mac, mac, 6) == 0) {
                device.role = newRole;
                Serial.println("Device role updated");
                return;
            }
        }
        Serial.println("Device not found to update");
    }

    // Verificar si un dispositivo está en la red
    bool isDeviceInNetwork(const uint8_t *mac) {
        for (const auto &device : devices) {
            if (memcmp(device.mac, mac, 6) == 0) {
                return true;
            }
        }
        return false;
    }

    // Obtener el rol de un dispositivo
    Role getDeviceRole(const uint8_t *mac) {
        for (const auto &device : devices) {
            if (memcmp(device.mac, mac, 6) == 0) {
                return device.role;
            }
        }
        return PAWN; // Retorna PAWN por defecto si no se encuentra
    }

    // Obtener todas las direcciones MAC en la red
    String getAllMacAddresses() {
        String macList = "";
        for (const auto &device : devices) {
            for (int i = 0; i < 6; i++) {
                macList += String(device.mac[i], HEX);
                if (i < 5) macList += ":";
            }
            macList += "\n";
        }
        return macList;
    }

    // Comprobar si hay una Reina activa
    bool isQueenActive() {
        for (const auto &device : devices) {
            if (device.role == QUEEN) {
                return true;
            }
        }
        return false;
    }

    // Encontrar el rol de mayor prioridad disponible para ser Reina
    Role findHighestPriorityRoleAvailable() {
        Role highestPriority = PAWN; // Prioridad más baja por defecto

        for (const auto &device : devices) {
            if (device.role == PAWN) {
                return PAWN; // Prioridad más alta
            } else if (device.role == KNIGHT_2 && highestPriority != PAWN) {
                highestPriority = KNIGHT_2;
            } else if (device.role == KNIGHT_1 && highestPriority != PAWN && highestPriority != KNIGHT_2) {
                highestPriority = KNIGHT_1;
            }
        }
        return highestPriority;
    }

    // Promover un dispositivo al rol de Reina
    void promoteToQueen() {
        Role roleToPromote = findHighestPriorityRoleAvailable();
        for (auto &device : devices) {
            if (device.role == roleToPromote) {
                device.role = QUEEN;
                Serial.println("Promoted a device to Queen");
                break;
            }
        }
    }

private:
    // Guardar una dirección MAC en la EEPROM
    void saveMacToEEPROM(const uint8_t *mac) {
        // Convertir MAC a string
        String macStr = "";
        for (int i = 0; i < 6; i++) {
            if (mac[i] < 16) macStr += "0";
            macStr += String(mac[i], HEX);
            if (i < 5) macStr += ":";
        }

        // Comprobar si la MAC ya está en la lista
        if (String(config.macList).indexOf(macStr) == -1) {
            // Añadir nueva MAC a la lista
            strcat(config.macList, macStr.c_str());
            strcat(config.macList, ",");

            // Guardar en la EEPROM
            writeModuleConfig(config);
            Serial.println("MAC saved to EEPROM: " + macStr);
        }
    }
};

#endif
