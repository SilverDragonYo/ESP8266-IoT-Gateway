#pragma once

#ifndef DATA_UPLOADER_H
#define DATA_UPLOADER_H

#include "config.h"

void callback(char* topic, byte* payload, unsigned int length);
void connectToServer();
void periodicSendToServer();
void sendFlagToServer(int flag);

#endif