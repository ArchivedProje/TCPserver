// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPSERVER_CONSOLEHANDLER_H
#define TCPSERVER_CONSOLEHANDLER_H

#include <string>
#include <vector>

class ConsoleHandler {
private:
    static std::vector<std::string> splitInput(std::string &input);

public:
    static void handle(std::string &input);
};

#endif //TCPSERVER_CONSOLEHANDLER_H
