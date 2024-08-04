# UDL
# Proyecto de Red de Módulos ESP32 con ESP-NOW

## Descripción General
Este proyecto desarrolla una red de módulos ESP32 que se comunican utilizando el protocolo ESP-NOW, optimizado para aplicaciones IoT con necesidades de comunicación inalámbrica eficiente y flexible. Se implementan diversos roles como King, Queen, Knight, Rook y Pawn, cada uno con responsabilidades específicas dentro de la red.

## Estructura del Proyecto
El proyecto incluye múltiples archivos de cabecera (.h) que encapsulan la funcionalidad de los sensores, la gestión de la red y la manipulación de datos:

- **ADS1115Handler.h**: Gestiona la conversión analógica a digital.
- **AlphasenseHandlers**: Controladores para diferentes sensores de gases Alphasense.
- **BatteryLevelHandler.h**: Monitorea y reporta el nivel de batería del dispositivo.
- **BMP280Handler.h**: Gestiona el sensor de presión y temperatura BMP280.
- **DeepSleepHandler.h**: Controla los ciclos de sueño profundo para ahorro de energía.
- **EEPROMHandler.h**: Maneja las operaciones de lectura/escritura en la EEPROM.
- **GasSensorHandler.h**: Procesa datos de sensores de gases genéricos.
- **GPSNEO6MHandler.h**: Encapsula la funcionalidad para manejar el módulo GPS NEO-6M.
- **NetworkManagement.h**: Administra la red de dispositivos, incluyendo el registro y la actualización de roles.
- **SDHandler.h y SDMMCHandler.h**: Gestión de archivos en tarjetas SD.
- **SensorModules.h**: Unifica todos los controladores de sensores para facilitar su acceso desde el código principal.

## Funcionalidades
### Roles de Dispositivos
- **King**: Máxima autoridad en la red. Puede modificar roles y configurar parámetros globales.
- **Queen**: Gestiona la recopilación y almacenamiento de datos. Sincroniza la hora y distribuye comandos.
- **Knight**: Actúa como apoyo a la Queen y puede tomar su lugar si es necesario.
- **Rook**: Se especializa en retransmitir información entre nodos distantes.
- **Pawn**: El rol más básico, capaz de escalar a roles superiores bajo condiciones específicas.

### Comunicación
Utilizando ESP-NOW, los dispositivos pueden comunicarse de manera eficiente sin necesidad de conectarse a una red WiFi tradicional. Este método permite una configuración flexible de redes ad-hoc.

### Gestión de Energía
Los dispositivos pueden entrar en modo de sueño profundo para conservar energía, despertando en intervalos configurables o mediante interruptores externos.

## Configuración y Uso
Para implementar el proyecto, se debe configurar cada dispositivo con el rol adecuado y cargar el código correspondiente. El `main.ino` permite definir el rol inicial y configurar los parámetros básicos del dispositivo.

## Limitaciones y Ventajas
- **Ventajas**: Alta modularidad, bajo consumo energético, y flexibilidad en la configuración de roles y tareas.
- **Limitaciones**: La cantidad de datos y la frecuencia de comunicación pueden estar limitadas por el hardware y la configuración del entorno de red.

## Contribuciones
Se invita a los desarrolladores a contribuir al proyecto mediante Pull Requests en GitHub, donde también se puede solicitar ayuda y reportar errores.

