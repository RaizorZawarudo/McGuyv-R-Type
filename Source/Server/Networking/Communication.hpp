/*
** EPITECH PROJECT, 2023
** B-CPP-500-BER-5-2-rtype-alban.de-tourtier
** File description:
** Communication
*/

#ifndef COMMUNICATION_HPP_
#define COMMUNICATION_HPP_

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <mutex>
#include <vector>
#include <map>
#include "MessageQueue.hpp"

class Communication {
    public:
        Communication(boost::asio::io_context &ioContext) {
            _messageQueue = std::make_shared<MessageQueue<boost::array<char, 1024>>>();
        };
        ~Communication() {};
        virtual void receive() = 0;
        virtual void send(const std::string &message) = 0;
        std::vector<boost::array<char, 1024>> getMessages() {
            return _messageQueue->getMessages();
        };

    protected:
        std::shared_ptr<MessageQueue<boost::array<char, 1024>>> _messageQueue;
    
    private:
        std::map<int, std::string> _messages;
};

#endif /* !COMMUNICATION_HPP_ */
