#ifndef ESPNOW_SETUP_H
#define ESPNOW_SETUP_H

#include <esp_now.h>
#include <WiFi.h>

// Inicialización de ESP-NOW
void initESPNow() {
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
    } else {
        Serial.println("ESP-NOW initialized successfully");
    }
}

void addPeer(const uint8_t *peerAddress) {
    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, peerAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
    } else {
        Serial.println("Peer added successfully");
    }
}

#endif
