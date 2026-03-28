#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>


// Wi-Fi

const char* ssid = "-----------";
const char* password = "----------";

const char* mqtt_server = "---------";
const int mqtt_port = 1883;
const char* mqtt_client_id = "esp32-room1-temp";
const char* topicTemp = "home/room1/temperature";

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// MQTT client

WiFiClient espClient;
PubSubClient mqttClient(espClient);

// Wi-Fi connect

void connectWiFi() {
    Serial.println();
    Serial.print("[WiFi] Connecting to: ");
    Serial.println(ssid);


    WiFi.mode(WIFI_STA);
    WiFi.disconnect(true);
    delay(1000);

    WiFi.begin(ssid, password);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 40) {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    Serial.println();

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("[WiFi] Connected!");
        Serial.print("[WiFi] IP: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("[WiFi] FAILED!");
        Serial.print("[WiFi] Status = ");
        Serial.println(WiFi.status());
    }
}


// MQTT reconnect

void reconnectMQTT() {
    while (!mqttClient.connected()) {
        Serial.print("[MQTT] Connecting... ");

        if (mqttClient.connect(mqtt_client_id)) {
            Serial.println("OK");
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
    delay(1500);

    Serial.println();
    Serial.println("=== ESP32 DHT22 -> MQTT test ===");

    dht.begin();
    delay(2000);

    connectWiFi();

    mqttClient.setServer(mqtt_server, mqtt_port);
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