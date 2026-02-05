#pragma once
#ifndef SOFT_TIMER_H
#define SOFT_TIMER_H

#include "config.h"

class SoftTimer {
    public:
        SoftTimer(unsigned long interval);
        bool expired();
        void reset();
        void setInterval(unsigned long interval);
    private:
        unsigned long interval;
        unsigned long lastTick;

};

#endif