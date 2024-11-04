#include "logger.hpp"

class logging::Logger* logger = nullptr;

namespace logging {

void Logger::write(const char* string, [[maybe_unused]] size_t length) {
    // TODO add logging via UDP
    switch (type) {
        case loggerType::uart:
            for (size_t i = 0; i < length; i++) {
                putchar(string[i]);
            }
            break;
        case loggerType::udp:
            printf("UDP not available yet!");
            break;
    }
}

Logger& INFO() {
    assert(logger);
    *logger << rtc::getTime() << " [INF] ";
    return *logger;
}

Logger& ERROR() {
    assert(logger);
    *logger << rtc::getTime() << " [ERR] ";
    return *logger;
}

Logger& RS485() {
    assert(logger);
    return *logger;
}

}  // namespace logging
