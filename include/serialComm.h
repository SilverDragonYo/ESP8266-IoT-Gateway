#pragma once

#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

#include "config.h"

bool receiveDataFrom2560();
void sendDataTo2560(uint8_t cmd);

#endif