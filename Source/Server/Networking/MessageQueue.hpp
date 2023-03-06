/*
** EPITECH PROJECT, 2023
** B-CPP-500-BER-5-2-rtype-alban.de-tourtier
** File description:
** MessageQueue
*/

#ifndef MESSAGEQUEUE_HPP_
#define MESSAGEQUEUE_HPP_

#include "boost/array.hpp"
#include <queue>

template <class T>
class MessageQueue {
    public:
        MessageQueue() {};
        ~MessageQueue() {};

        void pushMessage(T message)
        {
            std::lock_guard<std::recursive_mutex> lock(_mutex);
            _messageQueue.push(message);
        }

        T popMessage()
        {
            std::lock_guard<std::recursive_mutex> lock(_mutex);
            T message;
            
            if (!_messageQueue.empty()) {
                message = _messageQueue.front();
                _messageQueue.pop();
                return message;
            }
        }
        
        std::vector<T> getMessages()
        {
            std::lock_guard<std::recursive_mutex> lock(_mutex);
            std::vector<T> messages;

            while (!_messageQueue.empty()) {
                messages.push_back(_messageQueue.front());
                _messageQueue.pop();
            }
            return messages;
        }

    private:
        std::queue<T> _messageQueue;
        std::recursive_mutex _mutex;
};

#endif /* !MESSAGEQUEUE_HPP_ */
