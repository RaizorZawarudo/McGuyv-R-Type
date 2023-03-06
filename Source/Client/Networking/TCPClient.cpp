/*
** EPITECH PROJECT, 2023
** B-CPP-500-BER-5-2-rtype-alban.de-tourtier
** File description:
** TCPClient
*/

#include "TCPClient.hpp"

TCPClient::TCPClient(const std::string &host, const std::string &port)
    : _ioContext(), _resolver(_ioContext), _socket(_ioContext)
{
    boost::asio::ip::tcp::resolver::results_type endpoints = _resolver.resolve(host, port);
    boost::asio::connect(_socket, endpoints);
}

void TCPClient::receive_data()
{
    boost::array<char, 128> buffer;
    boost::system::error_code error;

    size_t len = _socket.read_some(boost::asio::buffer(buffer), error);

    if (error == boost::asio::error::eof)
    {
        // Connection closed cleanly by peer.
        std::cout << "Connection closed cleanly by peer." << std::endl;
    }
    else if (error)
    {
        // Some other error.
        throw boost::system::system_error(error);
    }

    std::cout.write(buffer.data(), len);
    std::cout << std::endl;
}

int main()
{
    TCPClient client("127.0.0.1", "8080");
    while (true)
        client.receive_data();
    return 0;
}
