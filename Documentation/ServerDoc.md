# **Developer documentation Server**

 ## **Introduction**

R type is a classic arcade-style game that has been reimagined as a multiplayer game with the R type game server. The server is built using C++ and Boost.Asio library, providing high-performance networking capabilities to handle multiple players and game sessions. This developer documentation is aimed at helping developers understand the architecture of the R type game server and provide guidance on how to build, customize, and extend it. It covers everything from networking and game logic to security and scaling, providing a comprehensive guide for building a robust and scalable game server. By the end of this documentation, developers will have a solid understanding of how to build a multiplayer game server using C++ and Boost.Asio, with the ability to customize and extend it as needed for their own games.

## **1 - Getting Started**

- Requirement
- Running the server locally
- Connecting to the server

## **2 - Architecture**

- Overview of the R type server architecture
- Components of the server
- Thread Communication

## **3 - Networking**

- Overview of the networking model
- Handling network connections and data transmission

## **4 - Conclusion**

## **1 - Getting Started**

- **Requirement**

To install Conan, you can follow these steps:

1- Download and install Python: Conan is a Python package, so you need to have Python installed on your system. You can download and install Python from the official Python website: https://www.python.org/downloads/

2 - Install pip: Pip is a package manager for Python, and it comes bundled with Python 2.7.9 and later versions. If you have an earlier version of Python, you need to install pip separately. You can do this by running the following command in your terminal or command prompt:

python get-pip.py

3 - Install Conan: Once you have pip installed, you can use it to install Conan by running the following command:

pip install conan

4 - Verify the installation: To verify that Conan has been installed successfully, you can run the following command:

conan --version

This should display the version of Conan that you have installed.

That's it! You now have Conan installed on your system, and you can use it to manage dependencies for your C++ projects.

- **Running the server locally**

You just need to launch this command at the repository root:

./rtype-server

- **Connecting to the server**

You need to launch the client:

./rtype-client

## **2 - Architecture**

- **Overview of the R type server architecture**

The R type server architecture is a design pattern for building multiplayer games that use the UDP protocol for communication. This architecture consists of two main components: a server that updates the state of the game entities and serializes the updated entities to send to clients, and multiple clients that deserialize the package and apply modifications, receive input from users, and send it back to the server.

At its core, the R type server architecture is designed to be lightweight and efficient, allowing for high-speed communication between the server and clients. This is achieved by using the UDP protocol, which is a connectionless protocol that does not require a lot of overhead for establishing and maintaining connections. Instead, each packet sent between the server and clients contains all the necessary information to update the game state and is processed independently by the receiver.

On the server side, the game state is maintained in memory and updated based on input received from clients. The server uses Boost.Asio, a C++ library for network and low-level I/O programming, to handle incoming and outgoing packets. When the game state is updated, the server serializes the updated entities into a packet and sends it to all connected clients.

On the client side, each connected client deserializes the incoming packets and applies the modifications to its local game state. The client then sends input from the user, such as keyboard or mouse events, back to the server. This input is used to update the game state on the server and send updated entities to all clients.

Overall, the R type server architecture is a powerful and flexible approach to building multiplayer games that require high-speed communication between clients and a central server. By using the UDP protocol and Boost.Asio, this architecture can handle a large number of clients and provide a smooth and responsive gaming experience.

- **Components of the server UDP**

This is a C++ class definition for a UDP server that inherits from a base class called "Server". The class has a constructor, a destructor, and three member functions:

- UDPServer: This is the constructor of the class, which takes an io\_context object from the Boost.Asio library as a parameter and an optional port number. It initializes several data members, including a UDP socket, a buffer for receiving data, and a timer for scheduling periodic events.
- ~UDPServer: This is the destructor of the class, which is responsible for cleaning up any resources allocated by the class.
- send: This is a member function that takes a string message as a parameter and sends it to all connected clients.
- receive: This is a member function that starts an asynchronous operation to receive data from a client. It uses a callback function called handleReceive to handle the received data.

The class also has several private member functions:

- handleReceive: This is a callback function that is called when data is received from a client. It takes two parameters: an error code and the number of bytes transferred. It extracts the received data from the buffer and then starts another asynchronous operation to receive more data.
- handleSend: This is a callback function that is called when data is sent to a client. It takes two parameters: an error code and the number of bytes transferred. It does nothing in this implementation.
- \_recvBuffer: This is a buffer for receiving data from clients.
- \_socket: This is a UDP socket used for communication.
- \_senderEndpoint: This is the endpoint of the client that sent the most recent data.
- \_clientsEndpoint: This is a vector of endpoints for all connected clients.
- \_clock: This is a timer used for scheduling periodic events.
- \_port: This is the port number used by the server for communication.

