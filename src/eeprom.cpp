#include "config.h"

EEPROMClass ESP_EEPROM;

/**
 * @brief 向EEPROM写入字符串
 * 
 * @param address 起始地址
 * @param str 要写入的字符串
 * @param maxLen 最大长度
 */
void writeEEPROM(int address, const char* str, size_t maxLen) {
    size_t len = strlen(str);
    if (len >= maxLen) len = maxLen - 1;

    for(size_t i = 0; i < len; i++) {
        ESP_EEPROM.write(address + i, str[i]);
    };
    ESP_EEPROM.write(address + len, '\0');
    ESP_EEPROM.commit();
}

/**
 * @brief 从EEPROM读取字符串
 * 
 * @param address 起始地址
 * @param buf 缓冲区 / 输出字符串变量
 * @param maxLen 最大长度
 */
void readEEPROM(int address, char* buf, size_t maxLen) {
    size_t i = 0;
    for(; i < maxLen-1; i++) {
        char c = ESP_EEPROM.read(address + i);
        if(c == '\0') break;
        buf[i] = c;
    };
    buf[i] = '\0';
}