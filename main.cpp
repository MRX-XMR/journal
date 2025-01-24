
#include <iostream>
#include <thread>
#include <atomic>
#include <string>
#include "Logger.h"

std::atomic<bool> running(true);
Logger logger("log.txt", LogLevel::INFO);

void logMessage(const std::string &message, LogLevel level) {
    logger.log(message, level);
}

void userInput() {
    while (running) {
        std::string message;
        std::cout << "Введите сообщение: ";
        std::getline(std::cin, message);
        if (message.empty()) continue;

        std::cout << "Введите уровень (0 - DEBUG, 1 - INFO, 2 - ERROR) (по умолчанию INFO): ";
        int levelInput;
        std::string input;
        std::getline(std::cin, input);  // Считываем строку для ввода уровня

        if (input.empty()) {  // Если ничего не введено, устанавливаем уровень по умолчанию
            levelInput = 1;  // Уровень INFO
        } else {
            try {
                levelInput = std::stoi(input);  // Преобразуем ввод в целое число
                if (levelInput < 0 || levelInput > 2) {
                    std::cout << "Введите корректный уровень важности" << std::endl;
                    continue;
                }
            } catch (...) {
                std::cout << "Ошибка ввода. Установка уровня по умолчанию: INFO" << std::endl;
                levelInput = 1;  // Уровень INFO по умолчанию при ошибке ввода
            }
        }

        LogLevel level = static_cast<LogLevel>(levelInput);

        std::thread(logMessage, message, level).detach();
    }
}

int main() {
    std::thread userThread(userInput);
    
    std::cout << "Приложение работает. Нажмите Ctrl+C для выхода." << std::endl;
    userThread.join();
    
    running = false;
    return 0;
}
