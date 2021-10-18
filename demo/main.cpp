#include <Server.h>
#include <Logger.h>
#include <ConsoleHandler.h>
#include <memory>
#include <thread>
#include <string>
#include <iostream>

int main() {
    try {
        Logger::log("Creating ioService", __FILE__, __LINE__);
        std::shared_ptr<boost::asio::io_service> ioService(new boost::asio::io_service);
        Logger::log("ioService succesfully created", __FILE__, __LINE__);
        Server server(ioService);
        std::thread th([](){
            while (true) {
                std::string input;
                std::getline(std::cin, input);
                ConsoleHandler::handle(input);
            }
        });
        th.detach();
        ioService->run();
    }
    catch (std::exception &e) {
        Logger::log(e.what(), __FILE__, __LINE__);
    }
    return 0;
}
