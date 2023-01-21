// Copyright [2022] <Andrew Allman>

#ifndef SOKOBAN_HPP_
#define SOKOBAN_HPP_

#include<iostream>
#include<vector>
#include<memory>
#include<string>
#include<exception>
#include<utility>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

#include"./Matrix.hpp"


using std::istream;
using std::vector;
using std::string;
using std::unique_ptr;
using std::ostream;

#define SPRITE_SIZE 64
#define NUM_SPRITES 8

enum DIRECTION {NORTH = 4, SOUTH, EAST, WEST};
enum TEXTURES { GROUND, STORAGE, CRATE, WALL, CHAR_N, CHAR_S, CHAR_E, CHAR_W };
const vector<string> TEXTURE_FP = {
    "sokoban/ground_01.png",
    "sokoban/ground_04.png",
    "sokoban/crate_03.png",
    "sokoban/block_06.png",
    "sokoban/player_08.png",
    "sokoban/player_05.png",
    "sokoban/player_17.png",
    "sokoban/player_20.png"
};


class Sokoban : public sf::Drawable, public sf::Transformable{
 public:
    Sokoban();
    void movePlayer();
    friend ostream& operator<<(ostream&, const Sokoban&);
    friend void operator>>(istream&, Sokoban&);
    std::pair<size_t, size_t>gridSize();
    ~Sokoban();

 private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        for (size_t i = 0; i < _sprites.size(); i++) {
            if (i < CHAR_N) {
                for (sf::Sprite* sprite : _sprites[i]) {
                    target.draw(*sprite, states);
                }
            } else if (i == _play_direction) {
                target.draw(*_sprites[i][0], states);
                break;
            }
        }
    }
    vector<sf::Texture> _textures;
    vector<vector<sf::Sprite*>> _sprites;
    std::pair<size_t, size_t> _play_position;
    DIRECTION _play_direction;
    Matrix _gamestate;
};


#endif  // SOKOBAN_HPP_
