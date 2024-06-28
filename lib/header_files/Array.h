#pragma once
#include  "../header_files/global.h"
#include  "../header_files/Buffer.h"
#include  "../header_files/Storage.h"


class Array {
public:
    Array(std::size_t dim_cnt, std::size_t type_bit_size, std::size_t* dim_list);
    ~Array();
    Array(const Array& copy);
    Array& operator=(const Array& copy);

    Array& operator[](std::size_t arg);
    void operator=(uint32_t value);
    operator uint32_t();
    operator int();

    friend std::ostream& operator<<(std::ostream& stream, Array& value);

    static Array MakeList(std::size_t x, std::size_t y, std::size_t z);
    void Mult(uint32_t arg);
private:
    std::size_t dim_cnt_;
    std::size_t type_bit_size_;
    std::size_t* dim_sizes_cache_;
    std::size_t* dim_list_;
    Buffer buffer_;
    Storage storage_;
};



