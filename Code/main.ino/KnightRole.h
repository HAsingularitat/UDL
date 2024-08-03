#ifndef KNIGHT_ROLE_H
#define KNIGHT_ROLE_H

#include <Arduino.h>
#include "EEPROMHandler.h"
#include "SensorModules.h"
#include "Config.h"
#include "RTCInternalHandler.h"
#include "DeepSleepHandler.h"
#include "SDHandler.h"
#include "ESPNowCommunication.h"
#include "NetworkManagement.h"

// Define el nombre del archivo donde se almacenan los datos
#define DATA_FILENAME "/datos.csv"

// Instancias de manejadores necesarios
RTCInternalHandler rtcHandler;
DeepSleepHandler sleepHandler;
SDHandler sdHandler;
NetworkManager networkManager;

class KnightRole {
private:
    unsigned long previousMillis = 0; // Para control del tiempo sin delay
    const unsigned long interval = 60000; // Intervalo de 1 minuto

    // Prioridad para convertirse en Reina
#ifdef ROLE_KNIGHT_CLASS_1
    const int queenPriority = 3; // Menor prioridad
#elif defined(ROLE_KNIGHT_CLASS_2)
    const int queenPriority = 2; // Mayor prioridad
#endif

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

        // Comprueba si ha pasado el intervalo definido
        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis;

            // Recopilar datos de los sensores
            String sensorData = collectAllSensorData();

            // Obtener el timestamp actual
            String timestamp = rtcHandler.getTime("%Y-%m-%d %H:%M:%S");

            // Crear la entrada de registro
            String logEntry = timestamp + "," + sensorData;

            // Guardar datos en la tarjeta SD
            sdHandler.logData(DATA_FILENAME, logEntry);
        }

        // Ejecutar otras tareas no bloqueantes aquí

        // Revisar si necesita convertirse en Reina
        checkForQueenRoleChange();
    }

    // Función para manejar la recepción de datos
    static void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
        uint8_t command;
        String data;
        decodeMessage(incomingData, len, command, data);

        switch (command) {
            case CMD_TIME_SYNC:
                handleTimeSync(data);
                break;
            case CMD_DATA_REQUEST_TOTAL:
                handleDataRequest(mac);
                break;
            case CMD_ROLE_CHANGE:
                handleRoleChange(data);
                break;
            default:
                Serial.println("Received an unknown command");
                break;
        }
    }

    // Manejar la sincronización de tiempo
    static void handleTimeSync(const String &timestamp) {
        // Actualizar la hora del RTC interno
        rtcHandler.setUnixTime(timestamp.toInt());
        Serial.println("Time synchronized to: " + timestamp);
    }

    // Manejar la petición de datos
    static void handleDataRequest(const uint8_t *senderMac) {
        // Leer los datos más recientes del sensor
        String recentData = collectAllSensorData();

        // Enviar los datos a la Reina
        sendData(senderMac, CMD_DATA_REQUEST_TOTAL, recentData);
        Serial.println("Data sent to Queen: " + recentData);
    }

    // Manejar el cambio de rol
    static void handleRoleChange(const String &newRole) {
        Serial.println("Role change requested: " + newRole);
        // Implementar lógica para cambio de rol aquí
    }

    // Función para verificar si debe convertirse en Reina
    void checkForQueenRoleChange() {
        if (!networkManager.isQueenActive()) {
            int availableQueenPriority = networkManager.findHighestPriorityRoleAvailable();
            if (queenPriority <= availableQueenPriority) {
                Serial.println("This Knight can become the Queen.");
                networkManager.promoteToQueen();
                // Implementar la lógica para convertirse en Reina
            }
        }
    }
};

#endif

/*
 * Uso en el sketch principal
 *
#include "KnightRole.h"

KnightRole knight;

void setup() {
    knight.setup();
}

void loop() {
    knight.loop();
}
 *
 */
