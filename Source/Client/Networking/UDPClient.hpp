/*
** EPITECH PROJECT, 2023
** RType
** File description:
** UDPClient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

#include "boost/asio.hpp"
#include "boost/array.hpp"
#include <iostream>
#include <string>
#include <thread>
#include "../../Server/Networking/Communication.hpp"
#include "../../Server/Networking/protocol/Serializator.hpp"

class UDPClient : public Communication {
    public:
        UDPClient(boost::asio::io_context& ioContext, std::string host = std::string("127.0.0.1"), unsigned int port = 1313);
        ~UDPClient();
        void receive() override;
        void send(const std::string &msg) override;
        void send(const char *message, size_t size);

    private:
        boost::asio::ip::udp::endpoint _serverEndpoint;
        boost::asio::ip::udp::socket _socket;
        boost::array<char, 1024> _recvBuffer;
        std::thread _threadClient;
        Serializator _serializator;
};

#endif /* !UDPCLIENT_HPP_ */
