#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "WemoSwitch.h"
#include "WemoManager.h"
#include "CallbackFunction.h"

// prototypes
boolean connectWifi();

//on/off callbacks
void lightOn();
void lightOff();

//------- Replace the following! ------
char ssid[] = "nome_da_sua_rede_wifi";       // your network SSID (name)
char password[] = "Digite_a_senha_do_seu_wifi";  // your network key

WemoManager wemoManager;
WemoSwitch *light = NULL;

const int ledPin = BUILTIN_LED;

void setup()
{
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("Wifi conectado!");
  Serial.println("Endereço IP: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  wemoManager.begin();
  // Format: Alexa invocation name, local port no, on callback, off callback
  light = new WemoSwitch("test lights", 80, lightOn, lightOff);
  wemoManager.addDevice(*light);

  pinMode(ledPin, OUTPUT); // initialize digital ledPin as an output.
  delay(10);
  digitalWrite(ledPin, HIGH); // Wemos BUILTIN_LED is active Low, so high is off
}

void loop()
{
  wemoManager.serverLoop();
}

void lightOn() {
    Serial.print("Chave 1 Ligada...");
    digitalWrite(ledPin, LOW);
}

void lightOff() {
    Serial.print("Chave 2 Desligada...");
    digitalWrite(ledPin, HIGH);
}
