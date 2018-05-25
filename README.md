# Wireless blinkers system

### How it works

It uses the ESP8266WiFi.h library so that the host side will act like a wifi hotspot and the controller will be used as a device that connects to the wifi.

You will need to add a pullup resistor to one of the button because wemos d1 only has 2 internal pullup resistor or use pin 8 that has an internal pull down resistor.

### Booting
When booting on the host side you the led strip will light up green when it has opened it's wifi hotspot.

The controller side will light up its internal led when it's connected.


### The cad files
All the cad files can be found on my thingiverse
https://www.thingiverse.com/Quad_out/about


## components list
* Nodemcu https://goo.gl/u722vH
* Wemos d1 https://goo.gl/bWQr4T
  * Either 2 wemos or 1 wemos + 1 Nodemcu
* 1-2meters 60led/meter ws2812b Leds (Depends on how big your board is) https://goo.gl/rgBPHC
* 24 leds from at 144leds/meter ws2812b led (Around 16cm) https://goo.gl/GiM2QE
* Some kind of stepdown regulator 42 -> 5v, I used lm2596 which is not optimal because it not specified for 42v but it should handle up to 45v https://goo.gl/GBPCds
* Another stepdown regulator 5v -> 3.3v https://goo.gl/xznVCD (For the leds)
