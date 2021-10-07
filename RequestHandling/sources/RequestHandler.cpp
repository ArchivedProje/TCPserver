// Copyright 2021 byteihq <kotov038@gmail.com>

#include <RequestHandler.h>
#include <nlohmann/json.hpp>

std::string RequestHadler::exec(const char *cmd) {
    char buffer[128];
    std::string result;
    FILE *pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL)
            result += buffer;
    }
    catch (...) {
        pclose(pipe);
        throw;
    }

    pclose(pipe);
    return result;
}

std::string RequestHadler::handle(const std::string &request) {
    nlohmann::json jsonRequest = nlohmann::json::parse(request);
    if (jsonRequest["type"] == "auth") {
        // working with db
        RequestHadler::exec("hellp");
    }
    return std::string();
}
