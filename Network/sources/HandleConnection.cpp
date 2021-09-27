// Copyright 2021 byteihq <kotov038@gmail.com>

#include <HandleConnection.h>
#include <nlohmann/json.hpp>
#include <Logger.h>

HandleConnection::HandleConnection(boost::asio::io_service &io_service, Logger& logger) : socket_(
        std::make_shared<tcp::socket>(io_service)), logger_(logger) {}

HandleConnection::pointer HandleConnection::create(boost::asio::io_service &io_service, Logger& logger) {
    return pointer(new HandleConnection(io_service, logger));
}

void HandleConnection::getMessage() {
    logger_.log("Getting new message", __FILE__, __LINE__);
    auto self(shared_from_this());
    boost::asio::async_read_until(*socket_, data_, '\n',
                                  [this, self](boost::system::error_code ec, std::size_t length) {
                                      if (!ec) {
                                          std::istream ss(&data_);
                                          std::string sData;
                                          std::getline(ss, sData);
                                          logger_.log("Message - " + sData, __FILE__, __LINE__);
                                      } else {
                                          logger_.log("Error receiving message", __FILE__, __LINE__);
                                      }
                                  });
}

void HandleConnection::sendMessage(const std::string &msg) {
    auto self(shared_from_this());
    boost::asio::async_write(*socket_, boost::asio::buffer(msg + '\n', msg.size() + 1),
                             [this, self, msg](boost::system::error_code ec, std::size_t /*length*/) {
                                 if (!ec) {
                                     getMessage();
                                 } else {
                                 }
                             });
}

void HandleConnection::start() {
    ip_ = socket_->remote_endpoint().address();
    logger_.log("New connection " + ip_.to_string(), __FILE__, __LINE__);
    getMessage();
}

std::shared_ptr<tcp::socket> HandleConnection::getSocket() const {
    return socket_;
}
