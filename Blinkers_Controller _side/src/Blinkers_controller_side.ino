// When I make stuff. It might work maybe it won't work. ¯\_(ツ)_/¯
#include "config.h"
#include <ESP8266WiFi.h>

int pot;


int rightButton = D4;  // White button
int leftButton = D3;   // Green Button
int brakeButton = D2;  // Red button

int stateR;
int stateL;
int stateB;

int respons;

byte ledPin = 2;

IPAddress server(192,168,4,15);     // IP address of the AP
WiFiClient client;

void setup() {
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(brakeButton, INPUT);
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  digitalWrite(D4, 1);
  client.connect(server, 80);
  client.setTimeout(50);
}

void loop() {
  stateR = digitalRead(rightButton);
  stateL = digitalRead(leftButton);
  stateB = digitalRead(brakeButton);

  if(stateR == 0){
    client.println(1);
    delay(800);
  }

  else if(stateL == 0){
    client.println(2);
    delay(800);
  }

  else if(stateB == 1){
    client.println(3);
  }

  if (WiFi.status() != WL_CONNECTED){
    connect();
  }
}

void connect(){
  delay(1000);
  Serial.print("not connect");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  digitalWrite(D4, 1);
  client.connect(server, 80);
  client.setTimeout(50);

}
