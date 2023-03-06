# **Protocol documentation**

## **Introduction**

This RFC documentation proposes the use of the UDP protocol for a multiplayer game coded in C++ using the Boost.Asio library. The proposed solution aims to provide low-latency communication between game clients and servers, which is critical for the smooth and responsive gameplay experience required in modern online multiplayer games. This document will outline the design, implementation, and testing of the proposed solution, as well as provide recommendations for best practices and future improvements.

## **1 - Serializator**

- **Getter**
- **Setter**
- **Bytes to structure**

## **2 - Create package**

- **Overview**
- **Create package**

## **3 - ToByte**

- **Overview**
- **ToByte function**

## **4 - User Datagram Protocol**

<br/>
<br/>

## **1 - Serializator**

- **Getter**

**Overview :**

This different function class called Msg, which appears to be a message container for a multiplayer game. The class has several public member functions that return different attributes of the message, such as its status, ID, owner ID, type, position, and other relevant information. The private members of the class include various indices and identifiers that may be used by the game engine to interpret the message and perform relevant actions. The class also has a member function called getmovement() that returns a serializator::Movement object, which is likely used to serialize and deserialize movement data for game objects. Overall, the Msg class seems to be a fundamental building block for sending and receiving messages in a multiplayer game.

**Mandatory getter :**

1 - getstatus() const: This function returns the status of the message as an integer value.

2 - getId() const: This function returns the ID of the message as an unsigned long long value.

3 - getOwnerId() const: This function returns the owner ID of the message as an integer value.

4 - getWeaponId() const: This function returns the weapon index of the message as an integer value.

5 - getClientHash() const: This function returns the client hash number of the message as an integer value.

6 - getX() const: This function returns the x-coordinate of the message as an integer value.

7 - getY() const: This function returns the y-coordinate of the message as an integer value.

8 - getZ() const: This function returns the z-coordinate of the message as an integer value.

10 - getDirection() const: This function returns the direction of the message as an integer value.

11 - getstate() const: This function returns the state of the message as an integer value.

12 - getaction() const: This function returns the action of the message as an integer value.

13 - getLootIndex() const: This function returns the loot index of the message as an integer value.

14 - getExplosionIndex() const: This function returns the explosion index of the message as an integer value.

15 - getEnemyIndex() const: This function returns the enemy index of the message as an integer value.

14 - getObstacleIndex() const: This function returns the obstacle index of the message as an integer value.

16 - getModelIndex() const: This function returns the model index of the message as an integer value.

17 - getAvatarIndex() const: This function returns the avatar index of the message as an integer value.

18 - gettype() const: This function returns the type of the message as a char value.

19 - getmovement() const: This function returns the movement data of the message as a serializator::Movement object.

- **Setter**

**Overview :**

This different function class called Msg has several public setter functions. These functions are used to set the values of the private data members of the class. The data members include variables such as the ID, owner ID, client hash number, type, X, Y, Z, action, state, and other indexes used for the game's logic. Additionally, there are setter functions for the different indexes and types used in the game, such as the loot index, explosion index, enemy index, obstacle index, model index, avatar index, and movement type. The class is designed to be used in a game using the UDP protocol, and the values set by the setter functions are used to serialize the data and send it over the network.

**Mandatory Setter:**

1 - setstatus(serializator::Header status) - sets the value of the \_status data member, which represents the message header status.

2 - setId(unsigned long long id) - sets the value of the \_id data member, which represents the message ID.

3 - setOwnerId(unsigned long long id) - sets the value of the \_ownerId data member, which represents the owner ID of the message.

4 - setWeaponId(unsigned long long weaponIndex) - sets the value of the \_weaponIndex data member, which represents the index of the weapon used in the message.

5 - setClientHash(unsigned long long clientHashNumber) - sets the value of the \_clientHashNumber data member, which represents the client hash number of the message.

6 - setX(int x) - sets the value of the \_x data member, which represents the X coordinate of the message.

7 - setY(int y) - sets the value of the \_y data member, which represents the Y coordinate of the message.

8 - setZ(int z) - sets the value of the \_z data member, which represents the Z coordinate of the message.

9 - setDirection(int direction) - sets the value of the \_direction data member, which represents the direction of the message.

10 - setstate(int state) - sets the value of the \_state data member, which represents the state of the message.

11 - setaction(int action) - sets the value of the \_action data member, which represents the action of the message.

12 - setLootIndex(int lootIndex) - sets the value of the \_lootIndex data member, which represents the index of the loot used in the message.

13 - setExplosionIndex(int lootIndex) - sets the value of the \_explosionIndex data member, which represents the index of the explosion used in the message.

14 - setEnemyIndex(int lootIndex) - sets the value of the \_enemyIndex data member, which represents the index of the enemy used in the message.

15 - setObstacleIndex(int lootIndex) - sets the value of the \_obstacleIndex data member, which represents the index of the obstacle used in the message.

