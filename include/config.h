#pragma once

#include <Arduino.h>
#include "serialComm.h"
#include "dataUploader.h"
#include <ESP8266WiFi.h>
#include "PubSubClient.h"
#include <ESP8266WebServer.h>
#include "ESP_EEPROM.h"
#include "DNSServer.h"

#include "led.h"
#include "wifi.h"
#include "webServer.h"
#include "eeprom.h"
#include "softTimer.h"

extern float data[3];
enum SensorIndex { SENSOR_OXYGEN = 0, SENSOR_PH = 1, SENSOR_TEMP = 2};

extern WiFiClient espClient;
extern PubSubClient Client;
extern char WiFi_SSID[];
extern char WiFi_PWD[];
extern bool wifiConfigMode;
extern bool dnsActive;
extern ESP8266WebServer server;
extern DNSServer dnsServer;
extern EEPROMClass ESP_EEPROM;

//定义帧头、帧尾、数据和命令码
#define FRAME_HEAD 0xFF
#define FRAME_TAIL 0xCB
#define DATA_LEN 3
#define DATA_FRAME 0x01
#define CMD_FRAME 0x02
#define FLAG_FRAME 0x03

//ssid和密码的最大长度
#define WIFI_MAX_LEN 21