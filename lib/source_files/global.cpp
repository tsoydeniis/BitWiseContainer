#include "../header_files/global.h"

size_t* Copy(size_t* arg, size_t size) {
    size_t* out = new size_t[size];
    for (int i = 0; i < size; ++i) {
        out[i] = arg[i];
    }

    return out;
}
uint8_t* Copy(uint8_t* arg, size_t size) {
    uint8_t* out = new uint8_t[size];
    for (int i = 0; i < size; ++i) {
        out[i] = arg[i];
    }

    return out;
}