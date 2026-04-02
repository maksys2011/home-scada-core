#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <string>
#include "utilsMcu.hpp"
 
std::string ssid = "...";
std::string password = "...";
 
const char* mqtt_server = "...";
const int mqtt_port = 1883;
 
std::string mqtt_client_id = "esp32-room1-temp";

const char* topicTemp = "home/bedroom2/sensor/temperature";
const char* topicHumidity = "home/bedroom2/sensor/humidity";
const char* topicLight = "home/bedroom2/sensor/light";

const char* cmdHeaterTopic  = "home/bedroom2/actuators/heater/5";           // управление сплит-системой
const char* cmdHumidifierTopic2 = "home/bedroom2/actuators/humidity/17";    // управление системой вентиляции
 
const int ledPin = 5;     // внешний LED -> GPIO5
const int ledPin_17 = 17;

#define DHTPIN 4          // DHT22 -> GPIO4
#define DHTTYPE DHT22
 
DHT dht(DHTPIN, DHTTYPE);
 
WiFiClient espClient;
PubSubClient mqttClient(espClient);
 
void setup() {
  Serial.begin(115200);
  delay(1000);
 
  Serial.println();
  Serial.println("=== ESP32 DHT22 + MQTT CMD ===");
 
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin_17, OUTPUT);

  digitalWrite(ledPin, LOW);
  digitalWrite(ledPin_17, LOW);
 
  dht.begin();

  utilsMcu::wifiMqtt::connect(ssid, password);
 
  mqttClient.setServer(mqtt_server, mqtt_port);
  mqttClient.setCallback(utilsMcu::commandActuators::callback);
}
 
void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[WiFi] Lost connection, reconnecting...");
    utilsMcu::wifiMqtt::connect(ssid, password);
  }
 
  if (!mqttClient.connected()) {
    utilsMcu::mqtt::reconnect(mqttClient, mqtt_client_id, cmdHeaterTopic, cmdHumidifierTopic2);

  }
 
  mqttClient.loop();
 
  float t = dht.readTemperature();
  float h = dht.readHumidity();
 
  if (isnan(t) || isnan(h)) {
    Serial.println("[DHT] Read failed!");
  } else {
    Serial.print("[DHT] Temp: ");
    Serial.print(t, 2);
    Serial.print(" C | Humidity: ");
    Serial.print(h, 2);
    Serial.println(" %");
 
    char tempPayload[16];
    char humPayload[16];

    snprintf(tempPayload, sizeof(tempPayload), "%.2f", t);
    snprintf(humPayload, sizeof(humPayload), "%.2f", h);
 
    bool okTemp = mqttClient.publish(topicTemp, tempPayload);
    bool okHum = mqttClient.publish(topicHumidity, humPayload);

 
    Serial.print("[MQTT] Publish ");
    Serial.print(topicTemp);
    Serial.print(" = ");
    Serial.print(tempPayload);
    Serial.print(" -> ");
    Serial.println(okTemp ? "OK" : "FAIL");

    Serial.print("[MQTT] Publish ");
    Serial.print(topicHumidity);
    Serial.print(" = ");
    Serial.print(humPayload);
    Serial.print(" -> ");
    Serial.println(okHum ? "OK" : "FAIL");
  }
 
  delay(3000);
}