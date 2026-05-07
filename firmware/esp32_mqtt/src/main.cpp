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
 
std::string mqtt_client_id = "esp32-home";

// topics - sensor humidity

const char* humidity_kitchen = "home/kitchen/sensor/humidity";
const char* humidity_living_room = "home/living_room/sensor/humidity";
const char* humidity_bedroom = "home/bedroom/sensor/humidity";

// topic - actuators command

const char* cmd_hum_system_kitchen = "home/kitchen/actuator/h_system/4";
const char* cmd_hum_system_living_room = "home/living_room/actuator/h_system/5";
const char* cmd_hum_system_bedroom = "home/bedroom/actuator/h_system/12"; 

const int ledPin_kitchen = 4;
const int ledPin_living_room = 5;
const int ledPin_bedroom = 12;

#define DTHPIN_16 16
#define DTHPIN_17 17
#define DTHPIN_18 18
#define DHTTYPE_22 DHT22
#define DHTTYPE_11 DHT11

DHT d1(DTHPIN_16, DHTTYPE_22);
DHT d2(DTHPIN_17, DHTTYPE_11);
DHT d3(DTHPIN_18, DHTTYPE_11);

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void setup(){

  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("=== ESP32 DHT22/11 + MQTT CMD ===");

  d1.begin();
  d2.begin();
  d3.begin();

  utilsMcu::wifiMqtt::connect(ssid, password);

  mqttClient.setServer(mqtt_server, mqtt_port);
  mqttClient.setCallback(utilsMcu::commandActuators::callback);

}

void loop()
{
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("[WiFi] Lost connection, reconnecting...");
      utilsMcu::wifiMqtt::connect(ssid, password);
    }

    Serial.print("[WiFi] IP: ");
    Serial.println(WiFi.localIP());

    
    if (!mqttClient.connected()) {
      utilsMcu::mqtt::reconnect(mqttClient, 
        mqtt_client_id, 
        cmd_hum_system_kitchen);

      utilsMcu::mqtt::reconnect(mqttClient, 
        mqtt_client_id, 
        cmd_hum_system_living_room);

      utilsMcu::mqtt::reconnect(mqttClient,
        mqtt_client_id,
        cmd_hum_system_bedroom);
    }

    mqttClient.loop();

    float temp1 = d1.readTemperature();
    float hum1 = d1.readHumidity();

    float temp2 = d2.readTemperature();
    float hum2 = d2.readHumidity();

    float temp3 = d3.readTemperature();
    float hum3 = d3.readHumidity();

    if(isnan(temp1) || isnan(hum1)){
      Serial.println("[DHT] Read failed: temp1 || hum1!");
    }else{
      Serial.print("[DHT] Temp: ");
      Serial.print(temp1, 2);
      Serial.print(" C | Humidity: ");
      Serial.print(hum1, 2);
      Serial.println(" %");

      char payLoad_t1[16];
      char payLoad_h1[16];

      snprintf(payLoad_h1, sizeof(payLoad_h1), "%.2f", hum1);

      Serial.print("payLoad_h1: ");
      Serial.println(payLoad_h1);

      bool ok_publich_payLoad_h1 = mqttClient.publish(humidity_kitchen, payLoad_h1);

      Serial.print("[MQTT] Publish ");
      Serial.println(ok_publich_payLoad_h1 ? "OK" : "FAIL");
    }

    if(isnan(temp2) || isnan(hum2)){
      Serial.println("[DHT] Read failed: temp2 || hum2!");
    }else{
      Serial.print("[DHT] Temp: ");
      Serial.print(temp2, 2);
      Serial.print(" C | Humidity: ");
      Serial.print(hum2, 2);
      Serial.println(" %");

      char payLoad_t2[16];
      char payLoad_h2[16];

      snprintf(payLoad_h2, sizeof(payLoad_h2), "%.2f", hum2);

      bool ok_publich_payLoad_h2 = mqttClient.publish(humidity_bedroom, payLoad_h2);
      
      Serial.print("[MQTT] Publish ");
      Serial.println(ok_publich_payLoad_h2 ? "OK" : "FAIL");
    }

    if(isnan(temp3) || isnan(hum3)){
      Serial.println("[DHT] Read failed: temp3 || hum3!");
    }else{
      Serial.print("[DHT] Temp: ");
      Serial.print(temp3, 2);
      Serial.print(" C | Humidity: ");
      Serial.print(hum3, 2);
      Serial.println(" %");

      char payLoad_t3[16];
      char payLoad_h3[16];

      snprintf(payLoad_h3, sizeof(payLoad_h3), "%.2f", hum3);
      
      bool ok_publich_payLoad_h3 = mqttClient.publish(humidity_living_room, payLoad_h3);

      Serial.print("[MQTT] Publish ");
      Serial.println(ok_publich_payLoad_h3 ? "OK" : "FAIL");
    }

    delay(3000);
}
