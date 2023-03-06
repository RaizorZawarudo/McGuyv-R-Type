#include <iostream>

void convertToBytes(unsigned long long number, unsigned char* byte_array)
{
    for(int i = 0; i < sizeof(unsigned long long); i++)
    {
        byte_array[i] = (number >> (i*8)) & 0xFF;
    }
}

int main()
{
    unsigned long long num = 4512582;
    unsigned char byte_array[sizeof(unsigned long long)];
    convertToBytes(num, byte_array);
    
    // Afficher le tableau d'octets
    for(int i = 0; i < sizeof(unsigned long long); i++)
    {
        std::cout << std::hex << (int)byte_array[i] << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
