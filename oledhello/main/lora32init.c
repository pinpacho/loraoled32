#include <stdio.h>
#include "string.h"
#include "ssd1306.h"


SSD1306_t screen;

void screen_init(){

    i2c_master_init(&screen, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO,CONFIG_RESET_GPIO);
    ssd1306_init(&screen, 128,64);
    ssd1306_contrast(&screen, 0xFF);


}

void scree_clear(){
    ssd1306_clear_screen(&screen,false); ///Siempre limpiar la pantalla en cada dibujo

}

void screen_print(char * str, int page){
  ssd1306_clear_line(&screen, page,false);//Limpia el primer renglon
  ssd1306_display_text(&screen, page, str,strlen(str),false);

}

void app_main(void)
{
    screen_init();
    scree_clear();
    screen_print("Hola Mundo B-)",0);
  
}
