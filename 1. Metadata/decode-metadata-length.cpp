#include <cstdint>
#include <iostream>

uint32_t reverseFourBytes(uint32_t num) {
    num = ((num << 8) & ((uint32_t) 0xFF00FF00)) | ((num >> 8) & ((uint32_t) 0xFF00FF));
    return (num << 0x10) | (num >> 0x10);
}

uint64_t reverseEightBytes(uint64_t num) {
    return (((uint64_t) reverseFourBytes((uint32_t) num)) << 0x20) | ((uint64_t) reverseFourBytes((uint32_t) (num >> 0x20)));
}

uint64_t decryptWithKey(uint64_t num1, uint64_t num2) {
    num2 &= ((uint64_t) 0x1FFFFFFFFF);
    uint64_t num3 = (num1 ^ num2) * ((uint64_t) 0x308DBC3) % ((uint64_t) 0x2000000000);
    uint64_t num4 = (num3 ^ (num3 >> 7)) & ((uint64_t) 0x550055);
    return (num3 ^ num4 ^ (num4 << 7)) - 1;
}

int main() {
    uint64_t num2 = reverseEightBytes(0x090E1CAD63FE6900);
    uint64_t num3 = decryptWithKey(0x0000001F2444E7A5, num2);
    std::cout << num3 << std::endl;

    return 0;
}
