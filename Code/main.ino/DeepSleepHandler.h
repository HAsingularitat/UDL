#ifndef DEEP_SLEEP_HANDLER_H
#define DEEP_SLEEP_HANDLER_H

#include <Arduino.h>
#include <ESP32Time.h>

// Definiciones para configuración
#define DEEP_SLEEP_WAKEUP_PIN GPIO_NUM_0  // Pin para el botón de activación
#define DEEP_SLEEP_START_HOUR 23          // Hora de inicio del Deep Sleep
#define DEEP_SLEEP_WAKE_HOUR 5            // Hora de finalización del Deep Sleep
#define uS_TO_S_FACTOR 1000000ULL         // Conversión de segundos a microsegundos

class DeepSleepHandler {
private:
    ESP32Time rtc; // Instancia del RTC interno
    gpio_num_t wakeupPin;
    int wakeHour;
    int sleepHour;

public:
    DeepSleepHandler()
        : wakeupPin(DEEP_SLEEP_WAKEUP_PIN),
          wakeHour(DEEP_SLEEP_WAKE_HOUR),
          sleepHour(DEEP_SLEEP_START_HOUR) {
        pinMode(wakeupPin, INPUT_PULLUP); // Configurar el pin del botón como entrada con pull-up interno
    }

    // Método para iniciar el modo Deep Sleep
    void enterDeepSleep() {
        // Calcular duración del sueño en segundos
        uint64_t sleepDurationSeconds = calculateSleepDuration();
        Serial.println("Entering Deep Sleep Mode...");
        Serial.printf("Sleeping for %llu seconds\n", sleepDurationSeconds);

        esp_sleep_enable_timer_wakeup(sleepDurationSeconds * uS_TO_S_FACTOR); // Configurar el despertador por tiempo
        esp_sleep_enable_ext0_wakeup(wakeupPin, 0);   // Configurar el despertador por botón (nivel bajo activa)
        esp_deep_sleep_start();                       // Iniciar el modo Deep Sleep
    }

    // Método para verificar si es hora de dormir
    bool shouldEnterSleep(int currentHour) {
        return (currentHour >= sleepHour || currentHour < wakeHour);
    }

    // Método para calcular la duración del sueño en segundos
    uint64_t calculateSleepDuration() {
        // Calcular cuánto tiempo debe dormir hasta la hora de despertar
        int currentHour = rtc.getTimeStruct().tm_hour;
        int currentMinute = rtc.getTimeStruct().tm_min;

        // Calcula el número de segundos desde la hora actual hasta la hora de despertar
        int wakeTimeInMinutes = wakeHour * 60; // Hora de despertar en minutos
        int currentTimeInMinutes = currentHour * 60 + currentMinute; // Hora actual en minutos

        if (currentHour >= sleepHour) {
            // Si ya es hora de dormir (o más tarde), calcula para el próximo día
            wakeTimeInMinutes += 24 * 60;
        }

        int sleepDurationMinutes = wakeTimeInMinutes - currentTimeInMinutes;
        return static_cast<uint64_t>(sleepDurationMinutes) * 60; // Convertir a segundos
    }

    // Método para determinar la razón del despertar
    void printWakeupReason() {
        esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
        switch (wakeup_reason)
        {
            case ESP_SLEEP_WAKEUP_TIMER: 
                Serial.println("Wakeup caused by timer");
                break;
            case ESP_SLEEP_WAKEUP_EXT0: 
                Serial.println("Wakeup caused by external signal using RTC_IO");
                break;
            default:
                Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason);
                rtc.setTime(30, 24, 15, 17, 1, 2021);  // Ejemplo de ajuste de tiempo
                break;
        }
    }
};

DeepSleepHandler sleepHandler; // Instancia global del manejador de Deep Sleep

#endif


/*

#include <Arduino.h>
#include "RTCInternalHandler.h"
#include "DeepSleepHandler.h"

RTCInternalHandler rtcHandler;

void setup() {
    Serial.begin(115200);
    sleepHandler.printWakeupReason();
    rtcHandler.setUnixTime(1609459200); // Ajusta la hora inicial si es necesario

    // Revisar si es hora de dormir
    int currentHour = rtcHandler.getTimeStruct().tm_hour;
    if (sleepHandler.shouldEnterSleep(currentHour)) {
        sleepHandler.enterDeepSleep();
    }
}

void loop() {
    // Ejecutar operaciones normales
    Serial.println("Device is awake");
    delay(1000);
}


*/