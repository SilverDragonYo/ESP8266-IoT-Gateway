#include "config.h"

/**
 * @brief 初始化定时器间隔
 * 
 * @param interval 定时器间隔，单位毫秒
 */
SoftTimer::SoftTimer(unsigned long interval)
    :interval(interval), lastTick(0) {

}

/**
 * @brief 检查定时器是否到期
 * 
 */
bool SoftTimer::expired() {
    unsigned now = millis();
    if(now - lastTick >= interval) {
        lastTick = now;
        return true;
    }
    return false;
}

/**
 * @brief 重置定时器
 * 
 */
void SoftTimer::reset() {
    lastTick = millis();
}

/**
 * @brief 重新设置定时器间隔
 * 
 * @param interval 定时器间隔，单位毫秒
 */
void SoftTimer::setInterval(unsigned long interval) {
    this->interval = interval;
}
