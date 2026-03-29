#include "utilsMcu.hpp"

void utilsMcu::wifiMqtt::connect(std::string& ssid, std::string& password)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());

    Serial.print("[WIFI] connecting!");
    
    if(WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("[Wifi] connected");
    Serial.println(WiFi.localIP());
}

void utilsMcu::mqtt::reconnect(PubSubClient& mqttClient, 
                            std::string& mqttClientId,
                            const char* topic1,
                            const char* topic2)
{
    while (!mqttClient.connect(mqttClientId.c_str())){
        
        Serial.println("[MQTT] connecte...");

        if(mqttClient.connect(mqttClientId.c_str())){
            Serial.println("[MQTT] OK");
            
            mqttClient.subscribe(topic1);
            mqttClient.subscribe(topic2);
            
            Serial.print("[MQTT] subscride: ");
            Serial.print(mqttClient.state());
            Serial.println(" retry in 2 sec");
            
            delay(2000);
        }else{
            Serial.print("FAILED, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" retry in 2 sec");
            delay(2000);
        }
    }
}

void utilsMcu::commandActuators::cmd(String cmdActuators, const int pin)
{

    if(cmdActuators == "ON"){
        digitalWrite(pin, HIGH);
        Serial.printf("pin № %d HIGH\n", pin);
    }else if(cmdActuators == "OFF"){
        digitalWrite(pin, LOW);
        Serial.printf("pin № %d LOW\n", pin);
    }
}

void utilsMcu::commandActuators::callback(char *topic, byte *payload, unsigned int length)
{
    String message = "";
    
    for(unsigned int i = 0; i < length; ++i){
        message += payload[i];
    }

    message.trim();
    message.toUpperCase();

    String topicStr = String(topic);
    int lastSlash = topicStr.lastIndexOf('/'); 
    String pinStr = topicStr.substring(lastSlash + 1); 
    int pin = pinStr.toInt();

    cmd(message, pin);
}
