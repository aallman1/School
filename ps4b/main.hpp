// Copyright [2022] <Andrew Allman>




#ifndef MAIN_HPP_
#define MAIN_HPP_

#include<math.h>
#include<iostream>
#include<sstream>
#include<memory>

#include "./Sokoban.hpp"
#include "./Matrix.hpp"
#include "SFML/Audio.hpp"

using std::cin;
using std::cout;

const size_t WOW_WIDTH = 160,
WOW_HEIGHT = 50,
DELAY = 18,
CONFETTI_COUNT = 1615;

enum RETURN_STATUS { RESET, WIN };

RETURN_STATUS runGame(sf::RenderWindow& window,
Sokoban* sGame,
sf::Clock& clock,
sf::Font& font,
sf::Text& text);

RETURN_STATUS winSequence(sf::RenderWindow& window,
Sokoban* sGame);

#endif  // MAIN_HPP_
