// Copyright [2022] <Andrew Allman>




#include "./Sokoban.hpp"
#include "./Matrix.hpp"

using std::string;
using std::vector;
using std::istream;
using std::ostream;


Sokoban::Sokoban() : _textures(vector<sf::Texture>(NUM_SPRITES)),
 _sprites(vector<vector<sf::Sprite*>>(NUM_SPRITES)),
 _play_direction(SOUTH),
 _play_position(std::make_pair(0, 0)) {}

Sokoban::~Sokoban() {
    if (_gamestate.size() != 0) {
        for (vector<sf::Sprite*>& sVector : _sprites) {
            for (sf::Sprite* sprite_ptr : sVector) {
                delete sprite_ptr;
            }
        }
    }
}

void Sokoban::movePlayer() {}

ostream& operator<<(ostream& out, const Sokoban& skb) {
    for (size_t i = 0; i < skb._gamestate.rSize(); i++) {
        for (size_t j = 0; j < skb._gamestate.cSize(); j++) {
            out << skb._gamestate(i, j);
        }
        out << '\n';
    }
    return out;
}

void operator>>(istream& initstream, Sokoban& skb) {
    size_t rows, columns;
    string buffer;
    bool char_set = false;
    if (!(initstream >> rows) || !(initstream >> columns)) {
        throw std::runtime_error("Invalid Dimension Data reading from Stream.");
    }

    skb._gamestate = Matrix(rows, columns);

    for (size_t texture_itr = 0;
        texture_itr < TEXTURE_FP.size();
        texture_itr++) {
            skb._textures[texture_itr].loadFromFile(TEXTURE_FP[texture_itr]);
    }

    for (size_t sprite_card_itr = static_cast<size_t>(CHAR_N);
        sprite_card_itr <= static_cast<size_t>(CHAR_W);
        sprite_card_itr++) {
            skb._sprites[sprite_card_itr].push_back(new sf::Sprite);
            skb._sprites[sprite_card_itr][0]->setTexture(
                skb._textures[sprite_card_itr]);
    }

    for (size_t i = 0; i < rows; i++) {
        if (!(initstream >> buffer)) {
            throw std::runtime_error(
                "Stream does not match provided dimensions.");
        }
        for (size_t j = 0; j < columns; j++) {
            switch (buffer[j]) {
            case '.':
                skb._sprites[GROUND].push_back(new sf::Sprite);
                skb._sprites[GROUND].back()->setTexture(
                    skb._textures[GROUND]);
                skb._sprites[GROUND].back()->setPosition(
                    SPRITE_SIZE * j, SPRITE_SIZE * i);
                skb._gamestate(i, j) = buffer[j];
                break;
            case '#':
                skb._sprites[WALL].push_back(new sf::Sprite);
                skb._sprites[WALL].back()->setTexture(
                    skb._textures[WALL]);
                skb._sprites[WALL].back()->setPosition(
                    SPRITE_SIZE * j, SPRITE_SIZE * i);
                skb._gamestate(i, j) = buffer[j];
                break;
            case 'O':
                skb._sprites[GROUND].push_back(new sf::Sprite);
                skb._sprites[GROUND].back()->setTexture(
                    skb._textures[GROUND]);
                skb._sprites[GROUND].back()->setPosition(
                    SPRITE_SIZE * j, SPRITE_SIZE * i);
                skb._sprites[CRATE].push_back(new sf::Sprite);
                skb._sprites[CRATE].back()->setTexture(
                    skb._textures[CRATE]);
                skb._sprites[CRATE].back()->setPosition(
                    SPRITE_SIZE * j, SPRITE_SIZE * i);
                skb._gamestate(i, j) = buffer[j];
                break;
            case '*':
                skb._sprites[STORAGE].push_back(new sf::Sprite);
                skb._sprites[STORAGE].back()->setTexture(
                    skb._textures[STORAGE]);
                skb._sprites[STORAGE].back()->setPosition(
                    SPRITE_SIZE * j, SPRITE_SIZE * i);
                skb._gamestate(i, j) = buffer[j];
                break;
            case '@':
                if (char_set) {
                    throw std::runtime_error(
                        "Attempted to initialize more than one character.");
                }
                skb._sprites[GROUND].push_back(new sf::Sprite);
                skb._sprites[GROUND].back()->setTexture(
                    skb._textures[GROUND]);
                skb._sprites[GROUND].back()->setPosition(
                    SPRITE_SIZE * j, SPRITE_SIZE * i);
                skb._sprites[skb._play_direction][0]->setPosition(
                    SPRITE_SIZE * j, SPRITE_SIZE * i);
                skb._gamestate(i, j) = buffer[j];
                skb._play_position = std::make_pair(i, j);
                char_set = true;
                break;
            default:
                break;
            }
        }
    }
}

std::pair<size_t, size_t>Sokoban::gridSize() {
    return std::make_pair(_gamestate.cSize(), _gamestate.rSize());
}
