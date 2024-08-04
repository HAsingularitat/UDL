#ifndef ROOK_ROLE_H
#define ROOK_ROLE_H

#include <Arduino.h>
#include "EEPROMHandler.h"
#include "Config.h"
#include "ESPNowCommunication.h"

// Define el tamaño de la EEPROM interna para almacenar direcciones MAC
#define EEPROM_SIZE 512

// Máximo número de direcciones MAC para retransmitir
#define MAX_MACS 10

class RookRole {
private:
    uint8_t specificMacs[MAX_MACS][6]; // Lista de MACs específicas
    uint8_t queenMac[6]; // Dirección MAC de la Reina

public:
    void setup() {
        Serial.begin(115200);

        // Inicializar EEPROM y cargar direcciones MAC
        initEEPROM(EEPROM_SIZE);
        loadMacAddresses();

        // Configurar ESP-NOW
        initESPNow();
        esp_now_register_recv_cb(onDataRecv);

        Serial.println("Rook Role Initialized");
    }

    void loop() {
        // La Torre no tiene operaciones periódicas más allá de retransmitir mensajes
    }

    // Cargar direcciones MAC desde la EEPROM
    void loadMacAddresses() {
        // Cargar la MAC de la Reina y las MACs específicas de la EEPROM
        for (int i = 0; i < MAX_MACS; i++) {
            for (int j = 0; j < 6; j++) {
                specificMacs[i][j] = EEPROM.read(i * 6 + j);
            }
        }
        // Cargar la dirección MAC de la Reina
        for (int j = 0; j < 6; j++) {
            queenMac[j] = EEPROM.read(MAX_MACS * 6 + j);
        }
    }

    // Función para manejar la recepción de datos
    static void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
        uint8_t command;
        String data;
        decodeMessage(incomingData, len, command, data);

        switch (command) {
            case CMD_DATA_RELAY:
                handleDataRelay(mac, data);
                break;
            default:
                Serial.println("Received an unknown command");
                break;
        }
    }

    // Manejar la retransmisión de datos
    static void handleDataRelay(const uint8_t *senderMac, const String &data) {
        Serial.println("Relaying data from: " + macToString(senderMac));

        // Retransmitir a la Reina
        sendData(queenMac, CMD_DATA_RELAY, data);

        // Retransmitir a MACs específicas
        for (int i = 0; i < MAX_MACS; i++) {
            if (isMacAddressSet(specificMacs[i])) {
                sendData(specificMacs[i], CMD_DATA_RELAY, data);
            }
        }
    }

    // Comprobar si una dirección MAC está establecida
    static bool isMacAddressSet(const uint8_t *mac) {
        for (int i = 0; i < 6; i++) {
            if (mac[i] != 0) return true;
        }
        return false;
    }

    // Utilidades para conversión de MAC
    static String macToString(const uint8_t *mac) {
        String macStr = "";
        for (int i = 0; i < 6; i++) {
            if (mac[i] < 16) macStr += "0";
            macStr += String(mac[i], HEX);
            if (i < 5) macStr += ":";
        }
        return macStr;
    }
};

#endif

/*
 * Uso en el sketch principal
 *
#include "RookRole.h"

RookRole rook;

void setup() {
    rook.setup();
}

void loop() {
    rook.loop();
}
 *
 */
