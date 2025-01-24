// logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <mutex>
#include <ctime>

enum class LogLevel {
    DEBUG,
    INFO,
    ERROR
};

class Logger {
public:
    Logger(const std::string &filename, LogLevel defaultLevel);
    ~Logger();
    
    void log(const std::string &message, LogLevel level = LogLevel::INFO);
    
    void setDefaultLogLevel(LogLevel level);

private:
    std::string getCurrentTime();
    
    std::ofstream logFile;
    LogLevel defaultLogLevel;
    std::mutex mtx;
};

#endif // LOGGER_H
