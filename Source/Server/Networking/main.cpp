#include "Server.hpp"
#include <iostream>

int main(int ac, char **av) {
    try {
        boost::asio::io_context ioContext;
        Server server;
        while (true) {
            
            server.send("merde");
        }
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }
    return 0;
}
