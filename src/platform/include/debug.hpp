#pragma once
#include "hardware/timer.h"

void enable_debug()
{
#ifndef NDEBUG
    // workaround for CMSIS-DAP,
    // see: https://github.com/raspberrypi/pico-sdk/issues/1152
    timer_hw->dbgpause = 0;
#endif
}