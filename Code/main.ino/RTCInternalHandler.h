#ifndef RTC_INTERNAL_HANDLER_H
#define RTC_INTERNAL_HANDLER_H

#include <ESP32Time.h>

class RTCInternalHandler {
private:
    ESP32Time rtc;               // Instancia principal de tiempo para UTC
    ESP32Time rtcGMTPlus1;       // Instancia para GMT+1
    ESP32Time rtcGMTMinus1;      // Instancia para GMT-1

public:
    // Constructor que configura los diferentes RTC con sus offsets
    RTCInternalHandler() {
        rtc.setTimeOffset(0);              // UTC
        rtcGMTPlus1.setTimeOffset(3600);   // GMT+1
        rtcGMTMinus1.setTimeOffset(-3600); // GMT-1
    }

    // Ajustar la hora del RTC usando tiempo Unix para todas las instancias
    void setUnixTime(time_t unixTime) {
        rtc.setTime(unixTime);             // Establece el mismo tiempo Unix base para todas las instancias
        rtcGMTPlus1.setTime(unixTime);
        rtcGMTMinus1.setTime(unixTime);
    }

    // Obtener la hora actual en formato personalizado para cualquier instancia
    String getTime(const String& format = "%A, %B %d %Y %H:%M:%S", int timeZone = 0) {
        switch (timeZone) {
            case 1:
                return rtcGMTPlus1.getTime(format);
            case -1:
                return rtcGMTMinus1.getTime(format);
            default:
                return rtc.getTime(format);
        }
    }

    // Métodos adicionales para manipular y obtener otras partes del tiempo
    // Podrías añadir métodos específicos para manipular y recuperar alarmas, segundos, etc.

    // Método para formatear el tiempo usando opciones específicas
    String formatTime(const char* format, int timeZone = 0) {
        struct tm timeinfo;
        switch (timeZone) {
            case 1:
                timeinfo = rtcGMTPlus1.getTimeStruct();
                break;
            case -1:
                timeinfo = rtcGMTMinus1.getTimeStruct();
                break;
            default:
                timeinfo = rtc.getTimeStruct();
                break;
        }
        char buffer[64];
        strftime(buffer, sizeof(buffer), format, &timeinfo);
        return String(buffer);
    }
};

#endif


/*

#include "RTCInternalHandler.h"

RTCInternalHandler rtcHandler;

void setup() {
    Serial.begin(115200);
    rtcHandler.setUnixTime(1609459200);  // Ajusta la hora inicial para todas las zonas
}

void loop() {
    Serial.println(rtcHandler.getTime("%A, %B %d %Y %H:%M:%S", 0));  // UTC
    Serial.println(rtcHandler.getTime("%A, %B %d %Y %H:%M:%S", 1));  // GMT+1
    Serial.println(rtcHandler.getTime("%A, %B %d %Y %H:%M:%S", -1)); // GMT-1
    delay(1000);
}


*/