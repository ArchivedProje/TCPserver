
#ifndef TCPSERVER_LOGGER_H
#define TCPSERVER_LOGGER_H

#include <string>
#include <fstream>

class Logger {
private:
    std::ofstream file_;
public:
    void log(const std::string& msg, const std::string& fileName, size_t lineNumber);

    explicit Logger(const std::string& filename);
};

#endif //TCPSERVER_LOGGER_H
