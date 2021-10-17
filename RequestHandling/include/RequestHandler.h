//Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPSERVER_REQUESTHANDLER_H
#define TCPSERVER_REQUESTHANDLER_H

#include <string>
#include <nlohmann/json.hpp>
#include <NetworkCommunication.h>

class RequestHandler {
private:
    static std::string exec(const char *cmd);

public:
    static std::pair<Requests, nlohmann::json> handle(const std::string &request);
};

#endif //TCPSERVER_REQUESTHANDLER_H
