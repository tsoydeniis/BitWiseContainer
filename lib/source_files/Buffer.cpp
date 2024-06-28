#include "../header_files/Buffer.h"

Buffer::Buffer(std::size_t size) {
    size_ = size;
    data_ = new std::size_t[size_];
}

Buffer::~Buffer() {
    delete(data_);
}

Buffer::Buffer(const Buffer& copy) {
    is_active_ = copy.is_active_;
    cur_index_ = copy.cur_index_;
    size_ = copy.size_;
    delete(data_);
    data_ = Copy(copy.data_, size_);
}

Buffer& Buffer::operator=(const Buffer& copy) {
    is_active_ = copy.is_active_;
    cur_index_ = copy.cur_index_;
    size_ = copy.size_;
    delete(data_);
    data_ = Copy(copy.data_, size_);

    return *this;
}

void Buffer::Add(std::size_t value) {
    if (cur_index_ == size_) {
        throw BufferError();
    }

    is_active_ = true;
    data_[cur_index_++] = value;
}

void Buffer::Deactivate() {
    is_active_ = false;
    cur_index_ = 0;
}

bool Buffer::Ready() const {
    return (cur_index_ == size_);
}

