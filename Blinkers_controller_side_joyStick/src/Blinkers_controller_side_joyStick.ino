// When I make stuff. It might work maybe it won't work. ¯\_(ツ)_/¯ To see this code in use, visit my instagram @quad_out
#include "config.h"
#include <ESP8266WiFi.h>

int stateB; // The state for brake button
int joyStickValue;



IPAddress server(192,168,4,15);     // IP address of the AP
WiFiClient client;

void setup() {
  pinMode(brakeButton, INPUT_PULLUP); // Using the integrated pullup resistor pin on the wemos
  Serial.begin(9600);
  connect();

}

void loop() {

  stateB = digitalRead(brakeButton);
  joyStickValue = analogRead(joyStickPin);

  // Serial.println(joyStickValue);

  if(joyStickValue < 200){
    client.println(1);
    Serial.println("R");
    client.flush();
    delay(700); // These delays are necessary to have a reliable code
  }

  else if(joyStickValue > 700){
    client.println(2);
    Serial.println("L");
    client.flush();
    delay(700);
  }

  else if(stateB == 0){
    client.println(3);
    Serial.println("B");
    client.flush();
    delay(150);
  }
  else{
    client.println(0);
    client.flush();
    delay(100);
  }

  if (WiFi.status() != WL_CONNECTED){ // Checks if im still connected to the host
    connect(); // Runs connect function which will reconnect to the wifi and client
  }
}

void connect(){
  delay(700);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  client.connect(server, 80);
  client.setTimeout(50);

}
