#ifndef ESPNOW_COMMUNICATION_H
#define ESPNOW_COMMUNICATION_H

#include <esp_now.h>
#include "MessageEncoding.h"
#include "NetworkManagement.h"

extern NetworkManager networkManager; // Se asume que el gestor de red está definido externamente

void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("Packet Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Failure");
}

void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
    uint8_t command;
    String data;
    decodeMessage(incomingData, len, command, data);

    Role role = networkManager.getDeviceRole(mac);

    switch (command) {
        case CMD_TIME_SYNC:
            if (role.canSyncTime) {
                handleTimeSync(data);
            }
            break;
        case CMD_ROLE_CHANGE:
            if (role.canChangeRoles) {
                handleRoleChange(mac, data);
            }
            break;
        case CMD_DATA_REQUEST_TOTAL:
            if (role.canInitiateCommunication) {
                handleDataRequest(mac, data);
            }
            break;
        case CMD_DISTRIBUTE_MACS:
            handleDistributeMacs(mac);
            break;
        default:
            Serial.println("Received an unknown command");
            break;
    }
}

void handleTimeSync(const String &timestamp) {
    Serial.println("Syncing time to: " + timestamp);
}

void handleRoleChange(const uint8_t *senderMac, const String &newRole) {
    Serial.println("Changing role as per command...");
}

void handleDataRequest(const uint8_t *senderMac, const String &data) {
    Serial.println("Handling data request...");
    String sensorData = "Sensor data"; // Simulación de datos
    sendData(senderMac, CMD_DATA_REQUEST_TOTAL, sensorData);
}

void handleDistributeMacs(const uint8_t *senderMac) {
    if (networkManager.getDeviceRole(senderMac) == QUEEN) {
        String macList = networkManager.getAllMacAddresses();
        broadcastData(CMD_DISTRIBUTE_MACS, macList);
    }
}

void broadcastData(uint8_t command, const String &data) {
    for (auto &device : networkManager.getDevices()) {
        sendData(device.mac, command, data);
    }
}

void sendData(const uint8_t* peerAddress, uint8_t command, const String& data) {
    uint8_t messageBuffer[250];
    size_t messageLength = encodeMessage(messageBuffer, sizeof(messageBuffer), command, data);
    if (messageLength > 0 && esp_now_send(peerAddress, messageBuffer, messageLength) == ESP_OK) {
        Serial.println("Data sent successfully");
    } else {
        Serial.println("Error sending data");
    }
}

#endif
