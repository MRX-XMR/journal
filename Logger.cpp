#include "Logger.h"

Logger::Logger(const std::string &filename, LogLevel defaultLevel) 
    : defaultLogLevel(defaultLevel) {
    logFile.open(filename, std::ios_base::app);
    if (!logFile.is_open()) {
        throw std::runtime_error("Failed to open log file");
    }
}
Logger::~Logger(){
    if(logFile.is_open()){
        logFile.close();
    }
}

void Logger::log(const std::string &message, LogLevel level) {
    if (static_cast<int>(level) < static_cast<int>(defaultLogLevel)) {
        return;
    }

    std::lock_guard<std::mutex> guard(mtx);
    logFile << getCurrentTime() << " [" << static_cast<int>(level) << "] " << message << std::endl;
}

void Logger::setDefaultLogLevel(LogLevel level) {
    std::lock_guard<std::mutex> guard(mtx);
    defaultLogLevel = level;
}

std::string Logger::getCurrentTime() {
    std::time_t now = std::time(nullptr);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buf);
}
