#include "../header_files/Storage.h"

Storage::Storage(size_t target_cell_size, size_t size) {
    target_cell_size_ = target_cell_size;
    buffer_ = Buffer(1);
    size_ = size;
    data_size_ = target_cell_size * size_ / kCellSize_ + 1;
    data_ = new uint8_t[data_size_]{0};
}

Storage::~Storage() {
    delete(data_);
}

Storage::Storage(const Storage& copy) {
    target_cell_size_ = copy.target_cell_size_;
    buffer_ = copy.buffer_;
    size_ = copy.size_;
    delete(data_);
    data_ = Copy(copy.data_, copy.data_size_);
    data_size_ = copy.data_size_;
}

Storage& Storage::operator=(const Storage& copy) {
    target_cell_size_ = copy.target_cell_size_;
    buffer_ = copy.buffer_;
    size_ = copy.size_;
    delete(data_);
    data_ = Copy(copy.data_, copy.data_size_);
    data_size_ = copy.data_size_;

    return *this;
}

size_t Storage::GetFirstIndex(size_t number) const {
    return number * target_cell_size_ / kCellSize_;
}

size_t Storage::GetFirstBit(size_t number) const {
    return number * target_cell_size_ % kCellSize_;
}

uint32_t Storage::GetMask(uint32_t first_bit, uint32_t last_bit) const {
    return (((1 << (last_bit + 1)) - 1) - ((1 << first_bit) - 1));
}

void Storage::Write(size_t index, size_t first_bit, size_t last_bit, uint32_t& value) {
    if (first_bit > last_bit || last_bit > kCellSize_) {
        throw WriteError();
    }
    size_t Mask = GetMask(first_bit, last_bit);
    data_[index] &= Mask8 - Mask;
    data_[index] += ((value << first_bit) & Mask);
    value >>= last_bit - first_bit + 1;
}

uint32_t Storage::Read(size_t index, size_t first_bit, size_t last_bit) const {
    if (first_bit > last_bit || last_bit > kCellSize_) {
        throw ReadError();
    }
    size_t Mask = GetMask(first_bit, last_bit);
    uint32_t res = ((data_[index] & Mask) >> first_bit);

    return res;
}

uint32_t Storage::GetValue(size_t number) const {
    size_t cur_index = GetFirstIndex(number);
    size_t first_bit = GetFirstBit(number);
    size_t cur_last_bit;
    size_t cur_shift = 0;
    size_t remaining_bits = target_cell_size_;
    uint32_t res = 0;
    while (remaining_bits != 0) {
        cur_last_bit = std::min(kCellSize_ - 1, first_bit + remaining_bits - 1);
        remaining_bits -= cur_last_bit - first_bit + 1;
        res += ((Read(cur_index, first_bit, cur_last_bit)) << cur_shift);
        cur_shift += cur_last_bit - first_bit + 1;
        ++cur_index;
        first_bit = 0;
    }

    return res;
}

void Storage::SetValue(size_t number, uint32_t value) {
    size_t cur_index = GetFirstIndex(number);
    size_t first_bit = GetFirstBit(number);
    size_t cur_last_bit;
    size_t remaining_bits = target_cell_size_;
    while (remaining_bits != 0) {
        cur_last_bit = std::min(kCellSize_ - 1, first_bit + remaining_bits - 1);
        remaining_bits -= cur_last_bit - first_bit + 1;
        Write(cur_index, first_bit, cur_last_bit, value);
        ++cur_index;
        first_bit = 0;
    }
}

Storage& Storage::operator[](size_t number) {
    buffer_.Add(number);

    return *this;
}

void Storage::operator=(uint32_t value) {
    if (!buffer_.Ready()) {
        throw BufferError();
    }
    SetValue(buffer_.data_[0], value);
    buffer_.Deactivate();
}

Storage::operator uint32_t() {
    if (!buffer_.Ready()) {
        throw BufferError();
    }
    uint32_t out = GetValue(buffer_.data_[0]);
    buffer_.Deactivate();

    return out;
}

Storage::operator int() {
    return static_cast<int>(uint32_t(*this));
}

void Storage::Mult(uint32_t arg) {
    for (int i = 0; i < size_; ++i) {
        SetValue(i, GetValue(i) * arg);
    }
}