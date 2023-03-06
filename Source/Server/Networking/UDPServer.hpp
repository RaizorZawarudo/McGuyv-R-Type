/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Server
*/

#ifndef UDPSERVER_HPP_
#define UDPSERVER_HPP_

#include <boost/asio.hpp>
#include "boost/bind/bind.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/array.hpp"
#include "iostream"
#include "Communication.hpp"
#include "protocol/Serializator.hpp"

typedef struct client {
    boost::asio::ip::udp::endpoint endpoint;
    unsigned long long id;
} client_t;

class UDPServer: public Communication {
    public:
        UDPServer(boost::asio::io_context& io, unsigned int port = 1313);
        ~UDPServer();
        void send(const std::string& message) override;
        void send(const char *message, size_t size);
        int getConnectedClients();
        void setConnectedClients();
        void receive() override;
        int getClientsEndpoint() const { return _clientsEndpoint.size(); }
        int getClientId(int index) { return _clientsEndpoint[index].id; };
        void sentToClient(int index, char *message, size_t size);

    private:
        void handleReceive(const boost::system::error_code& error, std::size_t bytesTransfered);
        void handleSend(const boost::system::error_code& error, std::size_t bytesTransfered);

        Serializator _serializator;
        boost::array<char, 1024> _recvBuffer;
        boost::asio::ip::udp::socket _socket;
        boost::asio::ip::udp::endpoint _senderEndpoint;
        std::vector<client_t> _clientsEndpoint;
        boost::asio::steady_timer _clock;
        unsigned int _port;


};

#endif /* !UDPSERVER_HPP_ */
