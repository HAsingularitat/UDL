#ifndef CONFIG_H
#define CONFIG_H

// Definir el rol del dispositivo descomentando el que necesitas
//#define ROLE_KING
//#define ROLE_QUEEN
#define ROLE_PAWN

// Configuración del módulo
#define SUB_BOARD_ID "SBSF0001"
#define VERSION "1.0.0"
#define UART_RX_PIN 0
#define UART_TX_PIN 1
#define ADC_PINS {36, 39, 99, 99}
#define SENSOR_LIST "BMP280,AHT20"

// Estructura para almacenar la configuración del módulo
struct ModuleConfig {
    char subBoardId[9];
    char version[6];
    uint8_t uartPins[2];
    uint8_t adcPins[4];
    char sensorList[50];
};

// Instancia global de la configuración del módulo
ModuleConfig config = {
    SUB_BOARD_ID,
    VERSION,
    {UART_RX_PIN, UART_TX_PIN},
    ADC_PINS,
    SENSOR_LIST
};

#endif
