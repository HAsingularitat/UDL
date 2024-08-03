Modulo versio C (esp32-c3 Supermini)

Cuenta con una parcial, ya  que  cuante con una limitacion en cuanto la catidad de pines,
asi que se recomienda usar unicamente param (multifuncional board ) que tengan unicamente la necesidad de lineas i2c o que sea para elementes que no requieran mas de 2 tipos de comunicacion  

Cuenta con un conector de microsd con una limitacion de maximo 32gb

Para identificar todos  los estados posibles de este modulo   se agrego un led 5050 rgb.

Una adicon es el btn adicional , opcional.

un pequeno modulo  opcional es el  agregar un modulo  rtc (i2c),

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
    #rx(opcional)
    #tx(opcional)

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
