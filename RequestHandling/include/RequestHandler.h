//Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPSERVER_REQUESTHANDLER_H
#define TCPSERVER_REQUESTHANDLER_H

#include <string>

class RequestHadler {
public:
    static std::string handle(const std::string& request);
};

#endif //TCPSERVER_REQUESTHANDLER_H
