#ifndef MESSAGE_ENCODING_H
#define MESSAGE_ENCODING_H

#include <Arduino.h>

// Definir códigos para comandos específicos
enum Command {
    CMD_DATA_REQUEST_TOTAL = 0x01,
    CMD_TIME_SYNC = 0x02,
    CMD_ROLE_CHANGE = 0x03,
    CMD_ACKNOWLEDGE = 0x04,
    CMD_PING = 0x05,
    CMD_SENSOR_DATA_REQUEST = 0x06,
    CMD_DEVICE_STATUS_REQUEST = 0x07,
    CMD_RESET = 0x08,
    CMD_FIRMWARE_UPDATE = 0x09,
    CMD_DISTRIBUTE_MACS = 0x0A, // Nuevo comando para distribución de MACs
    CMD_CUSTOM = 0xFF
};

// Codificar un mensaje
size_t encodeMessage(uint8_t *buffer, size_t bufferSize, uint8_t command, const String &data) {
    if (bufferSize < data.length() + 2) {
        return 0; // Buffer insuficiente
    }

    buffer[0] = command;
    memcpy(&buffer[1], data.c_str(), data.length());
    buffer[data.length() + 1] = '\0';
    return data.length() + 2;
}

// Decodificar un mensaje
void decodeMessage(const uint8_t *buffer, size_t len, uint8_t &command, String &data) {
    if (len < 2) {
        return;
    }

    command = buffer[0];
    data = String((char*)&buffer[1], len - 1);
}

#endif
