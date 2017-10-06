// When I make stuff. It might works maybe it won't work. ¯\_(ツ)_/¯

#include <ESP8266WiFi.h>

int pot;

int rightButton = D4;  // White button
int leftButton = D3;   // Green Button
int brakeButton = D2;   // Red button

int stateR;
int stateL;
int stateB;

byte ledPin = 2;
char ssid[] = "Test";
char pass[] = "123456798";

IPAddress server(192,168,4,15);     // IP address of the AP
WiFiClient client;

void setup() {
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(brakeButton, INPUT);


  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected");
  Serial.println("station_bare_01.ino");
  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());
  digitalWrite(D4, 1);
  pinMode(ledPin, OUTPUT);

  client.connect(server, 80);

  client.setTimeout(50);
}

void loop() {

  stateR = digitalRead(rightButton);
  stateL = digitalRead(leftButton);
  stateB = digitalRead(brakeButton);


  if(stateR == 0){
    client.println("1");
    client.flush();

    Serial.println("1");

  }
  else if(stateL == 0){
    client.println("2");
    client.flush();

    Serial.println("2");
  }
  else if(stateB == 1){
    client.println("3");
    client.flush();

    Serial.println("3");
  }

  //String answer = client.readStringUntil('\r');
  //client.flush();




}
