#pragma once
#include  "../header_files/global.h"
#include  "../header_files/Buffer.h"


class Storage {
public:
    Storage(std::size_t target_cell_size, std::size_t size);
    Storage() = default;
    ~Storage();
    Storage(const Storage& copy);
    Storage& operator=(const Storage& copy);

    Storage& operator[](std::size_t number);
    void operator=(uint32_t value);
    operator uint32_t();
    operator int();
    void Mult(uint32_t arg);
private:
    std::size_t GetFirstIndex(std::size_t number) const ;
    std::size_t GetFirstBit(std::size_t number) const ;

    uint32_t GetMask(uint32_t first_bit, uint32_t last_bit) const ;
    void Write(std::size_t index, std::size_t first_bit, std::size_t last_bit, uint32_t& value);
    uint32_t Read(std::size_t index, std::size_t first_bit, std::size_t last_bit) const ;

    uint32_t GetValue(std::size_t number) const ;
    void SetValue(std::size_t number, uint32_t value);

    const std::size_t kCellSize_ = 8;
    const uint32_t Mask8 = GetMask(0, 8);

    std::size_t target_cell_size_ = 0;

    Buffer buffer_;
    std::size_t size_ = 0;
    uint8_t* data_ = nullptr;
    std::size_t data_size_ = 0;
};