16 - setModelIndex(int lootIndex) - sets the value of the \_modelIndex data member, which represents the index of the model used in the message.

17 - setAvatarIndex(int lootIndex) - sets the value of the \_avatarIndex data member, which represents the index of the avatar used in the message.

18 - settype(char type) - sets the value of the \_type data member, which represents the type of the message.

19 - setmovement(serializator::Movement type) - sets the value of the \_mvt data member, which represents the movement type of the message.

- **Bytes to structur**

This part defines a function bytesToStruct in the Serializator class that takes in a char array (a C-style string) and returns a Msg object.

The Msg object is a custom struct that represents different types of messages that can be sent or received over a network. It has different properties that are set based on the type of message being sent or received.

The bytesToStruct function works by using a std::map called factory that maps different types of serializator::Header values (enums) to functions that create and return Msg objects. Each function takes in the char array that was passed to bytesToStruct and uses it to set the properties of the Msg object based on the specific format of the message.

The format of each message is determined by the Header value, which is represented by the first byte of the char array. Depending on the Header value, the corresponding function from factory is called to create a Msg object with the correct properties.

For example, if the Header value is createEntity, the function defined for that header in factory is called. That function takes the char array and extracts different parts of the message to set the properties of the Msg object. These properties include status, id, and type.

Overall, this code is part of a larger system that serializes and deserializes messages for a networked game. The bytesToStruct function is responsible for converting a received message (in the form of a char array) into a structured Msg object that can be used by the game logic.

For exemple serializator::Header::UpdateEnemy is a constant value that represents a specific type of message header in a software system.

It is likely part of a larger software system that handles some kind of data serialization or communication between different components. The UpdateEnemy part of the constant name suggests that this header type is used for messages that update information related to an enemy object or entity within the system.

The header is likely used to identify and distinguish different types of messages or data packets that are sent between different parts of the system. This allows the system to route the data to the appropriate components and take the necessary actions based on the type of data received.

## **2 - Create package**

- **Overview**

This is a C++ source code defining several overloaded functions named createPackage within the Serializator class. Each function creates and returns a serialized package (i.e., a sequence of bytes) that encodes different kinds of information related to the game entities, events, and state.

The createPackage function takes a serializator::Header enum parameter that determines the type of message being sent, as well as other parameters that depend on the message type. The function creates a dynamic memory allocation for a character array of the appropriate size to hold the serialized data.

- **Create package**

. createPackageUpdEnnemies(serializator::Header, int model, int x, int y, int z, int pitch, int raw, int roll, unsigned long long serverEntityId): Creates a byte array for updating the enemies' position and orientation.

. createPackageRemoveEntity(serializator::Header, unsigned long long): Creates a byte array for removing an entity.

. createPackagePosEntity(serializator::Header, unsigned long long serverEntityId, int x, int y, int z): Creates a byte array for updating an entity's position.

. createPackageUpgLootExp(serializator::Header, int, int x, int y, int z, unsigned long long serverEntityId): Creates a byte array for updating the loot and experience entities.

. createPackageUpdProjectile(serializator::Header, int, int x, int y, int z, unsigned long long serverEntityId, int, unsigned long long OwnerId): Creates a byte array for updating the projectile entities.

. createPackageUpdPowerUp(serializator::Header status, int model, int x, int y, int z, unsigned long long entityId): Creates a byte array for updating the power-up entities.

. createPackageUpdObs(serializator::Header status, int model, int x, int y, int z, unsigned long long entityId): Creates a byte array for updating the obstacle entities.

. createPackageUpdExplosion(serializator::Header status, int model, int x, int y, int z, unsigned long long entityId): Creates a byte array for updating the explosion entities.

. createPackageStateGame(serializator::Header status, bool state): Creates a byte array for updating the game state.

. createPackageSelection(serializator::Header status, int action): Creates a byte array for selecting an action.

. createPackageSetClientId(serializator::Header status, int id): Creates a byte array for setting the client ID.

. createPackageStartGame(serializator::Header status, bool): Creates a byte array for starting the game.

. createPackageCanSelect(serializator::Header status, int, bool state): Creates a byte array for enabling or disabling the selection option.

. createPackageSetSpaceShip(serializator::Header status, int indexSpaceShip, int id): Creates a byte array for setting the client's spaceship.

## **3 - ToByte**

- **Overview**

The Serializator class provides methods for serializing various data types into byte arrays. This allows for the transmission of data over a network or the storage of data in a file.

The class contains three methods for converting enums to bytes, which can be useful for serializing protocol headers or other enumerated values.

There are also three overloaded intToByte methods, which convert integers of different sizes and types to byte arrays. These methods use the memcpy function to copy the binary representation of the integer into a char array, which can then be sent over a network or written to a file.

Overall, the Serializator class provides a convenient way to serialize different data types into a binary format, which can be useful for a variety of applications.

- **ToByte function**

