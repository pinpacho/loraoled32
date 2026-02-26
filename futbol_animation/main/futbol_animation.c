#include <stdio.h>
#include "football.h"   // Contiene los frames del GIF y bitmaps

#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "ssd1306.h"

#define TAG "SSD1306"   // Etiqueta para mensajes de depuración

SSD1306_t screen;

// Inicializa la pantalla OLED:
// - Configura I2C
// - Define resolución 128x64
// - Ajusta contraste al máximo
void screen_init(){
    i2c_master_init(&screen, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
    ssd1306_init(&screen, 128, 64);
    ssd1306_contrast(&screen, 0xFF);
}

// Limpia completamente la pantalla antes de dibujar algo nuevo
void screen_clear(){
    ssd1306_clear_screen(&screen, false);
}

// Escribe texto en una página específica (0–7)
// Primero limpia la línea y luego imprime el texto
void screen_print(char * str, int page){
  ssd1306_clear_line(&screen, page, false);
  ssd1306_display_text(&screen, page, str, strlen(str), false);
}

void app_main(void)
{
    screen_init();
    screen_clear();

	int frame = 9;        // Frame inicial del GIF
	uint8_t segs[128];    // Buffer temporal para cada página

    while (1) {

        /* =====================================================
         * MOSTRAR GIF (5 segundos)
         * Se recorren los frames y se dibujan página por página.
         * ===================================================== */
        screen_clear();

        TickType_t gifStart = xTaskGetTickCount();

        while ((xTaskGetTickCount() - gifStart) < pdMS_TO_TICKS(5000)) {

            // Recorre las 8 páginas verticales de la pantalla
            for (int page = 0; page < 8; page++) {

                // Llena el buffer con los datos del frame actual
                for (int seg = 0; seg < 128; seg++) {
                    segs[seg] = ssd1306_rotate_byte(
                        monkeyAnimation[frame][seg * 8 + page]
                    );
                }

                // Muestra la página procesada
                ssd1306_display_image(&screen, page, 0, segs, 128);
            }

            frame--;              // Cambia al frame anterior
            if (frame < 0) frame = 9;  // Reinicia animación

            vTaskDelay(pdMS_TO_TICKS(120)); // Velocidad del GIF
        }

        /* =====================================================
         * MOSTRAR IMAGEN UDEA (5 segundos)
         * Dibuja un bitmap completo de 128x64.
         * ===================================================== */
        screen_clear();

        ssd1306_bitmaps(
            &screen,
            0,
            0,
            logoUdeA,
            128,
            64,
            false
        );

        vTaskDelay(pdMS_TO_TICKS(5000));
        screen_clear();

        /* =====================================================
         * 3️⃣ MOSTRAR TEXTO + IMAGEN + SCROLL
         * ===================================================== */

        // Muestra información del evento
        screen_print("Hola FPGAs B-)", 0);
        screen_print("Partido Viernes", 1);
        screen_print("4 PM", 5);
        screen_print("Cancha Sintetica UdeA", 6);

        // Centra el bitmap horizontalmente
		int bitmapWidth = 4 * 8;
		int width = ssd1306_get_width(&screen);
		int xpos = width / 2;
		xpos = xpos - bitmapWidth / 2;
		int ypos = 16;

		ESP_LOGD(TAG, "width=%d xpos=%d", width, xpos);

        // Dibuja imagen (ej. balon)
		ssd1306_bitmaps(&screen, xpos, ypos, balon, 32, 13, false);

		vTaskDelay(3000 / portTICK_PERIOD_MS);

        // Aplica efecto de desplazamiento horizontal
		for(int i = 0; i < 128; i++) {
			ssd1306_wrap_arround(&screen, SCROLL_RIGHT, 2, 3, 0);
		}

        // Mantiene el resultado en pantalla 10 segundos
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}