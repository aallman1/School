// Copyright [2022] <Andrew Allman>




#include<vector>
#include<random>

#include"./SynthSound.hpp"

using std::vector;
using std::unique_ptr;

const double X_MAX = 2 * M_PI / SAMPLING_RATE;

SynthSound::SynthSound(double frequency, double mod_frequency, double gain,
 double decay, double mod_gain, double osc2_pitch, double osc2_gain) :
    _buffersize(SAMPLING_RATE/frequency),
    _buffer(unique_ptr<CircularBuffer<sf::Int16>>(
        new CircularBuffer<sf::Int16>(_buffersize))),
    _carrier_frequency(frequency * 2 * M_PI),
    _mod_frequency(mod_frequency * 2 * M_PI),
    _mod_active(_mod_frequency != 0),
    _gain(gain),
    _mod_gain(mod_gain),
    _decay(decay),
    _osc2_active(sf::Int16(osc2_pitch * _buffersize) != 0),
    _osc2_gain(osc2_gain),
    _osc2_deq(0) {
    if (_osc2_active) {
         _osc2buffer = unique_ptr<CircularBuffer<sf::Int16>>(
            new CircularBuffer<sf::Int16>(_buffersize * (2.0/osc2_pitch)));
    }
}


void SynthSound::set() {
    double x_carrier = 0,
    x_mod = 0,
    step_mod = 0,
    mod_max = 0,
    mod_min = 0,
    I = 0;

    double step_carrier =  X_MAX / ((SAMPLING_RATE/_carrier_frequency));

    if (_buffer->isFull()) {
        _buffer->empty();
    }

    if (_mod_active) {
        step_mod = X_MAX / (SAMPLING_RATE/(_mod_frequency / 2 * M_PI));
        for (int i = 0; i < _buffersize; i++) {
            double e = _mod_gain * sin(_mod_frequency * x_mod);
            mod_max = e > mod_max ? e : mod_max;
            mod_min = e < mod_min ? e : mod_min;
            x_mod += step_mod;
        }
        I = (mod_max - mod_min) / _mod_frequency;
        x_mod = 0;
    }


    while (!_buffer->isFull()) {
        _buffer->enqueue(ceil(
            _gain * sin(_carrier_frequency * x_carrier +
                (I * ((sin(_mod_frequency * x_mod)))))));

        x_carrier += step_carrier;
        x_mod += step_mod;
    }

    x_mod = x_carrier = 0;

    if (_osc2_active) {
        if (_osc2buffer->isFull()) {
            _osc2buffer->empty();
        }

        while (!_osc2buffer->isFull()) {
            _osc2buffer->enqueue(ceil(
                _osc2_gain * sin(_carrier_frequency * x_carrier +
                (I * ((sin(_mod_frequency * x_mod)))))));

            x_carrier += step_carrier;
            x_mod += step_mod;
        }
    }
}

void SynthSound::tick() {
    sf::Int16 front(_buffer->dequeue());
    _buffer->enqueue((
        DECAY_RATE * _decay * (front + _buffer->peek())));

    sf::Int16 osc2_front(_osc2buffer->dequeue());
    _osc2buffer->enqueue(
        DECAY_RATE * _decay * (osc2_front + _osc2buffer->peek()));
}

sf::Int16 SynthSound::sample() {
    if (!_buffer->isEmpty()) {
        if (_osc2_active && !_osc2buffer->isEmpty()) {
            switch (_osc2_deq) {
                case 0:
                    _osc2_deq += 1;
                    return (_buffer->peek());
                case 1:
                    _osc2_deq += 1;
                    return (_buffer->peek());
                case 2:
                    _osc2_deq += 1;
                    return (_osc2buffer->peek());
                case 3:
                    _osc2_deq = 0;
                    return (_osc2buffer->peek());
           }
        } else { return (_buffer->peek()); }
    }
    return 0;
}
