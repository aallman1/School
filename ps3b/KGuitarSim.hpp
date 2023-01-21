// Copyright [2022] <Andrew Allman>




#ifndef KGUITARSIM_HPP_
#define KGUITARSIM_HPP_

#include<string>
#include<vector>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

#include"./StringSound.hpp"
#include"./SynthSound.hpp"



using std::string;
using std::vector;

const char keys[]  = "q2we4r5ty7u8i9op-[=zxdcfvgbnjmk,.;/' ";
const double MAX_DURATION = 6;
const int NOTE_COUNT = 37;

void drawScreen(sf::RenderWindow& window, vector<sf::Drawable*>& components);

vector<sf::Int16> makeSamples(StringSound& gs);
vector<sf::Int16> makeSamples(SynthSound& ss);

char getKey(uint32_t uc);

const int M_PITCH = 0,
OSC_I_GAIN = 1,
MOD_FREQ = 2,
MOD_GAIN = 3,
OSC_II_GAIN = 4,
OSC_II_PITCH = 5,
DECAY = 6;

#endif  // KGUITARSIM_HPP_
