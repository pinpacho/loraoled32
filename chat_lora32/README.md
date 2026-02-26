# Pasos de uso 



1.- Configurar la conexión WiFi y los pines de comunicación LoRa
```
idf.py menuconfig
```

2.- Compilar el proyecto
```sh
idf.py build
```

3.- Conectar las dos tarjetas de desarrollo y flashear el binario al puerto correspondiente
```sh
idf.py -p {PUERTO} flash
```

4.- (Opcional) Monitorear cada tarjeta vía USB para ver los logs / prints.
```sh
idf.py -p {PUERTO} monitor
```
* Es posible terminar el modo monitor con `Ctrl + ]`

5.- Una vez conectada la red WiFi, aparecerá la IP en la pantalla OLED de cada tarjeta de desarrollo.
Es necesario que el dispositivo móvil y la tarjeta estén conectadas a la misma red WiFi, se recomienda utilizar el móvil como hotspot.

6.- Abrir la IP en el navegador y comenzar a intercambiar mensajes.