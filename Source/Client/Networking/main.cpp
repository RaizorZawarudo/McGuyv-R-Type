/*
** EPITECH PROJECT, 2023
** Networking
** File description:
** main
*/

#include "UDPClient.hpp"
#include <cstdlib>

#include <iostream>
#include <cstring>

// Function to convert unsigned long long integer to an array of bytes
void ullToBytes(unsigned long long num, unsigned char* bytes) {
    // Copy the bytes of the integer to the byte array
    std::memcpy(bytes, &num, sizeof(num));
}

int main() {
    unsigned long long num = 1234567890123456789ULL;
    unsigned char bytes[sizeof(num)];
    
    // Call the function to convert the integer to bytes
    ullToBytes(num, bytes);
    
    // Print the byte array
    for (int i = 0; i < sizeof(num); i++) {
        std::cout << static_cast<int>(bytes[i]) << " ";
    }
    
    return 0;
}

// int main(int argc, char **argv) {
//   try {
//     if (argc != 3) {
//       std::cerr << "Usage: client <host> <port>" << std::endl;
//       return 1;
//     }
//     boost::asio::io_context ioContext;
//     UDPClient udpClient(ioContext, std::string(argv[1]),
//                         strtoul(argv[2], nullptr, 10));
//     while (true) {
//       udpClient.receive();
//     }
//   } catch (std::exception &err) {
//     std::cerr << err.what() << std::endl;
//   }
//   return 0;
// }
