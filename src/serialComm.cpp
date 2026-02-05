#include "config.h"

float data[3] = {0.0f, 0.0f, 0.0f}; // 全局数据：氧含量、pH、水温

bool receiveDataFrom2560(){
    while (Serial.available() >= 8){
        if (Serial.read() == FRAME_HEAD){
            uint8_t frameType = Serial.read();

            if (frameType == DATA_FRAME){
                Serial.print("has received msg head ");
                uint8_t raw[6];
                for (int i = 0;i < 6;i++){
                    if (!Serial.available()) return false;
                    raw[i] = Serial.read();
                    Serial.print(raw[i]);
                    Serial.print(" ");
                }
                Serial.println("");
                delay(100);
                if (Serial.read() == FRAME_TAIL){
                    Serial.println("has received msg tail");
                    for (int i = 0;i < DATA_LEN;i++){
                        float x = raw[i * 2];
                        float y = raw[i * 2 + 1];
                        data[i] = x + y / 100;
                        Serial.print(data[i],2);
                        Serial.print(" ");
                    }
                    Serial.println("");
                    return true;           
                }
            } else if (frameType == FLAG_FRAME) {
                while (!Serial.available()) return false;
                int flag = Serial.read();
                if (!Serial.available()) return false;
                if (Serial.read() == FRAME_TAIL){
                    Serial.print("has received command:");
                    Serial.println(flag);
                    sendFlagToServer(flag);
                    return true;
                }
            }
        }
    }
    return false;
}

void sendDataTo2560(uint8_t cmd){
    Serial.write(FRAME_HEAD);  // 0xFF
    Serial.write(CMD_FRAME); 
    Serial.write(cmd);         // 具体命令：0x0A开,0x0B关
    Serial.write(FRAME_TAIL);  // 0xCB
    Serial.print("has send command:");
    Serial.println(cmd); 
}
