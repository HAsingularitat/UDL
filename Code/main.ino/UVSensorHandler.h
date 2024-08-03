#ifndef UV_SENSOR_HANDLER_H
#define UV_SENSOR_HANDLER_H

#include "ADS1115_Handler.h"
#include <Arduino.h>

// Descomenta la siguiente línea para usar ADS1115, de lo contrario se usará el ADC interno del ESP32
// #define USE_ADS1115

class UVSensor {
private:
    uint8_t adcPin;   // Pin ADC para el ADC interno
    uint8_t adsChannel; // Canal del ADS1115
    bool useADS1115;

public:
    UVSensor(uint8_t pinOrChannel, bool useExternalADC = false) 
    : adcPin(pinOrChannel), adsChannel(pinOrChannel), useADS1115(useExternalADC) {}

    void begin() {
        if (useADS1115) {
            initADS1115(); // Asegura que el ADS1115 está inicializado
        }
        // Configuración adicional para el ADC interno si es necesario
    }

    String readUVIndex() {
        int16_t uvReading = 0;
        float voltage = 0.0;
        if (useADS1115) {
            uvReading = readADS1115Channel(adsChannel);
            voltage = uvReading * (6.144 / 32767.0); // Conversión para ADS1115
        } else {
            uvReading = analogRead(adcPin);
            voltage = uvReading * (3.3 / 4095.0); // Conversión para ADC interno del ESP32
        }
        float uvIndex = voltage / 0.1; // Conversión de voltaje a índice UV
        return String(uvIndex);
    }
};

#endif
/*

#include "UVSensorHandler.h"

// Cambiar a true si deseas usar ADS1115, asegúrate de definir el pin o canal correctamente
UVSensor uvSensor(0, true); // Usar canal 0 del ADS1115

void setup() {
    Serial.begin(115200);
    uvSensor.begin();
}

void loop() {
    String uvIndex = uvSensor.readUVIndex();
    Serial.print("UV Index: ");
    Serial.println(uvIndex);
    delay(1000); // Leer cada segundo
}


*/