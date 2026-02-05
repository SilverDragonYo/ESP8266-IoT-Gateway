#include "config.h"

EEPROMClass ESP_EEPROM;

void writeEEPROM(int address, const char* str, size_t maxLen) {
    size_t len = strlen(str);
    if (len >= maxLen) len = maxLen - 1;

    for(size_t i = 0; i < len; i++) {
        ESP_EEPROM.write(address + i, str[i]);
    };
    ESP_EEPROM.write(address + len, '\0');
    ESP_EEPROM.commit();
}

void readEEPROM(int address, char* buf, size_t maxLen) {
    size_t i = 0;
    for(; i < maxLen-1; i++) {
        char c = ESP_EEPROM.read(address + i);
        if(c == '\0') break;
        buf[i] = c;
    };
    buf[i] = '\0';
}