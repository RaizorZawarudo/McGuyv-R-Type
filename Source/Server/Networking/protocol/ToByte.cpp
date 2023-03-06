//
// Created by speedy on 2/8/23.
//
#include "Serializator.hpp"


#include <iostream>
#include <cstddef>
#include <algorithm>

char Serializator::enumToByte(serializator::Header header)
{
    return (char)header;
}

char Serializator::enumToByte(serializator::Movement header)
{
    return (char)header;
}

char *Serializator::intToByte(unsigned long long number)
{
    char* arrayOfByte = new char[sizeof(number)];

    memcpy(arrayOfByte, &number, sizeof(unsigned long long));
    return arrayOfByte;
}

char *Serializator::intToByte(int number)
{
    char* arrayOfByte = new char[sizeof(number)];

    memcpy(arrayOfByte, &number, sizeof(int));
    return arrayOfByte;
}

char *Serializator::intToByte(float number)
{
    char* arrayOfByte = new char[sizeof(number)];
    memcpy(arrayOfByte, &number, sizeof(float));
    return arrayOfByte;
}