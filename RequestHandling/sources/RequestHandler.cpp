// Copyright 2021 byteihq <kotov038@gmail.com>

#include <RequestHandler.h>
#include <Logger.h>

std::string RequestHandler::exec(const char *cmd) {
    char buffer[128];
    std::string result;
    FILE *pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL)
            result += buffer;
    } catch (...) {
        pclose(pipe);
        throw;
    }

    pclose(pipe);
    result.erase(result.end() - 1);
    return result;
}

std::pair<Requests, nlohmann::json> RequestHandler::handle(const std::string &request) {
    nlohmann::json jsonRequest = nlohmann::json::parse(request);
    nlohmann::json reply;
    if (jsonRequest["type"] == Requests::Auth) {
        std::string cmd = "python3 Python/MYSQLmain.py AUTH " + jsonRequest["data"]["login"].get<std::string>() + " " +
                          jsonRequest["data"]["password"].get<std::string>();
        if (RequestHandler::exec(cmd.c_str()) == "True") {
            reply = {
                    {"sender", "server"},
                    {"type",   Requests::Auth},
                    {"data",   Replies::Auth::Successful}
            };
        } else {
            reply = {
                    {"sender", "server"},
                    {"type",   Requests::Auth},
                    {"data",   Replies::Auth::Unsuccessful}
            };
        }
    } else if (jsonRequest["type"] == Requests::Msg) {
        Logger::log("New message from " + jsonRequest["sender"].get<std::string>() + " Message: " + jsonRequest["data"].get<std::string>(), __FILE__, __LINE__);
    } else if (jsonRequest["type"] == Requests::Disconnect) {
        Logger::log("Person disconnected", __FILE__, __LINE__);
    } else {
        reply = {
                {"sender", "server"},
                {"type",   Requests::Unknown},
                {"data",   Replies::Unknown::Unknown}
        };
    }
    return {jsonRequest["type"], reply};
}
