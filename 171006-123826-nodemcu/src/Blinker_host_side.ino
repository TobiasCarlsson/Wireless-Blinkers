#include <ESP8266WiFi.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

int flowTime = 10;
int direction;

#define PIN D1

Adafruit_NeoPixel strip = Adafruit_NeoPixel(37, PIN, NEO_RGB + NEO_KHZ800);

WiFiServer server(80);
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);

byte ledPin = 2;

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Test", "123456798");
  WiFi.softAPConfig(IP, IP, mask);
  server.begin();
  pinMode(ledPin, OUTPUT);
  Serial.println();
  Serial.println("Blinker_host_side.ino");
  Serial.println("Server started.");
  Serial.print("IP: ");     Serial.println(WiFi.softAPIP());
  Serial.print("MAC:");     Serial.println(WiFi.softAPmacAddress());

  strip.begin();
  strip.show();

}

void loop() {
  WiFiClient client = server.available();
  if (!client) {return;}
  client.setTimeout(50);

  while(true){


  String request = client.readStringUntil('\r');

  direction = request.toInt();

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
    // BrakeOff();
    break;
  }
}
}

  //Brake signal
void Brake(){
  Brakelight(strip.Color(255, 20 ,20), 4);
}
void Brakelight(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, c);
  }
  strip.show();
}

// void BrakeOff(){
//   BrakelightOff(strip.Color(0, 0 ,0), 4);
// }
// void BrakelightOff(uint32_t c, uint8_t wait) {
//   for(uint16_t i=0; i<strip.numPixels(); i++){
//     strip.setPixelColor(i, c);
//   }
//   strip.show();
//   //delay(wait);
// }

  //Right turn singal
void Right(){
    for(int x = 0; x < 1; x++){
      TurnRight(strip.Color(55, 0, 0), flowTime);
      TurnRight(strip.Color(0, 0, 0), flowTime);
    }
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
    for(int x = 0; x < 1; x++){
      TurnLeft(strip.Color(40, 0, 0), flowTime);
      TurnLeft(strip.Color(0, 0, 0), flowTime);
    }
  }

void TurnLeft(uint32_t c, uint8_t wait) {
  for(uint16_t i=strip.numPixels()-1; i<strip.numPixels(); i--) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
