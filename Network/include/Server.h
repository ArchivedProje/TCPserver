// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPSERVER_SERVER_H
#define TCPSERVER_SERVER_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>
#include <HandleConnection.h>
#include <Logger.h>

using boost::asio::ip::tcp;

class Server {
private:
    friend class HandleConnection;

    boost::asio::io_service& ioService_;
    tcp::acceptor acceptor_;
    Logger& logger_;
    void startAccept();

    void handleAccept(HandleConnection::pointer &connection, const boost::system::error_code &err);

public:
    explicit Server(boost::asio::io_service& ioService, Logger& logger);
};

#endif //TCPSERVER_SERVER_H
