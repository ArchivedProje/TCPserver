// Copyright 2021 byteihq <kotov038@gmail.com>

#include <HandleConnection.h>
#include <RequestHandler.h>
#include <Logger.h>

HandleConnection::HandleConnection(boost::asio::io_service &io_service) : socket_(
        std::make_shared<tcp::socket>(io_service)) {}

HandleConnection::pointer HandleConnection::create(boost::asio::io_service &io_service) {
    return pointer(new HandleConnection(io_service));
}

void HandleConnection::getMessage() {
    Logger::log("Getting new message", __FILE__, __LINE__);
    auto self(shared_from_this());
    boost::asio::async_read_until(*socket_, data_, '\n',
                                  [this, self](boost::system::error_code ec, std::size_t length) {
                                      if (!ec) {
                                          std::istream ss(&data_);
                                          std::string sData;
                                          std::getline(ss, sData);
                                          Logger::log("Message - " + sData, __FILE__, __LINE__);
                                          Logger::log("Handling new message", __FILE__, __LINE__);
                                          sendMessage(RequestHadler::handle(sData).dump());
                                      } else {
                                          Logger::log("Error receiving message", __FILE__, __LINE__);
                                      }
                                  });
}

void HandleConnection::sendMessage(const std::string &msg) {
    auto self(shared_from_this());
    boost::asio::async_write(*socket_, boost::asio::buffer(msg + '\n', msg.size() + 1),
                             [this, self, msg](boost::system::error_code ec, std::size_t /*length*/) {
                                 if (!ec) {
                                     Logger::log("Message successfully sent", __FILE__, __LINE__);
                                     getMessage();
                                 } else {
                                     Logger::log("Failed send message", __FILE__, __LINE__);
                                 }
                             });
}

void HandleConnection::start() {
    ip_ = socket_->remote_endpoint().address();
    Logger::log("New connection " + ip_.to_string(), __FILE__, __LINE__);
    getMessage();
}

std::shared_ptr<tcp::socket> HandleConnection::getSocket() const {
    return socket_;
}
