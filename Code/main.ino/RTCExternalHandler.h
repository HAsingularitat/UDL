//
//
//            RTC_DS3231
//
//
//

#ifndef RTC_DS3231_HANDLER_H
#define RTC_DS3231_HANDLER_H

#include <Wire.h>
#include <RTClib.h>

class RTCDS3231Handler {
private:
    RTC_DS3231 rtc;

public:
    RTCDS3231Handler() {}

    bool begin() {
        if (!rtc.begin()) {
            Serial.println("Couldn't find RTC");
            return false;
        }
        if (!rtc.isrunning()) {
            Serial.println("RTC is NOT running!");
            // Configura el RTC con un tiempo Unix predeterminado si no está corriendo
            setUnixTime(1609459200); // Ejemplo: 1 de Enero de 2021
        }
        return true;
    }

    void setUnixTime(time_t unixTime) {
        rtc.adjust(DateTime(unixTime));
    }

    time_t getUnixTime() {
        return rtc.now().unixtime(); // Devuelve el tiempo en formato Unix
    }
};

#endif

/*

#include <Arduino.h>
#include "RTCDS3231Handler.h"

RTCDS3231Handler rtcHandler;

void setup() {
    Serial.begin(115200);
    if (rtcHandler.begin()) {
        // Ajusta la hora del RTC a un tiempo Unix específico
        time_t currentTime = 1672531200; // Ejemplo: 1 de Enero de 2023
        rtcHandler.setUnixTime(currentTime);
    }
}

void loop() {
    time_t now = rtcHandler.getUnixTime();
    Serial.print("Current Unix Time: ");
    Serial.println(now);
    delay(1000); // Actualiza la hora cada segundo para verificar
}


*/