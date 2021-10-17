//Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPSERVER_REQUESTHANDLER_H
#define TCPSERVER_REQUESTHANDLER_H

#include <string>
#include <nlohmann/json.hpp>

class RequestHandler {
private:
    static std::string exec(const char *cmd);
public:
    static nlohmann::json handle(const std::string& request, bool& connected);
};

#endif //TCPSERVER_REQUESTHANDLER_H
