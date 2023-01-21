// Copyright [2022] <Andrew Allman>


#ifndef SYNTHSOUND_HPP_
#define SYNTHSOUND_HPP_

#include<vector>
#include<memory>

#include"./CircularBuffer.hpp"
#include"./Definitions.hpp"


using std::vector;
using std::unique_ptr;


class SynthSound {
 public:
    explicit SynthSound(
    double frequency,
    double mod_frequency,
    double gain,
    double decay,
    double mod_gain,
    double osc2_pitch,
    double osc2_gain);
    explicit SynthSound(vector<sf::Int16> init);
    SynthSound(const SynthSound& obj) = delete;
    sf::Int16 sample();
    void set();
    void tick();

 private:
    sf::Int16 _buffersize;
    unique_ptr<CircularBuffer<sf::Int16>> _buffer;
    double _carrier_frequency;
    double _mod_frequency;
    bool _mod_active;
    double _gain;
    double _mod_gain;
    double _decay;
    bool _osc2_active;
    double _osc2_pitch;
    double _osc2_gain;
    int _osc2_deq;
    unique_ptr<CircularBuffer<sf::Int16>> _osc2buffer;
};

#endif  // SYNTHSOUND_HPP_
