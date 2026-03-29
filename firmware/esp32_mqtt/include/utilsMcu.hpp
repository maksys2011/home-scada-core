#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <string>
#include <PubSubClient.h>

namespace utilsMcu{
    namespace wifiMqtt{
        void connect(std::string& ssid, std::string& password);
    }
    namespace commandActuators{
        void cmd(String cmdActuators, const int pin);
        void callback(char* topic,
                    byte* payload,
                    unsigned int length);
    }
    namespace mqtt{
        void reconnect(PubSubClient& mqttClient, 
                    std::string& mqttClientId, 
                    const char* topic1,
                    const char* topic2);
    }
    
}