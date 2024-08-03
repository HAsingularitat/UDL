#ifndef BATTERY_LEVEL_HANDLER_H
#define BATTERY_LEVEL_HANDLER_H

#include <Arduino.h>

class BatteryLevel {
private:
    int adcPin; // Ahora sólo se declara aquí
    float adcMaxValue = 4095.0;  // Máximo valor para ADC de 12 bits
    float voltageMax = 4.2;      // Máximo voltaje de batería
    float voltageMin = 3.7;      // Mínimo voltaje de batería
    float r1 = 100000.0;         // Resistencia R4 en ohmios
    float r2 = 27000.0;          // Resistencia R3 en ohmios

public:
    BatteryLevel() {}

    void begin(int pin) {
        adcPin = pin; // Configura el pin en el método begin
        analogSetPinAttenuation(adcPin, ADC_11db); // Configurar la atenuación para medir hasta 3.9V
    }

    String readBatteryLevel() {
        int adcValue = analogRead(adcPin);
        float measuredVoltage = adcValue * (3.9 / adcMaxValue); // Convertir el valor ADC a voltaje
        float batteryVoltage = measuredVoltage * (r1 + r2) / r2; // Calcular el voltaje real de la batería

        float batteryPercentage = (batteryVoltage - voltageMin) / (voltageMax - voltageMin) * 100;
        batteryPercentage = constrain(batteryPercentage, 0, 100); // Limitar el porcentaje entre 0 y 100

        return String(batteryPercentage) + "%";
    }
};

#endif
/*

#include "BatteryLevelHandler.h"

BatteryLevel battery; // Se instancia sin especificar el pin

void setup() {
    Serial.begin(115200);
    battery.begin(39); // Configurar el pin 39 aquí
}

void loop() {
    String batteryLevel = battery.readBatteryLevel();
    Serial.print("Battery Level: ");
    Serial.println(batteryLevel);
    delay(1000); // Leer cada segundo
}


*/