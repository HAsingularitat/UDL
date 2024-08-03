#ifndef SD_HANDLER_H
#define SD_HANDLER_H

#include <SD.h>
#include <SPI.h>

class SDHandler {
private:
    File logFile;

public:
    bool begin() {
        if (!SD.begin()) {
            Serial.println("Card Mount Failed");
            return false;
        }
        Serial.println("SD card initialized successfully");
        return true;
    }

    void logData(String filename, String data) {
        logFile = SD.open(filename, FILE_WRITE);
        if (logFile) {
            logFile.println(data);
            logFile.close();
            Serial.println("Data logged to " + filename);
        } else {
            Serial.println("Error opening " + filename + " for writing");
        }
    }

    String findTimestamp(String filename, String timestamp) {
        logFile = SD.open(filename, FILE_READ);
        if (!logFile) {
            Serial.println("Error opening " + filename);
            return "File not found";
        }

        String line;
        bool isLast = true;
        while (logFile.available()) {
            String currentLine = logFile.readStringUntil('\n');
            if (currentLine.startsWith(timestamp)) {
                String nextLine = logFile.readStringUntil('\n');
                logFile.close();
                if (nextLine.length() > 0) {
                    isLast = false; // There is another record after this one
                }
                return currentLine + (isLast ? ", Last Record" : ", Not Last Record");
            }
        }
        logFile.close();
        return "Timestamp not found";
    }

    void beginSequentialRead(String filename, String timestamp) {
        logFile.close(); // Ensure file is closed before we try to open it again
        logFile = SD.open(filename, FILE_READ);
        if (!logFile) {
            Serial.println("Failed to open file for sequential read");
            return;
        }

        while (logFile.available()) {
            String currentLine = logFile.readStringUntil('\n');
            if (currentLine.startsWith(timestamp)) {
                Serial.println("Starting sequential read from timestamp: " + timestamp);
                return; // Position the file pointer right after the matching timestamp line
            }
        }

        Serial.println("Timestamp not found, sequential read not started");
    }

    String readNextRecord() {
        if (!logFile || !logFile.available()) {
            logFile.close();
            return "No more records or file not open";
        }

        String line = logFile.readStringUntil('\n');
        return line;
    }
};

#endif
/*

#include "SDHandler.h"

SDHandler sdHandler;

void setup() {
    Serial.begin(115200);
    if (!sdHandler.begin()) {
        Serial.println("Initialization failed!");
        while (1);
    }
}

void loop() {
    // Ejemplo de uso de búsqueda de timestamp
    String result = sdHandler.findTimestamp("/DataLog.csv", "2023-08-15 12:00:00");
    Serial.println(result);

    // Iniciar lectura secuencial desde un timestamp específico
    sdHandler.beginSequentialRead("/DataLog.csv", "2023-08-15 12:00:00");

    // Leer registros secuenciales
    String record;
    while (!(record = sdHandler.readNextRecord()).startsWith("No more records")) {
        Serial.println("Next Record: " + record);
    }

    delay(10000); // Esperar un tiempo antes de reiniciar el loop
}


*/