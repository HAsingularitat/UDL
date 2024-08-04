# UDL

## Propósito
Este proyecto tiene como objetivo desarrollar un sistema modular e inteligente para la monitorización y análisis de la calidad del aire. Utiliza una red de módulos ESP32 intercambiables que recolectan diversos datos ambientales y los comunican a un dispositivo central para su procesamiento y análisis. La integración de tecnologías como la realidad aumentada y la capacidad de procesamiento local en smartphones permite no solo la recolección de datos, sino también su contextualización en tiempo real, ofreciendo así un enfoque más dinámico y enriquecido para la gestión de la calidad del aire.

## Componentes del Proyecto
El proyecto se compone de varios módulos funcionales, cada uno encapsulado en su propio archivo de código, lo que permite una gran modularidad y flexibilidad:
- **Módulos de Sensores (ESP32):** Varios tipos de sensores encargados de la recolección de datos ambientales.
- **Control de Roles:** Diferentes roles dentro de la red (Reina, Rey, Peón, etc.) que definen la jerarquía y las responsabilidades de cada módulo.
- **Manejo de Datos:** Almacenamiento de datos recolectados en tarjetas SD y transmisión de datos importantes a través de la red.
- **Comunicación Avanzada:** Uso de ESP-NOW para la comunicación eficiente y rápida entre módulos.
- **Interfaz de Usuario:** Integración con smartphones para la visualización de datos y manejo de módulos mediante realidad aumentada.
- **Análisis Contextual:** Uso de la cámara del smartphone para capturar imágenes que se correlacionan con los datos recolectados, permitiendo una mejor comprensión del entorno y la fuente de contaminantes.

## Funcionalidades Principales
- **Recolección de Datos:** Los módulos recogen datos de calidad del aire y condiciones ambientales.
- **Procesamiento y Análisis:** Los datos se procesan para identificar patrones, tendencias y áreas problemáticas.
- **Visualización en Realidad Aumentada:** Los datos y la ubicación de los módulos se visualizan en tiempo real sobre la imagen capturada por la cámara del smartphone.
- **Interactividad:** Los usuarios pueden interactuar con el sistema para obtener detalles específicos o realizar ajustes en la configuración de los módulos.

## Ventajas del Sistema
- **Adaptabilidad:** Capacidad para adaptarse a diferentes entornos y necesidades de monitoreo gracias a su diseño modular.
- **Interacción Enriquecida:** La realidad aumentada y la interfaz interactiva ofrecen una nueva dimensión en la monitorización ambiental.
- **Análisis Avanzado:** La integración de imágenes y datos permite un análisis contextual que puede mejorar significativamente la precisión y utilidad de la información recolectada.

## Documentación Adicional
Todos los detalles técnicos, configuraciones y guías de usuario están disponibles en los archivos adjuntos del repositorio, permitiendo a los usuarios y desarrolladores adaptar y expandir el sistema según sea necesario.

Este proyecto representa un avance significativo en la tecnología de monitoreo ambiental, con un potencial considerable para futuras innovaciones y aplicaciones.
