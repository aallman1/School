// Copyright [2022] Andrew Allman




#ifndef CIRCULARBUFFER_HPP_
#define CIRCULARBUFFER_HPP_

#include<stdlib.h>
#include <memory>
#include<stdexcept>

template<class T>

class CircularBuffer {
 public:
    explicit CircularBuffer(size_t capacity);
    size_t size(size_t(*evalSize)(size_t, size_t, size_t, bool)) const;
    bool isEmpty() const;  // Is the buffer is empty?
    bool isFull() const;  // Is the buffer full?
    void enqueue(T item);  // Add item to the end
    T dequeue();  // Delete and return item from the front
    T peek() const;  // Return (but do not delete) item from the front
 private:
    size_t _capacity;
    size_t _head;
    size_t _tail;
    std::unique_ptr<T[]> _data;
    bool _full;
};

// Lambda function for returning size
auto evalSize = [](size_t head, size_t tail, size_t capacity, bool is_full)
{return is_full ? capacity : (head - tail) % capacity;};

/* Initialize class with smart pointer to handle memory leaks,
   initialize data to capacity size, and head/tail to zero, 
   with full flag to false.*/ 

template<class T>
CircularBuffer<T>::CircularBuffer(size_t capacity) :
_capacity(capacity), _head(0), _tail(0),
_data(std::unique_ptr<T[]>(new T[capacity])), _full(false) {
    if (capacity < 1) {
        throw std::invalid_argument("Capacity Cannot be Less than 1.");
    }
}


/* Utilizes lambda function for calculating size.
   I didn't see a good reason to use a lambda for this assignment,
   as I'm not entirely sure what the utilization of the circular buffer 
   will entail in the next assignment */

template<class T>
size_t CircularBuffer<T>::size(size_t(*evalSize)(size_t, size_t, size_t, bool))
const {
    return evalSize(_head, _tail, _capacity, isFull());
}

/* If head == tail, buffer is either full or empty, 
   so maintain 'is_full' status with flag*/
template<class T>
bool CircularBuffer<T>::isEmpty() const {return _head == _tail && !_full;}

// Returns the full flag value
template<class T>
bool CircularBuffer<T>::isFull() const {return _full;}

/* If is full, throws a runtime error, otherwise the tail is set to the new value, 
   and the tail advances to the next, presumably empty space. If tail advances to 
   the head's position, the buffer is full, and the full flag is set */

template<class T>
void CircularBuffer<T>::enqueue(T item) {
    if (isFull()) {
        throw std::runtime_error("Buffer Full");
    }

    _data[_tail] = item;
    _tail = (_tail + 1) % _capacity;
    _full = _tail == _head;
}

/* If is empty, throws a runtime error, otherwise a temp item is assigned the value of head, 
   and the head advances to the next item. Since an item was removed, the full flag is set 
   to false. If the next item is the tail, the queue is empty, and since the full flag
   was explicitly set to false, we can reliably assess if the buffer is empty with the isEmpty function */
template<class T>
T CircularBuffer<T>::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Queue Empty");
    }

    T retItem = _data[_head];
    _head = (_head + 1) % _capacity;
    _full = false;

    return retItem;
}

/*If is empty, throws a runtime error, otherwise 
returns a copy of the head of the buffer, without altering items.*/
template<class T>
T CircularBuffer<T>::peek() const {
    if (isEmpty()) {
        throw std::runtime_error("Queue Empty");
    }
    return _data[_head];
}

#endif  // CIRCULARBUFFER_HPP_
