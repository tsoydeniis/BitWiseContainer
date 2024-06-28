#include "../header_files/Array.h"


Array::Array(std::size_t dim_cnt, std::size_t type_bit_size, std::size_t* dim_list) {
    dim_cnt_ = dim_cnt;
    type_bit_size_ = type_bit_size;
    std::size_t size_ = 1;
    dim_list_ = new std::size_t[dim_cnt_];
    for (int i = 0; i < dim_cnt_; ++i) {
        size_ *= dim_list[i];
        dim_list_[i] = dim_list[i];
    }
    buffer_ = Buffer(dim_cnt_);
    storage_ = Storage(type_bit_size_, size_);
    dim_sizes_cache_ = new std::size_t[dim_cnt_];
    dim_sizes_cache_[dim_cnt_ - 1] = 1;
    for (int i = dim_cnt_ - 2; i >= 0; --i) {
        dim_sizes_cache_[i] = dim_sizes_cache_[i + 1] * dim_list_[i + 1];
    }
}

Array::~Array() {
    delete(dim_sizes_cache_);
    delete(dim_list_);
}

Array::Array(const Array& copy) {
    dim_cnt_ = copy.dim_cnt_;
    type_bit_size_ = copy.type_bit_size_;
    dim_sizes_cache_ = Copy(copy.dim_sizes_cache_, dim_cnt_);
    dim_list_ = Copy(copy.dim_list_, dim_cnt_);
    buffer_ = copy.buffer_;
    storage_ = copy.storage_;
}

Array& Array::operator=(const Array& copy) {
    dim_cnt_ = copy.dim_cnt_;
    type_bit_size_ = copy.type_bit_size_;
    dim_sizes_cache_ = Copy(copy.dim_sizes_cache_, dim_cnt_);
    dim_list_ = Copy(copy.dim_list_, dim_cnt_);
    buffer_ = copy.buffer_;
    storage_ = copy.storage_;

    return *this;
}

Array& Array::operator[](std::size_t arg) {
    buffer_.Add(arg);
    if (arg >= dim_list_[buffer_.cur_index_ - 1]) {
        throw WrongIndex();
    }

    return *this;
}

void Array::operator=(uint32_t value) {
    if (!buffer_.Ready()) {
        throw BufferError();
    }
    std::size_t number = 0;
    for (int i = 0; i < buffer_.size_; ++i) {
        number += dim_sizes_cache_[i] * buffer_.data_[i];
    }
    buffer_.Deactivate();
    storage_[number] = value;
}

Array::operator uint32_t() {
    if (!buffer_.Ready()) {
        throw BufferError();
    }
    std::size_t number = 0;
    for (int i = 0; i < buffer_.size_; ++i) {
        number += dim_sizes_cache_[i] * buffer_.data_[i];
    }
    buffer_.Deactivate();

    return storage_[number];
}

Array::operator int() {
    return static_cast<int>(uint32_t(*this));
}

Array Array::MakeList(std::size_t x, std::size_t y, std::size_t z) {
    std::size_t list[3] = {x, y, z};
    return Array(3, 17, list);
}

void Array::Mult(uint32_t arg) {
    storage_.Mult(arg);
}

std::ostream& operator<<(std::ostream& stream, Array& arg) {
    std::size_t cnt = 1;
    for (std::size_t i = 0; i < arg.dim_cnt_; ++i) {
        cnt *= arg.dim_list_[i];
    }
    for (std::size_t i = 0; i < cnt; ++i) {
        stream << uint32_t(arg.storage_[i]);
    }

    return stream;
}

