#pragma once
#include  "../header_files/global.h"


class Buffer {
public:
    std::size_t size_ = 0;
    std::size_t* data_ = nullptr;
    std::size_t cur_index_ = 0;

    explicit Buffer(std::size_t size = 1);
    ~Buffer();
    Buffer(const Buffer& copy);
    Buffer& operator=(const Buffer& copy);

    void Add(std::size_t value);
    void Deactivate();
    bool Ready() const ;
private:
    bool is_active_ = false;
};


