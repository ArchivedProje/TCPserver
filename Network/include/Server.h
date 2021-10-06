// Copyright 2021 byteihq <kotov038@gmail.com>

#ifndef TCPSERVER_SERVER_H
#define TCPSERVER_SERVER_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>
#include <HandleConnection.h>

using boost::asio::ip::tcp;

class Server {
private:
    friend class HandleConnection;

    std::shared_ptr<boost::asio::io_service> ioService_;
    tcp::acceptor acceptor_;

    void startAccept();

    void handleAccept(HandleConnection::pointer &connection, const boost::system::error_code &err);

public:
    explicit Server(const std::shared_ptr<boost::asio::io_service>& ioService);
};

#endif //TCPSERVER_SERVER_H
