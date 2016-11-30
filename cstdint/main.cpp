#include <cstdint>
#include <iostream>

#define PRINT(T) \
    std::cout << "size of "#T": " << sizeof(T) << std::endl;


int main(int argc, char *argv[])
{
    PRINT(std::int8_t);
    PRINT(std::int16_t);
    PRINT(std::int32_t);
    PRINT(std::int64_t);
    std::cout << std::endl;
    PRINT(std::intmax_t);
    PRINT(std::intptr_t);
    PRINT(std::int_fast8_t);
}
