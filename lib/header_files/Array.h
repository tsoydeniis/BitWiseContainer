#pragma once
#include  "../header_files/global.h"
#include  "../header_files/Buffer.h"
#include  "../header_files/Storage.h"


class Array {
public:
    Array(size_t dim_cnt, size_t type_bit_size, size_t* dim_list);
    ~Array();
    Array(const Array& copy);
    Array& operator=(const Array& copy);

    Array& operator[](size_t arg);
    void operator=(uint32_t value);
    operator uint32_t();
    operator int();

    friend std::ostream& operator<<(std::ostream& stream, Array& value);

    static Array MakeList(size_t x, size_t y, size_t z);
    void Mult(uint32_t arg);
private:
    size_t dim_cnt_;
    size_t type_bit_size_;
    size_t* dim_sizes_cache_;
    size_t* dim_list_;
    Buffer buffer_;
    Storage storage_;
};



