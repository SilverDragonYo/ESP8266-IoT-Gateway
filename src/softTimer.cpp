#include "config.h"

SoftTimer::SoftTimer(unsigned long interval)
    :interval(interval), lastTick(0) {

}

bool SoftTimer::expired() {
    unsigned now = millis();
    if(now - lastTick >= interval) {
        lastTick = now;
        return true;
    }
    return false;
}

void SoftTimer::reset() {
    lastTick = millis();
}

void SoftTimer::setInterval(unsigned long interval) {
    this->interval = interval;
}
