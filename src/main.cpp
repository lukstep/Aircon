#include <iostream>

#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"

#include <logger.hpp>
#include <wifi.hpp>
#include <rtc.hpp>
#include <ntp.hpp>

void enable_debug()
{
#ifndef NDEBUG
    // workaround for CMSIS-DAP,
    // see: https://github.com/raspberrypi/pico-sdk/issues/1152
    timer_hw->dbgpause = 0;
#endif
}

extern class logging::Logger* logger;
constexpr int LED_PIN = 24;

void startup()
{
    stdio_init_all();
    enable_debug();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    rtc::init();

    bool is_wifi_connected = wifi::init(WIFI_SSID, WIFI_PASSWORD);

    if (is_wifi_connected) {
        ntp::Client ntpClient;
        logging::INFO() << "Sync RTC via NTP\n";
        if (ntpClient.syncTime()) {
            rtc::setTime(ntpClient.getTime());
            logging::INFO() << "RTC synced!\n";
        }
    }
}

int main()
{
    auto l = logging::Logger(logging::Logger::loggerType::uart);
    logger = &l;

    startup();

    while(1)
    {
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
        gpio_put(LED_PIN, 1);
        logging::INFO() << "Hello Word\n";
        sleep_ms(1000);
    }
}