#ifndef SENSOR_MODULES_H
#define SENSOR_MODULES_H

#include "GPSNEO6MHandler.h"
#include "BatteryLevelHandler.h"
#include "ADS1115Handler.h"
#include "AHT20Handler.h"
#include "EEPROMHandler.h"
#include "GasSensorHandler.h"
#include "InternalEEPROMHandler.h"
#include "NTCHandler.h"
#include "RainSensorHandler.h"
#include "RTCExternalHandler.h"
#include "RTCInternalHandler.h"
#include "SDHandler.h"
#include "SDMMCHandler.h"
#include "SPS30Handler.h"
#include "UVSensorHandler.h"

// Conditional includes for each module
#ifdef INCLUDE_BMP280
#include "BMP280Handler.h"
#endif

#ifdef INCLUDE_ALPHASENSE_CO
#include "AlphasenseCOHandler.h"
#endif

#ifdef INCLUDE_ALPHASENSE_NO2
#include "AlphasenseNO2Handler.h"
#endif

#ifdef INCLUDE_ALPHASENSE_NO
#include "AlphasenseNOHandler.h"
#endif

#ifdef INCLUDE_NEOPIXEL
#include "NeoPixelHandler.h"
#endif

class SensorModules {
private:
    GPSNEO6MHandler gpsHandler;
    BatteryLevel batteryLevel;
    ADS1115Handler ads1115;
    AHT20Handler aht20;
    EEPROMHandler eeprom;
    GasSensorHandler gasSensor;
    InternalEEPROMHandler internalEeprom;
    NTCHandler ntc;
    RainSensorHandler rainSensor;
    RTCExternalHandler rtcExternal;
    RTCInternalHandler rtcInternal;
    SDHandler sd;
    SDMMCHandler sdmmc;
    SPS30Handler sps30;
    UVSensorHandler uvSensor;

#ifdef INCLUDE_BMP280
    BMP280Handler bmp280;
#endif

#ifdef INCLUDE_ALPHASENSE_CO
    AlphasenseCOHandler coSensor;
#endif

#ifdef INCLUDE_ALPHASENSE_NO2
    AlphasenseNO2Handler no2Sensor;
#endif

#ifdef INCLUDE_ALPHASENSE_NO
    AlphasenseNOHandler noSensor;
#endif

#ifdef INCLUDE_NEOPIXEL
    NeoPixelHandler neoPixel;
#endif

public:
    SensorModules() {}

    void begin() {
        gpsHandler.begin(4, 3);
        batteryLevel.begin(39);
        ads1115.begin();
        aht20.begin();
        eeprom.begin();
        gasSensor.begin();
        internalEeprom.begin();
        ntc.begin();
        rainSensor.begin();
        rtcExternal.begin();
        rtcInternal.begin();
        sd.begin();
        sdmmc.begin();
        sps30.begin();
        uvSensor.begin();

#ifdef INCLUDE_BMP280
        bmp280.begin();
#endif

#ifdef INCLUDE_ALPHASENSE_CO
        coSensor.begin();
#endif

#ifdef INCLUDE_ALPHASENSE_NO2
        no2Sensor.begin();
#endif

#ifdef INCLUDE_ALPHASENSE_NO
        noSensor.begin();
#endif

#ifdef INCLUDE_NEOPIXEL
        neoPixel.begin();
#endif
    }

    String collectAllSensorData() {
        String data = "";

        data += gpsHandler.getFormattedData() + ",";
        data += batteryLevel.readBatteryLevel() + ",";
        data += ads1115.readSensorData() + ",";
        data += aht20.readSensorData() + ",";
        data += eeprom.readData() + ",";
        data += gasSensor.readSensorData() + ",";
        data += internalEeprom.readData() + ",";
        data += ntc.readTemperature() + ",";
        data += rainSensor.readRainStatus() + ",";
        data += rtcExternal.getTime() + ",";
        data += rtcInternal.getTime() + ",";
        data += sps30.readParticulateMatter() + ",";
        data += uvSensor.readUVIndex() + ",";

#ifdef INCLUDE_BMP280
        data += bmp280.readSensorData() + ",";
#endif

#ifdef INCLUDE_ALPHASENSE_CO
        data += coSensor.readSensorData() + ",";
#endif

#ifdef INCLUDE_ALPHASENSE_NO2
        data += no2Sensor.readSensorData() + ",";
#endif

#ifdef INCLUDE_ALPHASENSE_NO
        data += noSensor.readSensorData() + ",";
#endif

#ifdef INCLUDE_NEOPIXEL
        data += neoPixel.getStatus() + ",";
#endif

        return data;
    }
};

#endif


/*

#include <Arduino.h>
#include "SensorModules.h"

SensorModules sensorModules;

void setup() {
    Serial.begin(115200);
    sensorModules.begin(); // Inicializa todos los sensores
}

void loop() {
    String sensorData = sensorModules.collectAllSensorData();
    Serial.println(sensorData); // Muestra los datos recopilados
    delay(1000); // Ajusta según la frecuencia deseada de lectura
}


*/