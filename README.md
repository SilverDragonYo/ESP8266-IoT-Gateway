## Introduction

An ESP8266-based project for Wi-Fi provisioning and MQTT-based cloud communication in embedded systems.

On first boot, users need to connect to the hotspot of the device, enter the configuration page and finish Wi-Fi provisioning. Then it will automatically reconnect and monitor the connecting state.

Once connected to the Internet, it will periodically publish data to the MQTT server, receive and handle commands from server

## Features

- #### Captive Portal Wi-Fi provisioning

  - Automatic redirection to configuration page in AP mode.
  - Wi-Fi configuration storage in flash memory.

- #### Connection & State management

  - State-machine-based workflow.
  - Connection monitoring & automatic reconnection.
  - Automatically fallback to configuration mode when fail to reconnect.

- #### MQTT communication

  - Periodic sensor data publishing.
  - Subscription to the control topic & command handling.

- #### Serial communication

  - Receiving sensor data from Mega 2560.
  - Sending control commands.

- #### LED Status indication

  - Indicate Wi-Fi state through different LED patterns.

    |     LED patterns     |         meaning          |
    | :------------------: | :----------------------: |
    |       LED_OFF        |            /             |
    |        LED_ON        |     Wi-Fi connected      |
    | LED_BLINK_SLOW (1Hz) |     Wi-Fi connecting     |
    | LED_BLINK_FAST (2Hz) | enter configuration mode |

## Teck Stack

- #### Hardware

  - ESP8266

- #### Development

  - Platform IO

- #### libs included

  - Arduino
  - DNSServer
  - ESP_EEPROM
  - ESP8266WiFi
  - ESP8266WebServer (not async version)
  - PubSubClient

## Demo

- [ESP8266 IoT 小项目功能演示｜配网、MQTT 通信与状态指示](https://www.bilibili.com/video/BV1hGFvzwEGy/?vd_source=dc6062a3b05d6ddfefe6b194258183c9)

## Quick Start

0. Create an account on [Bemfa.com](https://cloud.bemfa.com/).
1. Create two device named `ED8266001` and `ED8266001CTRL` at **MQTT Device Cloud**.
2. Install **Visual Studio Code** & **PlatformIO extension**.
3. Clone / Download the project.
4. PIO Home → Open Project.
5. Select the project folder containing `platformio.ini`.
6. Copy the private key at **MQTT Device Cloud**. Paste it into the UID variable on `line 3`, `src/dataUploader.cpp`.
7. Build & Upload.



<div style="display: flex;justify-content: center;">
    <img src="https://pic.electro-dragon.site/keqingSuccess.png" width="180">
</div>








