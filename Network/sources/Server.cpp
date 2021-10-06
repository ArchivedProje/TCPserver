// Copyright 2021 byteihq <kotov038@gmail.com>

#include <Server.h>
#include <Logger.h>

void Server::startAccept() {
    Logger::log("Listening for new connection", __FILE__, __LINE__);
    HandleConnection::pointer connection = HandleConnection::create(*ioService_);
    acceptor_.async_accept(*connection->getSocket(),
                           boost::bind(&Server::handleAccept, this, connection,
                                       boost::asio::placeholders::error));
}

Server::Server(const std::shared_ptr<boost::asio::io_service>& ioService) : ioService_(ioService), acceptor_(*ioService,
                                                                                      tcp::endpoint(
                                                                                              tcp::v4(),
                                                                                              2001)) {
    Logger::log("Starting server", __FILE__, __LINE__);
    startAccept();
}

void Server::handleAccept(HandleConnection::pointer &connection, const boost::system::error_code &err) {
    if (!err) {
        connection->start();
    }
    startAccept();
}
