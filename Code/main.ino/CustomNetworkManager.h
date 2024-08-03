#ifndef CUSTOM_NETWORK_MANAGER_H
#define CUSTOM_NETWORK_MANAGER_H

#include <vector>
#include "Roles.h"

struct Device {
    uint8_t mac[6];
    Role role;
};

class CustomNetworkManager {
private:
    std::vector<Device> devices;

public:
    void addDevice(const uint8_t *mac, Role role) {
        Device newDevice;
        memcpy(newDevice.mac, mac, 6);
        newDevice.role = role;
        devices.push_back(newDevice);
    }

    void updateDeviceRole(const uint8_t *mac, Role newRole) {
        for (auto &device : devices) {
            if (memcmp(device.mac, mac, 6) == 0) {
                device.role = newRole;
                break;
            }
        }
    }

    bool isDeviceInNetwork(const uint8_t *mac) {
        for (const auto &device : devices) {
            if (memcmp(device.mac, mac, 6) == 0) {
                return true;
            }
        }
        return false;
    }

    Role getDeviceRole(const uint8_t *mac) {
        for (const auto &device : devices) {
            if (memcmp(device.mac, mac, 6) == 0) {
                return device.role;
            }
        }
        return PAWN; // Retornar PAWN por defecto si no se encuentra
    }
};

#endif
