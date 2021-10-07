#include <Server.h>
#include <Logger.h>
#include <memory>

int main() {
    exec("python3 Python/MYSQLmain.py AUTH user1 1u23456");

    try {
        Logger::log("Creating ioService", __FILE__, __LINE__);
        std::shared_ptr<boost::asio::io_service> ioService(new boost::asio::io_service);
        Logger::log("ioService succesfully created", __FILE__, __LINE__);
        Server server(ioService);
        ioService->run();
    }
    catch (std::exception &e) {
        Logger::log(e.what(), __FILE__, __LINE__);
    }
    return 0;
}
