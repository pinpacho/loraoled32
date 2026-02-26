# Configuración del componente LoRa (lora_hello)


Creamos un archivo **CMakeLists.txt** dentro de *components/lora* y le agregamos lo siguiente:

```c
idf_component_register(
    SRCS "lora.c"
    PRIV_REQUIRES driver
    INCLUDE_DIRS "include"
)

#set(COMPONENT_ADD_INCLUDEDIRS include)
#set(COMPONENT_SRCS "lora.c")
#register_component()
```

Y en el archivo de **lora.c** cambiamos las lineas 322 y 324:
```c
   gpio_reset_pin(CONFIG_RST_GPIO);
   gpio_set_direction(CONFIG_RST_GPIO, GPIO_MODE_OUTPUT);
   gpio_reset_pin(CONFIG_CS_GPIO);
   gpio_set_direction(CONFIG_CS_GPIO, GPIO_MODE_OUTPUT);
```

Revisar el datasheet de la tarjeta TTGO LoRa32 para verificar los pines correctos.

Luego configurarlos mediante:
```bash
idf.py menuconfig
```


En el menú correspondiente podrás asignar:

* Pin RST

* Pin CS

* SPI

