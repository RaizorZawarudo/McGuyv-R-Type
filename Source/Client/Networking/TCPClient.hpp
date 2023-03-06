/*
** EPITECH PROJECT, 2023
** B-CPP-500-BER-5-2-rtype-alban.de-tourtier
** File description:
** TCPClient
*/

#ifndef TCPCLIENT_HPP_
#define TCPCLIENT_HPP_

#include <boost/array.hpp>
#include "../../../../lib/asio.hpp"
#include <iostream>

class TCPClient {
public:
  TCPClient(const std::string &, const std::string &port);
  ~TCPClient(){};
  void receive_data();

private:
  boost::asio::io_context _ioContext;
  boost::asio::ip::tcp::resolver _resolver;
  boost::asio::ip::tcp::socket _socket;
};

#endif /* !TCPCLIENT_HPP_ */
