#ifndef GPS_NEO6M_HANDLER_H
#define GPS_NEO6M_HANDLER_H

#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

class GPSNEO6MHandler {
private:
    TinyGPSPlus gps;
    SoftwareSerial* ss = nullptr;
    const uint32_t GPSBaud = 4800;

public:
    GPSNEO6MHandler() {} // Constructor vacío

    ~GPSNEO6MHandler() {
        if (ss != nullptr) {
            delete ss;
        }
    }

    void begin(int rxPin, int txPin) {
        if (ss != nullptr) {
            delete ss; // Elimina la instancia anterior si existe
        }
        ss = new SoftwareSerial(rxPin, txPin); // Crea una nueva instancia con los pines nuevos
        ss->begin(GPSBaud);
        Serial.println(F("GPS Module initialized with RX pin: ") + String(rxPin) + " and TX pin: " + String(txPin));
    }

    bool readGPS() {
        bool newData = false;
        while (ss->available() > 0) {
            if (gps.encode(ss->read())) {
                newData = true;
            }
        }
        return newData;
    }

    String getFormattedData() {
        String data;
        if (gps.location.isValid()) {
            data += String(gps.location.lat(), 6) + F(",") + 
                    String(gps.location.lng(), 6) + F(",");
        } else {
            data += F("*,*,");
        }

        data += String(gps.altitude.meters(), 2) + F(",") +
                String(gps.speed.kmph(), 2) + F(",") +
                String(gps.course.deg(), 2) + F(",") +
                String(gps.satellites.value()) + F(",");

        return data;
    }
};

#endif
/*

#include <Arduino.h>
#include "GPSNEO6MHandler.h"

GPSNEO6MHandler gpsHandler; // Sin pines definidos en el constructor

void setup() {
    Serial.begin(115200);
    gpsHandler.begin(4, 3); // Configura los pines RX y TX aquí
}

void loop() {
    if (gpsHandler.readGPS()) {
        String gpsData = gpsHandler.getFormattedData();
        Serial.println(gpsData);
    }
    // El loop sigue ejecutándose sin delays
}


*/