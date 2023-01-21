// Copyright [2022] <Andrew Allman>




#include "StringSound.hpp"
#include<exception>
#include<vector>

using std::vector;
using std::unique_ptr;


StringSound::StringSound(double frequency) : _tick_count(0) {
    if (ceil(SAMPLING_RATE/frequency) <= 0) {
        throw std::invalid_argument("Invalid Frequency");
    }

    _buffer = unique_ptr<CircularBuffer<sf::Int16>>(
        new CircularBuffer<sf::Int16>(SAMPLING_RATE/frequency));
}

StringSound::StringSound(vector<sf::Int16> init): _tick_count(0) {
    if (init.size() == 0) {
        throw std::invalid_argument("Invalid Vector Size");
    }
    _buffer = unique_ptr<CircularBuffer<sf::Int16>>(
        new CircularBuffer<sf::Int16>(init.size()));

    for (size_t i = 0; i < _buffer->capacity(); i++) {
        _buffer->enqueue(init[i]);
    }
}

void StringSound::pluck() {
    std::random_device rand_dev;
    std::default_random_engine rand_engine(rand_dev());
    std::uniform_int_distribution<int16_t> rand_dist(-32768, 32767);

    if (!_buffer->isEmpty()) {
        _buffer->empty();
    }

    while (!_buffer->isFull()) {
        _buffer->enqueue(rand_dist(rand_engine));
    }
}

void StringSound::tick() {
    sf::Int16 front(_buffer->dequeue());
    _buffer->enqueue(DECAY_RATE * 0.5 * (front + _buffer->peek()));
    _tick_count++;
}

sf::Int16 StringSound::sample() const {
    return _buffer->peek();
}

size_t StringSound::time() const {
    return _tick_count;
}
