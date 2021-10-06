// Copyright 2021 byteihq <kotov038@gmail.com>

#include <RequestHandler.h>
#include <nlohmann/json.hpp>

std::string RequestHadler::handle(const std::string &request) {
    nlohmann::json jsonRequest = nlohmann::json::parse(request);
    if (jsonRequest["type"] == "auth") {
        // working with db
    }
    return std::string();
}
