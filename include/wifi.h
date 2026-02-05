#pragma once

#ifndef WIFI_H
#define WIFI_H

#include "config.h"

enum WiFiTaskState {
    WIFI_IDLE,
    WIFI_CONFIG,        // 配网状态
    WIFI_CONFIG_SAVING, // 配置状态保存中
    DNS_SETTING,        // DNS设置中
    WIFI_CONFIG_SAVED,  // 配置保存
    WIFI_CONNECT,       // 连接状态，用于开始连接
    WIFI_CONNECTING,    // 正在连接
    WIFI_CONNECTED,     // 已连接
    WIFI_MONITOR,       // wifi监视器，用来检测是否连接
};

void wifiTask();
void storageWiFiConfig(const char* ssid, const char* password);
void getWiFiConfig();
void existConfigMode();
void enterConfigMode();
void wifiSetup();
void wifiConnect();

#endif