#include <ESP8266WiFi.h>
#include "config.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif


int direction;
int dir;

#define PIN D1

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, PIN, NEO_RGB + NEO_KHZ800);

WiFiServer server(80);
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);
byte ledPin = 2;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(WIFI_SSID, WIFI_PASS);

  WiFi.softAPConfig(IP, IP, mask);
  server.begin();

  strip.begin();
  strip.show();
  BootLight(strip.Color(0, 100, 0), 5);


}

void loop() {
  WiFiClient client = server.available();
  if (!client) {return;}
  client.setTimeout(50);

  while(true){

  direction = client.readStringUntil('\r').toInt();
  server.flush();

  Serial.println(direction);
  //Serial.println(client.readStringUntil('\r').toInt());

  switch (direction) {


    case 1:
    Right();
    break;

    case 2:
    Left();
    break;

    case 3:
    Brake();
    break;

    default:
    BrakeOff();
    break;
    }
  }
}

  //Brake signal
void Brake(){
  Brakelight(strip.Color(255,127,80), 4);
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
      TurnRight(strip.Color(0, 0, 0), 0);

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
// Boot light
void BootLight(uint32_t c, uint8_t wait) {
  for(uint16_t i=strip.numPixels()-1; i<strip.numPixels(); i--) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
