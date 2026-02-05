#pragma once

#ifndef EEPROM_H
#define EEPROM_H

#include "config.h"

void writeEEPROM(int address, const char* str, size_t maxLen);
void readEEPROM(int address, char* buf, size_t maxLen);

#endif