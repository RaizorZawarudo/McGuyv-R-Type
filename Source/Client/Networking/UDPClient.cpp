/*
** EPITECH PROJECT, 2023
** RType
** File description:
** UDPClient
*/

#include "UDPClient.hpp"

UDPClient::UDPClient(boost::asio::io_context &ioContext, std::string host,
                     unsigned int port)
    : Communication(ioContext), _serverEndpoint(boost::asio::ip::address::from_string(host), port),
      _socket(ioContext) {
    _socket.open(boost::asio::ip::udp::v4());
    _socket.send_to(boost::asio::buffer(boost::array<char, 1>({{10}})),
        _serverEndpoint);
}

UDPClient::~UDPClient() {}

void UDPClient::receive() {
    std::size_t len = _socket.receive_from(boost::asio::buffer(_recvBuffer), _serverEndpoint);
    _messageQueue->pushMessage(_recvBuffer);
}

void UDPClient::send(const std::string &msg) {
  _socket.send_to(boost::asio::buffer(msg), _serverEndpoint);
}

void UDPClient::send(const char *message, size_t size) {
  _socket.send_to(boost::asio::buffer(message, size), _serverEndpoint);
}
