#pragma once
#include  "../header_files/global.h"
#include  "../header_files/Buffer.h"


class Storage {
public:
    Storage(size_t target_cell_size, size_t size);
    Storage() = default;
    ~Storage();
    Storage(const Storage& copy);
    Storage& operator=(const Storage& copy);

    Storage& operator[](size_t number);
    void operator=(uint32_t value);
    operator uint32_t();
    operator int();
    void Mult(uint32_t arg);
private:
    size_t GetFirstIndex(size_t number) const ;
    size_t GetFirstBit(size_t number) const ;

    uint32_t GetMask(uint32_t first_bit, uint32_t last_bit) const ;
    void Write(size_t index, size_t first_bit, size_t last_bit, uint32_t& value);
    uint32_t Read(size_t index, size_t first_bit, size_t last_bit) const ;

    uint32_t GetValue(size_t number) const ;
    void SetValue(size_t number, uint32_t value);

    const size_t kCellSize_ = 8;
    const uint32_t Mask8 = GetMask(0, 8);

    size_t target_cell_size_ = 0;

    Buffer buffer_;
    size_t size_ = 0;
    uint8_t* data_ = nullptr;
    size_t data_size_ = 0;
};


