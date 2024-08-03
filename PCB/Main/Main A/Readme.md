Modulo versio C (esp32-wroom-32d)

Cuenta con una compativilidad total  entre todos los modulos,

el procesador principla es el microcontrolador esp32 wroom 32d, en le cual se esta usando todos los pines con los que cuenta para poder  estar preparadospara cualquier adecion .

cuenta con los componetes minmos necesarios para el  funcionamiento  del microprocesador , con los otones "EN" , "IO0" , un conversor usb to serial , el cual es le  CH340G , ademas de un conector  usb.

Otro componencte con los que cuenta es un conector  de memoria microsd , en especifico  una memoria microsd - mmc , para tener la capacidad de aceptar memoria de 2tb.

Para identificar todos  los estados posibles de este modulo   se agrego un led 5050 rgb.

Una adicon es el btn adicional , opcional.

Estos son los componentes universales de todos los modulos.

un pequeno modulo  opcional es el  agregar un modulo  rtc,

conector to energymini
    #gnd
    #5v
    #bat
    #rx
    #tx

conector to multifuncional 
    #gnd
    #5v
    #bat
    #sda
    #scl
    #rx
    #tx

Conectort oled (opcional)
    #gnd
    #5v
    #sda
    #scl

Conector spi
    #miso
    #mosi
    #sck
    #ss
