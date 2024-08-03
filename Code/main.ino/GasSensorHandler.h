#ifndef GAS_SENSOR_HANDLER_H
#define GAS_SENSOR_HANDLER_H

#include <HardwareSerial.h>

class GasSensor {
private:
    HardwareSerial* port;
    int rxPin;
    int txPin;

public:
    GasSensor(int uartNumber) {
        if (uartNumber == 1) {
            port = &Serial1;
        } else if (uartNumber == 2) {
            port = &Serial2;
        }
    }

    void begin(int rx, int tx, long baudRate = 9600) {
        rxPin = rx;
        txPin = tx;
        port->begin(baudRate, SERIAL_8N1, rxPin, txPin);
    }

    String sendCommand(const byte* command, size_t commandSize) {
        port->write(command, commandSize);
        delay(500); // Wait for sensor response

        if (port->available() >= 9) {
            byte response[9];
            port->readBytes(response, 9);

            if (response[0] == 0xFF && response[1] == command[2]) { // Check command byte
                int highByte = response[2];
                int lowByte = response[3];
                int gasConcentration = highByte * 256 + lowByte;
                return String(gasConcentration) + " ppm";
            } else {
                return "Invalid sensor response";
            }
        }
        return "No response from sensor";
    }

    // Métodos específicos para leer diferentes gases
    String readCO() {
        byte cmd[] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
        return sendCommand(cmd, sizeof(cmd));
    }

    String readO2() {
        byte cmd[] = {0xFF, 0x01, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7B};
        return sendCommand(cmd, sizeof(cmd));
    }

    // Agrega más métodos aquí para otros gases si es necesario
};

#endif
/*

#include "GasSensorHandler.h"

GasSensor gasSensor(1); // Configura usando UART1

void setup() {
    Serial.begin(115200);
    gasSensor.begin(27, 14); // Configura los pines RX y TX
}

void loop() {
    // Lee la concentración de CO y la imprime
    String coConcentration = gasSensor.readCO();
    Serial.println("CO Concentration: " + coConcentration);
    delay(10000); // Espera 10 segundos antes de la próxima lectura
}

*/