# Wireless blinkers system

### How it works

It uses the ESP8266WiFi.h library so that the host side will act like a wifi hotspot and the controller will be used as a device that connects to the wifi.

You will need to add a pullup resistor to one of the button because wemos d1 only has 2 internal pullup resistor or use pin 8 that has an internal pull down resistor.

### Booting
When booting on the host side you the led strip will light up green when it has opened it's wifi hotspot.

The controller side will light up its internal led when it's connected.
