#include "config.h"

ESP8266WebServer server(80);
DNSServer dnsServer;
const byte DNS_PORT = 53;
bool dnsActive = false;  

const char index_html[] PROGMEM = R"rawliteral(
<head>
  <meta charset="UTF-8">
  <title>设备配网页</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-weight: bolder; margin-top: 15px;}
    input {margin-bottom: 5px; height: 35px; border-radius: 8px;}
    button {margin-top: 5px; border-radius: 8px; width: 100px; height: 35px;}
    body {margin:x auto;}
  </style>
</head>

<body>
  <h2>ElectroDragon</h2>
  <h4>输入WiFi名称和密码, 然后提交</h4>
  <h5 style="color: red;">请输入不超过 20 位的数字或英文字母</h5>
  <form action="wifi" method="POST">
    <input name="ssid" placeholder="请输入WiFi SSID"><br>
    <input name="password" placeholder="请输入WiFi密码"><br>
    <button type="submit">提交</button>
  </form>
</body>
)rawliteral";

const char success_html[] PROGMEM = R"rawliteral(
<head>
  <meta charset="UTF-8">
  <title>设备配网页</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-weight: bolder; margin-top: 15px;}
    button {margin-top: 5px; border-radius: 8px; width: 100px; height: 35px;}
    body {margin:x auto;}
  </style>
</head>

<body>
  <h2>ElectroDragon</h2>
  <h4>已成功配网，将在一段时间后自动退出此页</h4>
  <h4>您也可以手动退出当前页面</h4>
  <h4>退出后设备将自动重连，请确保热点配置正确</h4>
  <h6><i>Developed by ElectroDragon</i></h6>

</body>
)rawliteral";


/**
 * @brief 初始化web服务器
 * 
 */
void serverSetup() {
    server.on("/", HTTP_GET, []() {
        server.send_P(200, "text/html", index_html);
    });

    // 处理安卓、iOS、Windows系统的网络连接测试请求
    server.on("/generate_204", HTTP_GET, []() {
        server.send_P(200, "text/html", index_html);
    });

    server.on("/library/test/success.html", HTTP_GET, []() {
        server.send_P(200, "text/html", index_html);
    });

    server.on("/connecttest.txt", HTTP_GET, []() {
        server.send_P(200, "text/html", index_html);
    });

    server.on("/wifi", HTTP_POST, []() {
        char ssid[21];
        char password[21];
        if(server.hasArg("ssid")) {
            server.arg("ssid").toCharArray(ssid, sizeof(ssid));
        };

        if(server.hasArg("password")) {
            server.arg("password").toCharArray(password, sizeof(password));
        }

        server.send_P(200, "text/html", success_html);
        storageWiFiConfig(ssid, password);
        wifiConfigMode = false;
    });

    server.onNotFound([]() {
        if(wifiConfigMode) {
            server.send_P(200, "text/html", index_html);
        } else {
            server.send(404, "text/plain", "not found");
        }
    });
    server.begin();
}

void dnsStart() {
    dnsServer.start(DNS_PORT, "*", IPAddress(192, 168, 4, 1));
    Serial.println("dns started");
    dnsActive = true;
}

void dnsEnd() {
    if(dnsActive) {
        dnsServer.stop();
        Serial.println("dns ended");
        dnsActive = false;
    }
}
