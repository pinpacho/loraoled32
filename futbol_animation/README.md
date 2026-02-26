# futbol_animation

## Descripción

Proyecto para la TTGO LoRa32 (ESP32 + OLED SSD1306) que demuestra el uso de gráficos en la pantalla.

El programa:

- Reproduce una animación por frames.
- Muestra una imagen bitmap en pantalla completa.
- Imprime texto en distintas posiciones.
- Aplica efecto de desplazamiento (scroll).

---

## Funcionamiento

El programa ejecuta un ciclo continuo con tres etapas:

1. Animación tipo GIF durante algunos segundos.  
2. Imagen estática 128x64.  
3. Texto + imagen centrada + efecto de scroll.

---

## Conversión de imágenes a bitmap

Para mostrar imágenes en la OLED es necesario convertirlas a formato compatible con SSD1306 (arreglo de bytes en C).

Se puede usar el siguiente conversor online:

https://mischianti.org/ssd1306-oled-display-draw-images-splash-and-animations-2/

Recomendaciones:

- Usar imágenes en blanco y negro (1 bit).
- Ajustar tamaño (ej. 128x64).
- Copiar el arreglo generado en un archivo `.h` e incluirlo en el proyecto.

---

## Compilación

```bash
idf.py build
idf.py flash
idf.py monitor