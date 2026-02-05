#include "config.h"

void setup() {
    Serial.begin(9600);
    ESP_EEPROM.begin(512);
    wifiSetup();
    serverSetup();
    Client.setServer("bemfa.com", 9501);
    Client.setCallback(callback);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    server.handleClient();
    wifiTask();
    ledTask();
    dnsServer.processNextRequest();
    if (!Client.connected() && WiFi.status() == WL_CONNECTED) {
        connectToServer();     // 保证MQTT连接
    }
    Client.loop();  // MQTT客户端循环
    receiveDataFrom2560();
    if(Client.connected()) {
        periodicSendToServer();
    }
}