- **Thread Communication**

This is a C++ class definition for a class called "Communication". The class is an abstract base class, meaning that it defines a common interface for its derived classes but cannot be instantiated on its own.

The class has a constructor that takes an io\_context object from the Boost.Asio library as a parameter, and a destructor that does nothing.

The class also has two pure virtual member functions:

- receive: This is a pure virtual function that must be implemented by derived classes. It is responsible for receiving messages from a communication channel.
- send: This is a pure virtual function that must be implemented by derived classes. It is responsible for sending messages through a communication channel.

The class has a protected data member:

- \_messageQueue: This is a shared pointer to a MessageQueue object, which is a thread-safe queue used for storing received messages. It is protected to allow derived classes to access it.

The class also has a private data member:

- \_messages: This is a map that associates an integer key with a string message. It is not used in this implementation and could be removed.

The class also provides a member function:

- getMessages: This function returns a vector of messages received by the communication object. It does this by calling the getMessages function of the \_messageQueue member variable.

## **3 - Networking**

- Overview of the networking model

The networking model for a game in C++ and using Boost.Asio is a high-performance, event-driven networking library that provides a flexible and efficient way to handle network I/O operations. It enables developers to build multiplayer games with low latency and high throughput, while ensuring that the game logic is synchronized across all clients.

In the game networking model, each client connects to the game server using a TCP or UDP socket, depending on the game's requirements. Once connected, the client sends and receives messages from the server, which can include game state updates, player movements, and other game-related information.

Boost.Asio provides a number of features that make it ideal for game networking, including asynchronous I/O operations, thread safety, and support for a wide range of protocols and transports. It also supports both TCP and UDP protocols, allowing developers to choose the appropriate protocol for their game.

One important aspect of the networking model is the synchronization of game state across all clients. This is typically achieved by sending periodic updates from the server to all clients, which include the current state of the game. Clients can then use this information to update their local game state and ensure that all players see the same game state at all times.

In addition to synchronization, the networking model also includes error handling and recovery mechanisms, to ensure that the game remains stable and consistent even in the presence of network errors or other issues. This can include techniques such as packet loss detection and recovery, as well as connection timeouts and other error handling strategies.

Overall, the networking model for a game in C++ and using Boost.Asio provides a robust and efficient way to build multiplayer games with low latency and high throughput. With the right design and implementation, developers can create engaging and immersive gaming experiences that are enjoyed by players around the world.

- Handling network connections and data transmission

The above code represents a class named Serializator that provides methods for converting data types to bytes and creating packages for a specific protocol header.

The Serializator class contains several methods for converting data types such as integers and floats to bytes, using functions like intToByte() and enumToByte(). It also includes several methods for creating packages with different combinations of header types and parameters, using functions like createPackage(). These packages can then be sent over a network to other clients or servers, depending on the specific networking protocol being used.

Finally, the Serializator class also includes a method named bytesToStruct() which can be used to deserialize the bytes received from a network into a structured format. This is a key component of any serialization system, as it enables data to be transmitted over a network in a compact, efficient format, while still allowing it to be reconstructed on the other end.

Overall, the Serializator class is an important building block for any networked application, as it provides a way to serialize and deserialize data for transmission over a network, enabling fast and efficient communication between clients and servers.

## **4 - Conclusion**

In conclusion, the R type game server is a robust and scalable solution for building a multiplayer game server using C++ and Boost.Asio library. This developer documentation has covered all the important aspects of the server, including networking, game logic, security, and scaling. By following the guidelines provided in this documentation, developers can customize and extend the server to suit their specific requirements.

Looking ahead, there are several future plans and improvements that can be made to the R type game server. These include enhancing the networking performance, adding new game features, and improving the server monitoring and logging capabilities. With continuous development and improvement, the R type game server will remain a popular choice for building multiplayer games in the years to come.

————— _Alban de Tourtier - Alexandre Schaffner - Antoine Beaudoux - Mickael Riess —————_

————— _Renan Dubois - Yann-Arthur Tcheumani —————_
