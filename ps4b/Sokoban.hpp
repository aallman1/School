// Copyright [2022] <Andrew Allman>

#ifndef SOKOBAN_HPP_
#define SOKOBAN_HPP_

#include<iostream>
#include<vector>
#include<memory>
#include<unordered_map>
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
#define NUM_SPRITES 9

enum DIRECTION {NORTH = 4, SOUTH, EAST, WEST};
enum TEXTURES { GROUND, STORAGE, CRATE, WALL, CHAR_N,
CHAR_S, CHAR_E, CHAR_W, CRATE_SET };

const vector<string> TEXTURE_FP = {
    "sokoban/ground_01.png",
    "sokoban/ground_04.png",
    "sokoban/crate_03.png",
    "sokoban/block_06.png",
    "sokoban/player_08.png",
    "sokoban/player_05.png",
    "sokoban/player_17.png",
    "sokoban/player_20.png",
    "sokoban/crate_03_set.png"
};


class Sokoban : public sf::Drawable, public sf::Transformable{
 public:
    Sokoban();
    void movePlayer(const DIRECTION);
    void moveCrate(const DIRECTION, const bool, int8_t, int8_t);
    friend ostream& operator<<(ostream&, const Sokoban&);
    friend void operator>>(istream&, Sokoban&);
    std::pair<size_t, size_t> gridSize() const;
    void reset() {
            if (_gamestate.size() != 0) {
            for (vector<sf::Sprite*>& sVector : _sprites) {
                for (sf::Sprite* sprite_ptr : sVector) {
                    delete sprite_ptr;
                }
            }
        }
    }
    const std::pair<size_t, size_t> getPlayerPosition()
    { return _play_position; }
    bool isWin() { return _win ;}

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
    std::unordered_map<size_t, std::pair<size_t, bool>> _crates;
    DIRECTION _play_direction;
    Matrix _gamestate;
    char _trail;
    size_t _crate_count;
    bool _win;
};




#endif  // SOKOBAN_HPP_
