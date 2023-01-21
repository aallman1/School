// Copyright [2022] <Andrew Allman>

#ifndef STRINGSOUND_HPP_
#define STRINGSOUND_HPP_

#include<math.h>
#include<random>
#include<memory>
#include<exception>
#include<vector>

#include"./CircularBuffer.hpp"
#include"./Definitions.hpp"

using std::vector;
using std::unique_ptr;


class StringSound {
 public:
    explicit StringSound(double frequency);
    explicit StringSound(vector<sf::Int16> init);
    StringSound(const StringSound& obj) = delete;
    void pluck();
    void tick();
    sf::Int16 sample() const;
    size_t time() const;
 private:
    unique_ptr<CircularBuffer<sf::Int16>> _buffer;
    size_t _tick_count;
};

#endif  // STRINGSOUND_HPP_
