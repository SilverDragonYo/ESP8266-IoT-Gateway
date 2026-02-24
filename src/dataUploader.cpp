#include "config.h"

const char* UID = "input UID here";             // 用户私钥，巴法云控制台获取，粘贴到这里
const char* pubTopic = "ED8266001";                          // 发布主题，与巴法云控制台创建的topic一致
const char* subTopic = "ED8266001CTRL";                      // 订阅主题，与巴法云控制台一致

SoftTimer ConnectTimer(5000);

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Topic:");
    Serial.println(topic);
    String Msg = "";
    for (unsigned int i = 0; i < length; i++) {
        Msg += (char)payload[i];
    }

    Serial.print("MQTT消息:");
    Serial.println(Msg);
    if (Msg == "on") {
        sendDataTo2560(0x0A);
    } else if (Msg == "off") {
        sendDataTo2560(0x0B);
    }
    Msg = "";
}

void connectToServer() {
    if(!ConnectTimer.expired()) return;
    if (Client.connect(UID)) {
        Serial.println("MQTT connected");
        Serial.print("subscribe:");
        Serial.println(subTopic);
        Client.subscribe(subTopic);
    } else {
        Serial.print("failed, rc=");
        Serial.print(Client.state());
        Serial.println("try again in 5 seconds");
    }
}


void periodicSendToServer() {
    static unsigned long startTime = millis();
    if (millis() - startTime > 10000) {
        String msg = "#"+String(data[SENSOR_OXYGEN])+"#"+String(data[SENSOR_PH])+"#"+String(data[SENSOR_TEMP])+"#";   
        Serial.print("send to server:");
        Serial.println(msg);
        Client.publish(pubTopic, msg.c_str());
        startTime = millis();
    }
}

void sendFlagToServer(int flag) {
    String msg;
    if(flag == 0x0A) {
        msg = "onSuccess";
    } else if (flag == 0x0B) {
        msg = "offSuccess";
    };
    Client.publish(pubTopic, msg.c_str());
    Serial.print("send to server:");
    Serial.println(msg);
}