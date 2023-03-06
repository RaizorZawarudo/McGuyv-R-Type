/*
** EPITECH PROJECT, 2023
** B-CPP-500-BER-5-2-rtype-alban.de-tourtier
** File description:
** TCPServer
*/

#include "TCPServer.hpp"

std::string make_daytime_string() {
  std::time_t now = std::time(0);
  return std::ctime(&now);
}

TCPServer::TCPServer(boost::asio::io_context &ioContext, unsigned int port)
    : _ioContext(ioContext),
      _acceptor(ioContext, boost::asio::ip::tcp::endpoint(
                               boost::asio::ip::tcp::v4(), port)) {
  startAccept();
  std::cout << "TCP Server listening on port " << port << std::endl;
}

TCPServer::~TCPServer() {}

void TCPServer::startAccept() {
  TCPConnection::pointer newConnetion = TCPConnection::create(_ioContext);
  _acceptor.async_accept(newConnetion->socket(),
                         boost::bind(&TCPServer::handleAccept, this,
                                     newConnetion,
                                     boost::asio::placeholders::error));
}

void TCPServer::handleAccept(TCPConnection::pointer newConnection,
                   const boost::system::error_code &error) {
  if (!error) {
    newConnection->start();
  }

  startAccept();
}

// TCPConnection class

TCPConnection::TCPConnection(boost::asio::io_context &ioContext)
    : _socket(ioContext) {}

TCPConnection::~TCPConnection() {}

TCPConnection::pointer TCPConnection::create(boost::asio::io_context &ioContext) {
  return TCPConnection::pointer(new TCPConnection(ioContext));
}

boost::asio::ip::tcp::socket& TCPConnection::socket() {
  return _socket;
}

void TCPConnection::start() {
  _message = make_daytime_string();

  boost::asio::async_write(_socket, boost::asio::buffer(_message),
                           boost::bind(&TCPConnection::handleWrite, shared_from_this(),
                                       boost::asio::placeholders::error,
                                       boost::asio::placeholders::bytes_transferred));
}

void TCPConnection::handleWrite(const boost::system::error_code &error,
                                size_t bytesTransferred) {
  if (!error) {
    std::cout << "Sent " << bytesTransferred << " bytes" << std::endl;
  }
}

