#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
 
const char* ssid = "...";
const char* password = "...";
 
const char* mqtt_server = "...";
const int mqtt_port = 1883;
 
const char* mqtt_client_id = "esp32-room1-temp";
const char* topicTemp = "home/room1/temperature";
const char* cmdTopic  = "home/test/cmd";
 
const int ledPin = 5;     // внешний LED -> GPIO5
#define DHTPIN 4          // DHT22 -> GPIO4
#define DHTTYPE DHT22
 
DHT dht(DHTPIN, DHTTYPE);
 
WiFiClient espClient;
PubSubClient mqttClient(espClient);
 
void connectWiFi() {
  Serial.println();
  Serial.print("[WiFi] Connecting to: ");
  Serial.println(ssid);
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println();
  Serial.println("[WiFi] Connected!");
  Serial.print("[WiFi] IP: ");
  Serial.println(WiFi.localIP());
}
 
void callBack(char* topic, byte* payload, unsigned int length) {
  String msg = "";
 
  for (unsigned int i = 0; i < length; ++i) {
    msg += (char)payload[i];
  }
 
  Serial.print("[MQTT] Message on ");
  Serial.print(topic);
  Serial.print(" -> ");
  Serial.println(msg);
 
  if (String(topic) == cmdTopic) {
    if (msg == "ON") {
      digitalWrite(ledPin, HIGH);
      Serial.println("[LED] ON");
    } else if (msg == "OFF") {
      digitalWrite(ledPin, LOW);
      Serial.println("[LED] OFF");
    }
  }
}
 
void reconnectMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("[MQTT] Connecting... ");
 
    if (mqttClient.connect(mqtt_client_id)) {
      Serial.println("OK");
 
      mqttClient.subscribe(cmdTopic);
      Serial.print("[MQTT] Subscribed: ");
      Serial.println(cmdTopic);
 
    } else {
      Serial.print("FAILED, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" retry in 2 sec");
      delay(2000);
    }
  }
}
 
void setup() {
  Serial.begin(115200);
  delay(1000);
 
  Serial.println();
  Serial.println("=== ESP32 DHT22 + MQTT CMD ===");
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  dht.begin();
 
  connectWiFi();
 
  mqttClient.setServer(mqtt_server, mqtt_port);
  mqttClient.setCallback(callBack);
}
 
void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[WiFi] Lost connection, reconnecting...");
    connectWiFi();
  }
 
  if (!mqttClient.connected()) {
    reconnectMQTT();
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
 
    char payload[16];
    snprintf(payload, sizeof(payload), "%.2f", t);
 
    bool ok = mqttClient.publish(topicTemp, payload);
 
    Serial.print("[MQTT] Publish ");
    Serial.print(topicTemp);
    Serial.print(" = ");
    Serial.print(payload);
    Serial.print(" -> ");
    Serial.println(ok ? "OK" : "FAIL");
  }
 
  delay(3000);
}