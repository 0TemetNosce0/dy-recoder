#include "CircleBuffer.h"




CircleBuffer::CircleBuffer()
{
    data.resize(size);

}


CircleBuffer::~CircleBuffer()
{

}


void CircleBuffer::pushBack(uint8_t * in,size_t mSize)
{
    size_t new_end_pos = end_pos + mSize;

    size += mSize;
    ensureCapacity();

    if (new_end_pos > capacity) {
        size_t back_size = capacity - end_pos;
        size_t loop_size = mSize - back_size;

        if (back_size)
            memcpy(data.data() + end_pos, in,
                   back_size);
        memcpy(data.data(), in + back_size, loop_size);

        new_end_pos -= capacity;
    } else {
        memcpy((uint8_t *)data.data() + end_pos, in, size);
    }

    end_pos = new_end_pos;
}
#include <assert.h>
void CircleBuffer::popFront(uint8_t *out, size_t mSize)
{
    assert(size <= mSize);

    if (out) {
        size_t start_size = capacity - start_pos;

        if (start_size < size) {
            memcpy(out, data.data() + start_pos,
                   start_size);
            memcpy(out + start_size, data.data(),
                   size - start_size);
        } else {
            memcpy(out, data.data() + start_pos, size);
        }
    }

    size -= mSize;
    if (!size) {
        start_pos = end_pos = 0;
        return;
    }

    start_pos += mSize;
    if (start_pos >= capacity)
        start_pos -= capacity;
}

void CircleBuffer::reorderData(size_t new_capacity)
{

}


void CircleBuffer::ensureCapacity()
{
    size_t new_capacity;
    if (size <= capacity)
        return;

    new_capacity = capacity * 2;
    if (size > new_capacity)
        new_capacity = size;
    data.resize(new_capacity);

    capacity = new_capacity;
}
