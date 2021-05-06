#pragma once
#include <vector>


class CircleBuffer
{
public:
    CircleBuffer();
    ~CircleBuffer();
    void ensureCapacity();
    void pushBack(uint8_t *in, size_t );
    void popFront(uint8_t *out,size_t mSize);
private:
//    T *data = nullptr;
    void reorderData(size_t new_capacity);
    std::vector<uint8_t> data;
    size_t size = 100;

    size_t start_pos = 0;
    size_t end_pos = 0;
    size_t capacity = 100;
};

