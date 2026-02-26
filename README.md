# IoT con TTGO LoRa32

Este repositorio contiene varios proyectos desarrollados con la placa **TTGO LILYGO LoRa32**, la cual integra:

- Microcontrolador ESP32  
- Módulo LoRa  
- Pantalla OLED SSD1306  

Todos los proyectos fueron desarrollados utilizando el framework **ESP-IDF**.

Cada trabajo se encuentra en una carpeta independiente con el nombre del código correspondiente.

---

## Librerías utilizadas

### 1. Módulo LoRa  
Se utilizó la librería ESP32 LoRa Library, que permite:

- Configurar frecuencia (915 MHz)
- Enviar y recibir paquetes
- Obtener RSSI
- Activar verificación CRC  

Esta librería permite la comunicación inalámbrica de largo alcance y bajo consumo.

### 2. Pantalla OLED  
Se utilizó la librería SSD1306, que permite:

- Mostrar texto
- Dibujar imágenes (bitmaps)
- Crear animaciones
- Aplicar efectos de desplazamiento (scroll)

---

# Descripción de los proyectos

## 1. oledhello

Proyecto básico de prueba de la pantalla OLED.

Funcionalidades:
- Inicialización de la pantalla
- Limpieza del display
- Visualización del mensaje "Hola Mundo"

Objetivo: Verificar el correcto funcionamiento de la pantalla y la comunicación I2C.

---

## 2. lora_hello

Ejemplo básico de comunicación LoRa.

Funcionalidades:
- Envío periódico de mensajes ("Ping")
- Recepción de paquetes
- Visualización en pantalla del contador de paquetes y RSSI

Objetivo: Probar transmisión y recepción LoRa entre dispositivos.

---

## 3. futbol_animation

Proyecto enfocado en gráficos y animaciones en la pantalla OLED.

Funcionalidades:
- Visualización de animación tipo GIF
- Mostrar imágenes bitmap
- Impresión de texto personalizado
- Efecto de desplazamiento horizontal

Objetivo: Explorar las capacidades gráficas de la pantalla.

---

## 4. chat_lora32

Proyecto IoT que integra múltiples tecnologías.

Funcionalidades:
- Recepción de mensajes LoRa
- Visualización de datos en pantalla OLED
- Conexión WiFi
- Servidor web HTTP
- API para enviar y consultar mensajes desde el navegador

Permite:
- Visualizar mensajes LoRa desde una página web
- Enviar mensajes LoRa desde el navegador
- Mostrar SSID, dirección IP, RSSI y contador en pantalla

Objetivo: Integrar LoRa, WiFi y servidor web en un sistema IoT funcional.

---

# Uso del proyecto (ESP-IDF)

En la terminal:

```bash
cd nombre_del_proyecto
get_idf
idf.py build
idf.py flash
idf.py monitor
```