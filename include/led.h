#pragma once
#include "config.h"

enum ledMode { LED_OFF, LED_ON, LED_BLINK_SLOW, LED_BLINK_FAST, LED_BLINK_ONCE };

void ledTask();
void setLedMode(ledMode mode);