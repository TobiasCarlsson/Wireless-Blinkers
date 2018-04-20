// When I make stuff. It might work maybe it won't work. ¯\_(ツ)_/¯ To see this code in use, visit my instagram @quad_out
#include <ESP8266WiFi.h>
#include "config.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

int state; // just a declaring the state to us in the switch

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, LED, NEO_RGB + NEO_KHZ800);

WiFiServer server(80); // Sets the port to open
IPAddress IP(192,168,4,15); // The ip address for the server
IPAddress mask = (255, 255, 255, 0);

void setup() {
  Serial.begin(9600);

  strip.setBrightness(150); // Set the strips brightness
  WiFi.mode(WIFI_AP);
  WiFi.softAP(WIFI_SSID, WIFI_PASS);

  WiFi.softAPConfig(IP, IP, mask);
  server.begin();

  strip.begin(); // Prepars the datapin for neopixel commands
  strip.show(); // Turns off all the leds
  delay(500);

}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    rainbowCycle(5);
    return;}
  client.setTimeout(50);

  while(true){

  state = client.readStringUntil('\r').toInt(); // Reciving the string from the controller and making it to an interger
  server.flush(); // wating for the whole string to be recieved

  //Serial.println(state); // Serial print the state value which is a interger (only needed for debugging)

  switch (state) {


    case 1:
    Right();
    break;

    case 2:
    Left();
    break;

    case 3:
    Brake();
    delay(100);
    break;

    default:
    BrakeOff();
    break;
    }
  }
}

  //Brake signal
void Brake(){
  Brakelight(strip.Color(55,0,0), 4);
}
void Brakelight(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, c);
  }
  strip.show();
}

void BrakeOff(){
  BrakelightOff(strip.Color(0, 0 ,0), 4);
}
void BrakelightOff(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, c);
  }
  strip.show();
}

  //Right turn singal
void Right(){
      TurnRight(strip.Color(55, 0, 0), FLOWTIME);
      TurnLeft(strip.Color(0, 0, 0), 0);

  }

void TurnRight(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

//Left turn signal
void Left(){
      TurnLeft(strip.Color(40, 0, 0), FLOWTIME);
      TurnLeft(strip.Color(0, 0, 0), 0);

  }

void TurnLeft(uint32_t c, uint8_t wait) {
  for(uint16_t i=strip.numPixels()-1; i<strip.numPixels(); i--) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

// Rainbowlight
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*1; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
