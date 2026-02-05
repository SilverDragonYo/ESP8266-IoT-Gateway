## Introduction

A project based on ESP8266 and Wi-Fi provisioning, network management, cloud communication for embedded devices.

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

- Coming soon……

## Quick Start

0. Create an account on [Bemfa.com](https://cloud.bemfa.com/).
1. Copy the private key at **MQTT Device Cloud**. Paste it into the UID variable on `line 3`, `src/dataUploader.cpp`.
2. Install **Visual Studio Code** & **PlatformIO extension**.
3. PIO Home → Open Project.
4. Select the project folder containing `platformio.ini`.
5. Build & Upload.

<img src="https://pic.electro-dragon.site/keqingSuccess.png" width="180">





