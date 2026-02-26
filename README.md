# **IoT con TTGO Lora32** 


Para el desarrollo de estos codigos se utilizo la placa de TTGO LILYGO LORA32, la cual posee un chip ESP32, un modulo LORA y una pantalla OLED.

Se utilizo el framework ESP-IDF

## Librerias utilizadas

1. **Módulo LoRa:** Libreria ESP32 Lora Library para controlar el módulo de radio LoRa. Esencial para la comunicación de radio con baja energía y larga distancias.

2. **Pantalla OLED:** Integramos la librería SSD1306. Incluye varios ejemplos que pueden ser de gran utilidad.

## Uso del proyecto

Para usar los proyectos con el framework ESP-IDF utilizamos en la terminal

```sh
cd nombre_del_proyecto
get_idf
idf.py build
```

Para importar las librerias nos movemos al proyecto y creamos una carpeta *components* . 

Luego copiamos los archivos de las librerias y los pegamos en la carpeta *components* . 




