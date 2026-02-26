#include <stdio.h>
#include "string.h"
#include "ssd1306.h"


SSD1306_t screen;       // Objeto de la pantalla

// Inicializa I2C y la pantalla OLED
void screen_init(){
    i2c_master_init(&screen, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
    ssd1306_init(&screen, 128, 64);   // Resolución 128x64
    ssd1306_contrast(&screen, 0xFF);  // Contraste máximo
}

// Limpia toda la pantalla
void scree_clear(){
    ssd1306_clear_screen(&screen, false);
}

// Imprime texto en una línea (page 0–7)
void screen_print(char * str, int page){
  ssd1306_clear_line(&screen, page, false);          // Limpia la línea
  ssd1306_display_text(&screen, page, str, strlen(str), false); // Muestra texto
}

// Función principal
void app_main(void)
{
    screen_init();             
    scree_clear();              
    screen_print("Hola Mundo B-)", 0); // Texto en línea 0
}