#include "config.h"

unsigned long lastTick = 0;
unsigned long blinkInterval_slow = 1000;
unsigned long blinkInterval_fast = 500;
unsigned long blinkTime_once = 1000;

ledMode currentMode = LED_OFF;

void setLedMode(ledMode newMode) {
    if(newMode != currentMode) {
        currentMode = newMode;
        lastTick = millis();
    } 
}

void ledTask() {
    unsigned long now = millis();
    switch(currentMode) {
        case LED_OFF:
            digitalWrite(LED_BUILTIN, HIGH);
            break;
        case LED_ON:
            digitalWrite(LED_BUILTIN, LOW);
            break;
        case LED_BLINK_SLOW:
            if(now - lastTick >= blinkInterval_slow) {
                lastTick = now;
                digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
            }
            break;
        case LED_BLINK_FAST:
            if(now - lastTick >= blinkInterval_fast) {
                lastTick = now;
                digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
            }
            break;
        case LED_BLINK_ONCE:
            digitalWrite(LED_BUILTIN, LOW);
            if(now - lastTick >= blinkTime_once) {
                currentMode = LED_OFF;
            }
            break;
    }
}