// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H

#include <string>
#include <fstream>

class Logger {
private:
    Logger() {}

    Logger(const Logger &) = delete;

    Logger &operator=(Logger &) = delete;

    static std::ofstream file_;
public:
    static void log(const std::string &msg, const std::string &fileName, size_t lineNumber);
};

#endif //LOGGER_LOGGER_H
