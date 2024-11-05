#include "wifi.hpp"
#include <logger.hpp>
#include <pico/cyw43_arch.h>
#include <pico/stdlib.h>
#include <rtc.hpp>

namespace wifi {

bool init(const char* ssid, const char* password) {
    logging::INFO() << "Start WiFi connection\n";

    if (cyw43_arch_init_with_country(CYW43_COUNTRY_POLAND)) {
        logging::ERROR() << "Failed to init!\n";
        return false;
    }

    cyw43_arch_enable_sta_mode();

    logging::INFO() << "try to connect ssid:" << ssid <<"\n";

    constexpr int32_t connectionTimeoutMs = 10'000;
    if (cyw43_arch_wifi_connect_timeout_ms(
            ssid, password, CYW43_AUTH_WPA2_AES_PSK, connectionTimeoutMs)) {
        logging::INFO() << "Failed to connect to network!\n";
        return false;
    }

    logging::INFO() << "Connected to " << ssid << "\n";
    return true;
}

void deinit() {
    cyw43_arch_deinit();
}

}  // namespace wifi
