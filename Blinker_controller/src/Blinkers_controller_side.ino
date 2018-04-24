// When I make stuff. It might work maybe it won't work. ¯\_(ツ)_/¯ To see this code in use, visit my instagram @quad_out
#include "config.h"
#include <ESP8266WiFi.h>


int stateR; // The state for right button
int stateL; // The state for left button
int stateB; // The state for brake button



IPAddress server(192,168,4,15);     // IP address of the AP
WiFiClient client;

void setup() {
  pinMode(rightButton, INPUT_PULLUP); // Using the integrated pullup resistor pin on the wemos
  pinMode(leftButton, INPUT_PULLUP);  // So you dont need to use as many extra components
  pinMode(brakeButton, INPUT); // You will need to add a pullupp or pulldown resistor on this button
  Serial.begin(9600);

  connect();
}

void loop() {
  stateR = digitalRead(rightButton);
  stateL = digitalRead(leftButton);
  stateB = digitalRead(brakeButton);

  if(stateR == 0){
    client.println(1);
    delay(800); // These delays are necessary to have a reliable code
  }

  else if(stateL == 0){
    client.println(2);
    delay(800);
  }

  else if(stateB == 1){
    client.println(3);
    delay(100);
  }

  if (WiFi.status() != WL_CONNECTED){ // Checks if im still connected to the host
    connect(); // Runs connect function which will reconnect to the wifi and client
  }
}

void connect(){
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  digitalWrite(D4, 1);
  client.connect(server, 80);
  client.setTimeout(50);

}
