// Copyright 2021 byteihq <kotov038@gmail.com>

#include <ConsoleHandler.h>
#include <HandleConnection.h>
#include <NetworkCommunication.h>
#include <nlohmann/json.hpp>

void ConsoleHandler::handle(std::string &input) {
    auto sInput = splitInput(input);
    if (sInput[0] == "MSG") {
        if (sInput.size() > 1) {
            nlohmann::json msg;
            std::string data;
            if (sInput[1] == "@important") {
                for (auto iter = sInput.begin() + 2; iter < sInput.end(); ++iter) {
                    data += *iter + " ";
                }
                data.erase(data.end() - 1);
                msg = {
                        {"sender", "server"},
                        {"type",   Requests::Msg},
                        {"data",   data},
                        {"status", Status::Important}
                };
            } else {
                for (auto iter = sInput.begin() + 1; iter < sInput.end(); ++iter) {
                    data += *iter + " ";
                }
                data.erase(data.end() - 1);
                msg = {
                        {"sender", "server"},
                        {"type",   Requests::Msg},
                        {"data",   data},
                        {"status", Status::UnImportant}
                };
            }
            HandleConnection::sendAll(msg.dump());
        }
    }
}

std::vector<std::string> ConsoleHandler::splitInput(std::string &input) {
    std::string delimiter = " ";
    size_t pos = 0;
    std::vector<std::string> result;
    size_t index = 0;
    while (index < 2 && (pos = input.find(delimiter)) != std::string::npos) {
        result.push_back(input.substr(0, pos));
        input.erase(0, pos + delimiter.size());
        ++index;
    }
    result.push_back(input);
    return result;
}
