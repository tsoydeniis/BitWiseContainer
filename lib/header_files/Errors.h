#include <iostream>

class BufferError : public std::runtime_error {
public:
    explicit BufferError()
            : std::runtime_error("BufferError") {}
};

class ReadError : public std::runtime_error {
public:
    explicit ReadError()
            : std::runtime_error("ReadError") {}
};

class WriteError : public std::runtime_error {
public:
    explicit WriteError()
            : std::runtime_error("WriteError") {}
};

class WrongIndex : public std::runtime_error {
public:
    explicit WrongIndex()
            : std::runtime_error("WrongIndex") {}
};
