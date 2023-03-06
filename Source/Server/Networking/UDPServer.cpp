/*
** EPITECH PROJECT, 2023
** RType
** File description:
** UDPServer
*/

#include "UDPServer.hpp"

UDPServer::UDPServer(boost::asio::io_context &io, unsigned int port) : Communication(io),  _port(port), _clock(io), 
    _socket(io, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)) 
    {
    std::cout << "UDP protocol created" << std::endl;
    _clientsEndpoint.clear();
    receive();
    std::cout << "UDP protocol listening on port " << _port << std::endl;
}

UDPServer::~UDPServer() {}

void UDPServer::receive() {
    _socket.async_receive_from(
        boost::asio::buffer(_recvBuffer), _senderEndpoint,
        boost::bind(&UDPServer::handleReceive, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

void UDPServer::handleReceive(const boost::system::error_code &error,
                              std::size_t bytesTransfered) {
    bool inVector = false;
    
    if (!error) {
        for (auto ele : _clientsEndpoint) {
            if (ele.endpoint == _senderEndpoint)
                inVector = true;
        }
        if (inVector == false) {
            client_t client;
            client.endpoint = _senderEndpoint;
            client.id = _clientsEndpoint.size();
            _clientsEndpoint.push_back(client);
            char *package = _serializator.createPackageSetClientId(serializator::Header::menu, client.id);
            sentToClient(client.id, package, SIZE_ID_CLIENT);
            auto msg = _serializator.bytesToStruct(package);
            std::cout << "New client connected with id: " << msg.getClientHash() << std::endl;
            delete package;
        }
        _messageQueue->pushMessage(_recvBuffer);
        receive();
    }
}

int UDPServer::getConnectedClients() {
    return _clientsEndpoint.size();
}

void UDPServer::send(const std::string& message) {
    for (auto ele : _clientsEndpoint) {
        _socket.async_send_to(
            boost::asio::buffer(message), ele.endpoint,
            boost::bind(&UDPServer::handleSend, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    }
}

void UDPServer::send(const char *message, size_t size) {
    for (auto ele : _clientsEndpoint) {
        _socket.async_send_to(
            boost::asio::buffer(message, size), ele.endpoint,
            boost::bind(&UDPServer::handleSend, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    }
}

void UDPServer::sentToClient(int index, char *message, size_t size) {
    _socket.async_send_to(
        boost::asio::buffer(message, size), _clientsEndpoint[index].endpoint,
        boost::bind(&UDPServer::handleSend, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

void UDPServer::handleSend(const boost::system::error_code &error,
                           std::size_t bytesTransfered) {}
