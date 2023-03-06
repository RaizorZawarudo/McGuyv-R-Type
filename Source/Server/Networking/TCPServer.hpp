/*
** EPITECH PROJECT, 2023
** B-CPP-500-BER-5-2-rtype-alban.de-tourtier
** File description:
** TCPServer
*/

#ifndef TCPSERVER_HPP_
#define TCPSERVER_HPP_

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <ctime>
#include <iostream>
#include <string>

class TCPConnection : public boost::enable_shared_from_this<TCPConnection> {

public:
  TCPConnection(boost::asio::io_context &io_context);
  ~TCPConnection();

  typedef boost::shared_ptr<TCPConnection> pointer;
  static pointer create(boost::asio::io_context &io_context);
  boost::asio::ip::tcp::socket &socket();
  void start();

private:
  boost::asio::ip::tcp::socket _socket;
  std::string _message;
  TCPConnection(boost::asio::io_context &io_context);
  void handleWrite(const boost::system::error_code &error,
                   size_t bytes_transferred);
};

class TCPServer {
public:
  TCPServer(boost::asio::io_context &ioContext, unsigned int port = 1313);
  ~TCPServer();

private:
  void startAccept();
  void handleAccept(TCPConnection::pointer newConnection,
                    const boost::system::error_code &error);

  boost::asio::io_context &_ioContext;
  boost::asio::ip::tcp::acceptor _acceptor;
};

#endif /* !TCPSERVER_HPP_ */
