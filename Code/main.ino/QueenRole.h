#ifndef QUEEN_ROLE_H
#define QUEEN_ROLE_H

#include <Arduino.h>
#include "EEPROMHandler.h"
#include "SensorModules.h"
#include "Config.h"
#include "RTCInternalHandler.h"
#include "DeepSleepHandler.h"
#include "SDHandler.h"
#include "ESPNowCommunication.h"
#include "NetworkManagement.h"

// Define nombres de archivo
#define DATA_FILENAME "/datos.csv"
#define METADATA_FILENAME "/metadata.csv"

// Instancias de manejadores necesarios
RTCInternalHandler rtcHandler;
DeepSleepHandler sleepHandler;
SDHandler sdHandler;
NetworkManager networkManager;

class QueenRole {
private:
    unsigned long previousMillis = 0; // Para control del tiempo sin delay
    const unsigned long dataRequestInterval = 60000; // Intervalo para solicitar datos (1 minuto)
    const unsigned long timeSyncInterval = 300000; // Intervalo para sincronización de tiempo (5 minutos)
    unsigned long lastDataRequestTime = 0;
    unsigned long lastTimeSyncTime = 0;

public:
    void setup() {
        Serial.begin(115200);

        // Inicializar EEPROM y verificar configuración
        initEEPROM(1024);
        ModuleConfig currentConfig = readModuleConfig();
        
        if (String(currentConfig.subBoardId) != String(config.subBoardId)) {
            // Si no coincide, guardar configuración inicial
            writeModuleConfig(config);
            Serial.println("Configuration saved to EEPROM");
        }

        // Inicializar la tarjeta SD
        if (!sdHandler.begin()) {
            Serial.println("Failed to initialize SD card");
            return;
        }

        // Imprimir la razón del despertar
        sleepHandler.printWakeupReason();

        // Configurar el RTC interno
        rtcHandler.setUnixTime(1609459200); // Ajuste inicial del tiempo

        // Revisar si es hora de entrar en deep sleep
        int currentHour = rtcHandler.getTimeStruct().tm_hour;
        if (sleepHandler.shouldEnterSleep(currentHour)) {
            sleepHandler.enterDeepSleep();
        }

        // Configurar ESP-NOW
        initESPNow();
        esp_now_register_recv_cb(onDataRecv);
    }

    void loop() {
        unsigned long currentMillis = millis();

        // Solicitar datos de cada dispositivo
        if (currentMillis - lastDataRequestTime >= dataRequestInterval) {
            lastDataRequestTime = currentMillis;
            requestDataFromAllDevices();
        }

        // Sincronización de tiempo con todos los dispositivos
        if (currentMillis - lastTimeSyncTime >= timeSyncInterval) {
            lastTimeSyncTime = currentMillis;
            sendTimeSyncToAllDevices();
        }

        // Ejecutar otras tareas no bloqueantes aquí
    }

    // Solicitar datos de todos los dispositivos
    void requestDataFromAllDevices() {
        String macList = networkManager.getAllMacAddresses();
        // Convertir la lista de MACs en un arreglo de direcciones MAC
        std::vector<String> macs = splitString(macList, '\n');
        for (const String &macStr : macs) {
            uint8_t mac[6];
            parseMacAddress(macStr, mac);
            sendData(mac, CMD_DATA_REQUEST_TOTAL, "");
            Serial.println("Requested data from: " + macStr);
        }
    }

    // Enviar sincronización de tiempo a todos los dispositivos
    void sendTimeSyncToAllDevices() {
        String macList = networkManager.getAllMacAddresses();
        std::vector<String> macs = splitString(macList, '\n');
        String currentTime = String(rtcHandler.getUnixTime());
        for (const String &macStr : macs) {
            uint8_t mac[6];
            parseMacAddress(macStr, mac);
            sendData(mac, CMD_TIME_SYNC, currentTime);
            Serial.println("Sent time sync to: " + macStr);
        }
    }

    // Función para manejar la recepción de datos
    static void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
        uint8_t command;
        String data;
        decodeMessage(incomingData, len, command, data);

        switch (command) {
            case CMD_DATA_RESPONSE:
                handleDataResponse(mac, data);
                break;
            case CMD_METADATA_RESPONSE:
                handleMetadataResponse(mac, data);
                break;
            default:
                Serial.println("Received an unknown command");
                break;
        }
    }

    // Manejar la respuesta de datos de un dispositivo
    static void handleDataResponse(const uint8_t *senderMac, const String &data) {
        // Convertir MAC a string para el nombre del archivo
        String filename = macToString(senderMac) + ".csv";
        sdHandler.logData(filename, data);
        Serial.println("Data received and logged from: " + macToString(senderMac));
    }

    // Manejar la respuesta de metadatos de un dispositivo
    static void handleMetadataResponse(const uint8_t *senderMac, const String &metadata) {
        // Registrar metadatos en METADATA_FILENAME
        sdHandler.logData(METADATA_FILENAME, macToString(senderMac) + "," + metadata);
        Serial.println("Metadata received and logged from: " + macToString(senderMac));
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

    static void parseMacAddress(const String &macStr, uint8_t *mac) {
        int values[6];
        if (6 == sscanf(macStr.c_str(), "%x:%x:%x:%x:%x:%x", 
                        &values[0], &values[1], &values[2], 
                        &values[3], &values[4], &values[5])) {
            for (int i = 0; i < 6; ++i) {
                mac[i] = (uint8_t)values[i];
            }
        }
    }

    // División de una cadena en función de un delimitador
    static std::vector<String> splitString(const String &str, char delimiter) {
        std::vector<String> tokens;
        String token;
        for (char c : str) {
            if (c == delimiter) {
                if (!token.isEmpty()) {
                    tokens.push_back(token);
                    token = "";
                }
            } else {
                token += c;
            }
        }
        if (!token.isEmpty()) {
            tokens.push_back(token);
        }
        return tokens;
    }
};

#endif

/*
 * Uso en el sketch principal
 *
#include "QueenRole.h"

QueenRole queen;

void setup() {
    queen.setup();
}

void loop() {
    queen.loop();
}
 *
 */
