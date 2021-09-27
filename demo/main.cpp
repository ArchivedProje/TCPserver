#include <iostream>
#include <Server.h>
#include <Logger.h>

int main() {
    try {
        Logger logger("log/mainLog.log");
        logger.log("Creating ioService", __FILE__, __LINE__);
        boost::asio::io_service ioService;
        logger.log("ioService succesfully created", __FILE__, __LINE__);
        Server server(ioService, logger);
        ioService.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
