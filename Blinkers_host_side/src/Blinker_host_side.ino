#include <ESP8266WiFi.h>
#include "config.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif


int direction;
int dir;

#define LED1 D1
#define LED2 D2

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(LEDS, LED1, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(LEDS, LED2, NEO_RGB + NEO_KHZ800);

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

  strip1.begin();
  strip1.show();
  BootLight(strip1.Color(0, 100, 0), 5);


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
  Brakelight(strip1.Color(255,130,0), 4);
}
void Brakelight(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip1.numPixels(); i++){
    strip1.setPixelColor(i, c);
  }
  strip1.show();
}

void BrakeOff(){
  BrakelightOff(strip1.Color(0, 0 ,0), 4);
}
void BrakelightOff(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip1.numPixels(); i++){
    strip1.setPixelColor(i, c);
  }
  strip1.show();
}

  //Right turn singal
void Right(){
      TurnRight(strip1.Color(55, 0, 0), FLOWTIME);
      TurnRight(strip1.Color(0, 0, 0), 0);

  }

void TurnRight(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip1.numPixels(); i++) {
    strip1.setPixelColor(i, c);
    strip11.show();
    delay(wait);
  }
}

//Left turn signal
void Left(){
      TurnLeft(strip1.Color(40, 0, 0), FLOWTIME);
      TurnLeft(strip1.Color(0, 0, 0), 0);
  }

void TurnLeft(uint32_t c, uint8_t wait) {
  for(uint16_t i=strip1.numPixels()-1; i<strip1.numPixels(); i--) {
    strip1.setPixelColor(i, c);
    strip1.show();
    delay(wait);
  }
}
// Boot light
void BootLight(uint32_t c, uint8_t wait) {
  for(uint16_t i=strip1.numPixels()-1; i<strip1.numPixels(); i--) {
    strip1.setPixelColor(i, c);
    strip1.show();
    delay(wait);
  }
}
// Rainbowlight
void RainbowCycle(uint8_t interval, direction dir = FORWARD)
{
    ActivePattern = RAINBOW_CYCLE;
    Interval = interval;
    TotalSteps = 255;
    Index = 0;
    Direction = dir;
}
