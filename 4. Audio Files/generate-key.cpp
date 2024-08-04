#include <cstdint>
#include <cstring>
#include <iostream>

uint64_t magicNumbers(uint64_t value) {
    return value * ((uint64_t) 0x19660D) + ((uint64_t) 0x3C6EF35F);
}

uint64_t magicBitshiftXOR(int32_t value) {
    uint64_t num = ((uint64_t) 0xFFFFFFFFFFFFFFFF) / (uint64_t) (((uint64_t) value) << 0x13);
    uint64_t num2 = num & ((uint64_t) 0xFF00FF00FF00FF00);
    uint64_t num3 = num & ((uint64_t) 0xFF00FF00FF00FF);
    num2 >>= 1;
    num3 <<= 1;
    return magicNumbers(num2 ^ num3);
}

void magicTwinUlongOperation(uint64_t &val1, uint64_t &val2) {
    for (int i = 0; i <= (int) ((val1 ^ val2) & ((uint64_t) 0x3F)); i++) {
        uint64_t num = val1 & (((uint64_t) 0xF) << i);
        uint64_t num2 = val2 & (((uint64_t) 0xF) << i);
        val1 ^= ((uint64_t) 0xF) << i;
        val2 ^= ((uint64_t) 0xF) << i;
        val1 |= num2;
        val2 |= num;
    }
}

template <typename T>
void typedArrayWrite(uint8_t *buffer, T value, int &ptr) {
    memcpy(buffer + ptr, &value, sizeof(T));
    ptr += sizeof(T);
}

void twinUlongToArray(uint64_t val1, uint64_t val2, uint8_t *buffer) {
    int num = 0;
    typedArrayWrite<uint64_t>(buffer, val1, num);
    typedArrayWrite<uint64_t>(buffer, val2, num);
}

int main() {
    uint8_t buffer[0x10];

    uint64_t num = magicBitshiftXOR(5);
    uint64_t num2 = magicBitshiftXOR(0xB);
    magicTwinUlongOperation(num, num2);
    twinUlongToArray(num, num2, buffer);

    std::cout << std::hex << std::uppercase;
    for (int i = 0; i < sizeof(buffer) / sizeof(uint8_t); i++) {
        std::cout << +buffer[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
