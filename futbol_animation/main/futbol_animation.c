#include <stdio.h>
#include "football.h"

#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "ssd1306.h"


#define TAG "SSD1306"

SSD1306_t screen;





void screen_init(){

    i2c_master_init(&screen, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO,CONFIG_RESET_GPIO);
    ssd1306_init(&screen, 128,64);
    ssd1306_contrast(&screen, 0xFF);


}

void screen_clear(){
    ssd1306_clear_screen(&screen,false); ///Siempre limpiar la pantalla en cada dibujo

}

void screen_print(char * str, int page){
  ssd1306_clear_line(&screen, page,false);//Limpia el primer renglon
  ssd1306_display_text(&screen, page, str,strlen(str),false);

}


void app_main(void)
{
    screen_init();
    screen_clear();

	int frame = 9;
	uint8_t segs[128];
    while (1) {

        /* =====================================================
         * 1️⃣ MOSTRAR GIF (5 segundos)
         * ===================================================== */
        screen_clear();

        TickType_t gifStart = xTaskGetTickCount();

        while ((xTaskGetTickCount() - gifStart) < pdMS_TO_TICKS(5000)) {

            for (int page = 0; page < 8; page++) {
                for (int seg = 0; seg < 128; seg++) {
                    segs[seg] = ssd1306_rotate_byte(
                        monkeyAnimation[frame][seg * 8 + page]
                    );
                }
                ssd1306_display_image(&screen, page, 0, segs, 128);
            }

            frame--;
            if (frame < 0) frame = 9;

            // velocidad del GIF (ajusta si quieres)
            vTaskDelay(pdMS_TO_TICKS(120));
        }

        /* =====================================================
         * 2️⃣ MOSTRAR IMAGEN UDEA (5 segundos)
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



        screen_print("Hola FPGAs B-)",0);

        screen_print("Partido Viernes",1);
        screen_print("4 PM",5);
        screen_print("Cancha Sintetica UdeA",6);

		int bitmapWidth = 4*8;
		int width = ssd1306_get_width(&screen);
		int xpos = width / 2; // center of width
		xpos = xpos - bitmapWidth/2; 
		int ypos = 16;
		ESP_LOGD(TAG, "width=%d xpos=%d", width, xpos);
		ssd1306_bitmaps(&screen, xpos, ypos, batman, 32, 13, false);
		vTaskDelay(3000 / portTICK_PERIOD_MS);

		for(int i=0;i<128;i++) {
			ssd1306_wrap_arround(&screen, SCROLL_RIGHT, 2, 3, 0);
		}


        
        vTaskDelay(pdMS_TO_TICKS(10000));

    }
}



