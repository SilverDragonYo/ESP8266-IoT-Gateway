#include "config.h"

char WiFi_SSID[21] = "yuanshen";   //WIFI名称，最多20位
char WiFi_PWD[21] = "yuanshen";     //WIFI密码 
bool wifiConfigMode = false;  

WiFiTaskState currentState = WIFI_CONNECT;
WiFiClient espClient;

PubSubClient Client(espClient);
SoftTimer RetryTimer(15000);
SoftTimer DNSSetupTimer(200);
SoftTimer ConfigSaveTimer(1500);
SoftTimer MonitorTimer(10000);

/**
 * @brief wifi任务状态机
 * 
 */
void wifiTask() {
    switch (currentState) {
        case WIFI_IDLE:
            break;

        case WIFI_CONNECT:
            WiFi.mode(WIFI_STA);
            setLedMode(LED_BLINK_SLOW);
            wifiConnect();
            currentState = WIFI_CONNECTING;
            break;

        case WIFI_CONNECTING:
            if(WiFi.status() == WL_CONNECTED) {
                currentState = WIFI_CONNECTED;
            } else if (RetryTimer.expired() && !wifiConfigMode) {
                currentState = WIFI_CONFIG;
            }
            break;

        case WIFI_CONFIG:
            setLedMode(LED_BLINK_FAST);
            if(!wifiConfigMode) enterConfigMode();
            currentState = DNS_SETTING;
            DNSSetupTimer.reset();
            break;

        case DNS_SETTING:
            if(DNSSetupTimer.expired()) {
                if(!dnsActive && WiFi.softAPIP() != IPAddress(0,0,0,0)) {
                    dnsStart();
                    currentState = WIFI_CONFIG_SAVING;
                }
            }
            break;

        case WIFI_CONFIG_SAVING:
            if(!wifiConfigMode) {
                Serial.println("get wifi config");
                currentState = WIFI_CONFIG_SAVED;
                ConfigSaveTimer.reset();
            }
            break;

        case WIFI_CONFIG_SAVED:
            if(ConfigSaveTimer.expired()) {
                Serial.println("restart connect");
                server.stop();
                dnsEnd();
                currentState = WIFI_CONNECT;  
            }
            break;

        case WIFI_CONNECTED:
            setLedMode(LED_ON);
            Serial.println("WiFi connected");
            Serial.print("IP address: ");
            Serial.println(WiFi.localIP());
            currentState = WIFI_MONITOR;
            break;
            
        case WIFI_MONITOR:
            if(MonitorTimer.expired() && WiFi.status() != WL_CONNECTED) {
                currentState = WIFI_CONNECT;
            }
            break;      
    }
}

void storageWiFiConfig(const char* ssid, const char* password) {
    writeEEPROM(0, ssid, WIFI_MAX_LEN);
    writeEEPROM(100, password, WIFI_MAX_LEN);
}

void getWiFiConfig() {
    readEEPROM(0, WiFi_SSID, WIFI_MAX_LEN);
    readEEPROM(100, WiFi_PWD, WIFI_MAX_LEN);
}

void wifiSetup() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WiFi_SSID, WiFi_PWD);
    getWiFiConfig();
}

/**
 * @brief 进入wifi配置模式
 * 
 */
void enterConfigMode() {
    wifiConfigMode = true;  
    WiFi.mode(WIFI_AP);
    server.begin();
    Serial.println("enter config mode");
    IPAddress apIP(192, 168, 4, 1);
    IPAddress netMsk(255, 255, 255, 0);
    WiFi.softAPConfig(apIP, apIP, netMsk);
    WiFi.softAP("ED8266001_Config", "12345678");
}

/**
 * @brief 单次连接wifi。重置重试计时器。
 * 
 */
void wifiConnect() {
    getWiFiConfig();
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WiFi_SSID);
    Serial.print("PWD: ");
    Serial.println(WiFi_PWD);
    WiFi.begin(WiFi_SSID, WiFi_PWD);
    RetryTimer.reset();
}

