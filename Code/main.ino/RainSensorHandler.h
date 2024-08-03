#ifndef RAIN_SENSOR_HANDLER_H
#define RAIN_SENSOR_HANDLER_H

#include "ADS1115_Handler.h"
#include <Arduino.h>

class RainSensor {
private:
    int pin;          // Pin para el ADC interno
    uint8_t channel;  // Canal del ADS1115
    bool useAnalog;   // Indica si se usa analógico
    bool useADS1115;  // Indica si se usa el ADC externo

public:
    RainSensor(int pinOrChannel, bool analog = false, bool externalADC = false) 
    : pin(pinOrChannel), channel(pinOrChannel), useAnalog(analog), useADS1115(externalADC) {}

    void begin() {
        if (useADS1115 && useAnalog) {
            initADS1115(); // Inicializa el ADS1115 si se usa
        } else if (!useAnalog) {
            pinMode(pin, INPUT); // Configura el pin como entrada digital si no es analógico
        }
    }

    String readRainStatus() {
        if (useAnalog) {
            int sensorValue = 0;
            if (useADS1115) {
                sensorValue = readADS1115Channel(channel);
                // Conversión a voltaje y decisión de lluvia
                float voltage = sensorValue * (6.144 / 32767.0);
                int threshold = 0.5; // Umbral de voltaje para detectar lluvia, ajusta según el sensor
                return (voltage < threshold) ? "Rain Detected" : "No Rain";
            } else {
                sensorValue = analogRead(pin);
                int threshold = 500; // Umbral de lectura analógica
                return (sensorValue < threshold) ? "Rain Detected" : "No Rain";
            }
        } else {
            int sensorState = digitalRead(pin);
            return (sensorState == LOW) ? "Rain Detected" : "No Rain";
        }
    }
};

#endif
/*
#include "RainSensorHandler.h"

// Cambiar a true si deseas usar salida analógica y ADS1115
RainSensor rainSensor(0, true, true); // Usar canal 0 del ADS1115

void setup() {
    Serial.begin(115200);
    rainSensor.begin();
}

void loop() {
    String rainStatus = rainSensor.readRainStatus();
    Serial.print("Rain Status: ");
    Serial.println(rainStatus);
    delay(1000); // Leer cada segundo
}


*/