1 - enumToByte(serializator::Header header) - This function takes a serializator::Header enum value and converts it to a single byte character representation. It does this by casting the enum value to a char.

2 - enumToByte(serializator::Movement header) - This function takes a serializator::Movement enum value and converts it to a single byte character representation. It does this by casting the enum value to a char.

3 - char \*intToByte(unsigned long long number) - This function takes an unsigned 64-bit integer and converts it into an array of bytes. It does this by creating a char array of the same size as the unsigned long long type, and then copying the memory of the unsigned long long value into the char array using the memcpy function.

4 - char \*intToByte(int number) - This function takes a signed 32-bit integer and converts it into an array of bytes. It does this by creating a char array of the same size as the int type, and then copying the memory of the int value into the char array using the memcpy function.

5 - char \*intToByte(float number) - This function takes a 32-bit floating point number and converts it into an array of bytes. It does this by creating a char array of the same size as the float type, and then copying the memory of the float value into the char array using the memcpy function.

All of these functions are used to convert data types into arrays of bytes, which can then be sent over a network or written to disk as binary data. The enumToByte functions are useful for encoding enum values into a compact form, while the intToByte functions can be used to encode integers and floating point numbers.

<br/>

# User Datagram Protocol
----------------------

Introduction
------------

This User Datagram Protocol (UDP) is defined to make available a
datagram mode of packet-switched computer communication in the
environment of an interconnected set of computer networks. This
protocol assumes that the Internet Protocol (IP) [1] is used as the
underlying protocol.

This protocol provides a procedure for application programs to send
messages to other programs with a minimum of protocol mechanism. The
protocol is transaction oriented, and delivery and duplicate protection
are not guaranteed. Applications requiring ordered reliable delivery of
streams of data should use the Transmission Control Protocol (TCP) [2].

Format
------

## 0 7 8 15 16 23 24 31

## +--------+--------+--------+--------+

| Source | Destination |
| Port | Port |
+--------+--------+--------+--------+
| | |
| Length | Checksum |
+--------+--------+--------+--------+
|
| data octets ...
+---------------- ...

User Datagram Header Format

Fields
------

Source Port is an optional field, when meaningful, it indicates the port
of the sending process, and may be assumed to be the port to which a
reply should be addressed in the absence of any other information. If
not used, a value of zero is inserted.

28 Aug 1980
User Datagram Protocol RFC 768
Fields

Destination Port has a meaning within the context of a particular
internet destination address.

Length is the length in octets of this user datagram including this
header and the data. (This means the minimum value of the length is
eight.)

Checksum is the 16-bit one’s complement of the one’s complement sum of a
pseudo header of information from the IP header, the UDP header, and the
data, padded with zero octets at the end (if necessary) to make a
multiple of two octets.

The pseudo header conceptually prefixed to the UDP header contains the
source address, the destination address, the protocol, and the UDP
length. This information gives protection against misrouted datagrams.
This checksum procedure is the same as is used in TCP.

0 7 8 15 16 23 24 31
+--------+--------+--------+--------+
| source address |
+--------+--------+--------+--------+
| destination address |
+--------+--------+--------+--------+
| zero |protocol| UDP length |
+--------+--------+--------+--------+

If the computed checksum is zero, it is transmitted as all ones (the
equivalent in one’s complement arithmetic). An all zero transmitted
checksum value means that the transmitter generated no checksum (for
debugging or for higher level protocols that don’t care).

User Interface
--------------

A user interface should allow

the creation of new receive ports,

receive operations on the receive ports that return the data octets
and an indication of source port and source address,

and an operation that allows a datagram to be sent, specifying the
data, source and destination ports and addresses to be sent.

28 Aug 1980
RFC 768 User Datagram Protocol
IP Interface

IP Interface
-------------

The UDP module must be able to determine the source and destination
internet addresses and the protocol field from the internet header. One
possible UDP/IP interface would return the whole internet datagram
including all of the internet header in response to a receive operation.
Such an interface would also allow the UDP to pass a full internet
datagram complete with header to the IP to send. The IP would verify
certain fields for consistency and compute the internet header checksum.

Protocol Application
--------------------

The major uses of this protocol is the Internet Name Server [3], and the
Trivial File Transfer [4].

Protocol Number
---------------

This is protocol 17 (21 octal) when used in the Internet Protocol.
Other protocol numbers are listed in [5].

References
----------

[1] Postel, J., "Internet Protocol," RFC 760, USC/Information
Sciences Institute, January 1980.

[2] Postel, J., "Transmission Control Protocol," RFC 761,
USC/Information Sciences Institute, January 1980.

[3] Postel, J., "Internet Name Server," USC/Information Sciences
Institute, IEN 116, August 1979.

[4] Sollins, K., "The TFTP Protocol," Massachusetts Institute of
Technology, IEN 133, January 1980.

[5] Postel, J., "Assigned Numbers," USC/Information Sciences
Institute, RFC 762, January 1980.


