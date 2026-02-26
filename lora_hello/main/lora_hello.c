#include <stdio.h>
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ssd1306.h"
#include "lora.h"


#define MESSAGE_LENGTH 240   // Tamaño máximo del paquete LoRa

SSD1306_t screen;
TaskHandle_t xHandleRXTask;  // Handle para controlar la tarea de recepción
uint8_t msg[MESSAGE_LENGTH]; // Buffer donde se guarda el mensaje recibido
int packets = 0;             // Contador de paquetes recibidos
int rssi = 0;                // Intensidad de señal en dBm

// Inicializa la pantalla OLED configurando I2C,
// resolución 128x64 y contraste máximo.
void screen_init(){
    i2c_master_init(&screen, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
    ssd1306_init(&screen, 128, 64);
    ssd1306_contrast(&screen, 0xFF);
}

// Borra completamente el contenido de la pantalla.
// Se recomienda usar antes de dibujar nueva información.
void scree_clear(){
    ssd1306_clear_screen(&screen, false);
}

// Muestra un texto en la página indicada (0–7).
// Primero limpia la línea y luego escribe el nuevo contenido.
void screen_print(char * str, int page){
  ssd1306_clear_line(&screen, page, false);
  ssd1306_display_text(&screen, page, str, strlen(str), false);
}

// Tarea encargada de recibir paquetes LoRa continuamente.
// Cuando llega un paquete:
// 1. Lo guarda en el buffer
// 2. Obtiene el RSSI
// 3. Incrementa el contador
// 4. Muestra datos en pantalla
void task_rx(void *p){
    
    char packets_count[64];
    char rrsi_str[64];
    int len;

    for (;;)
    {
        lora_receive();  // Coloca el módulo en modo recepción

        while (lora_received()) // Verifica si hay paquete disponible
        {
           len = lora_receive_packet(msg, MESSAGE_LENGTH);
           msg[len] = 0;          // Termina el string correctamente
           rssi = lora_packet_rssi(); // Lee intensidad de señal

           printf("Receive msg: %s, len: %d \n", msg, len);

           packets++; // Aumenta contador de paquetes
           
           sprintf(packets_count, "Count:%d\n", packets);
           sprintf(rrsi_str, "RSSI:%d dBM\n", rssi);

           // Actualiza información en la OLED
           screen_print(packets_count, 0);
           screen_print(rrsi_str, 1);
        }

        vTaskDelay(1); // Cede tiempo al scheduler
    }
}

// Envía un mensaje por LoRa.
// Suspende temporalmente la tarea RX para evitar conflictos
// y la reactiva después del envío.
void send_msg(char * msg, int size){
        printf("send packet : %s\n", msg);
        vTaskSuspend(xHandleRXTask);
        lora_send_packet((uint8_t *)msg, size);
        vTaskResume(xHandleRXTask);
        printf("Packet sent B) \n");
}

// Tarea encargada de transmitir periódicamente.
// Envía el mensaje "Ping" cada 2 segundos.
void task_tx(void *p){
    for (;;)
    {
        send_msg("Ping", 5);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

// Inicializa el módulo LoRa:
// - Configura frecuencia (915 MHz)
// - Activa verificación CRC
// - Crea tareas de recepción y transmisión
void lora_config_init(){
    printf("lora config init\n");
    lora_init();
    lora_set_frequency(915e6);
    lora_enable_crc();

    xTaskCreate(&task_rx, "task_rx", 2048, NULL, 5, &xHandleRXTask);
    xTaskCreate(&task_tx, "task_tx", 2048, NULL, 5, NULL);
}

// Función principal del ESP32.
// Inicializa pantalla y luego el sistema LoRa.
void app_main(void)
{
    screen_init();
    scree_clear();
    lora_config_init();
}
