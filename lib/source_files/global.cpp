#include "../header_files/global.h"

std::size_t* Copy(std::size_t* arg, std::size_t size) {
    std::size_t* out = new std::size_t[size];
    for (int i = 0; i < size; ++i) {
        out[i] = arg[i];
    }

    return out;
}
uint8_t* Copy(uint8_t* arg, std::size_t size) {
    uint8_t* out = new uint8_t[size];
    for (int i = 0; i < size; ++i) {
        out[i] = arg[i];
    }

    return out;
}