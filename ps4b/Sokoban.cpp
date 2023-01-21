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
 _play_position(std::make_pair(0, 0)),
  _trail('.'),
  _crate_count(0),
  _crates(0),
  _win(false) {}

Sokoban::~Sokoban() {
    if (_gamestate.size() != 0) {
        for (vector<sf::Sprite*>& sVector : _sprites) {
            for (sf::Sprite* sprite_ptr : sVector) {
                delete sprite_ptr;
            }
        }
    }
}

void Sokoban::moveCrate(const DIRECTION dMove,
const bool crate_set, int8_t x_mod, int8_t y_mod) {
        if (crate_set) {
            _sprites[CRATE][_crates[
            _play_position.first *
            _gamestate.cSize() +
            _play_position.second].first]->setTexture(_textures[CRATE_SET]);
            _crate_count--;
        }
        _sprites[CRATE][_crates[
            _play_position.first *
            _gamestate.cSize() +
            _play_position.second
            ].first
        ]
        ->setPosition(
            SPRITE_SIZE * (_play_position.second + x_mod),
            SPRITE_SIZE * (_play_position.first + y_mod));
        _crates[
            (_play_position.first + y_mod) *
              _gamestate.cSize() +
              (_play_position.second + x_mod)
        ] = std::make_pair(
            _crates[_play_position.first *
            _gamestate.cSize() +
            _play_position.second
            ].first, crate_set);

        _crates.erase(
            _play_position.first *
            _gamestate.cSize() +
            (_play_position.second));
        _gamestate(
            _play_position.first + y_mod,
            _play_position.second + x_mod) = 'O';
}

void Sokoban::movePlayer(const DIRECTION dMove) {
    std::pair<size_t, size_t> start_position = _play_position;
    char start_trail = _trail;
    bool crate_set = false;

    size_t y_mod = 0, x_mod = 0;

    switch (dMove) {
    case NORTH:
        y_mod = -1;
        break;
    case WEST:
        x_mod = -1;
        break;
    case SOUTH:
        y_mod = 1;
        break;
    case EAST:
        x_mod = 1;
    default:
        break;
    }

    switch (_gamestate.at(_play_position.first + y_mod,
            _play_position.second + x_mod)) {
        case '.':
                _trail = '.';
                _play_direction = dMove;
                _sprites[dMove][0]->setPosition(
                    SPRITE_SIZE * (_play_position.second + x_mod),
                    SPRITE_SIZE * (_play_position.first + y_mod));
                _play_position = std::make_pair(
                    _play_position.first + y_mod,
                    _play_position.second + x_mod);
                break;

        case '*':
                _trail = '*';
                _play_direction = dMove;
                _sprites[dMove][0]->setPosition(
                    SPRITE_SIZE * (_play_position.second + x_mod),
                    SPRITE_SIZE * (_play_position.first + y_mod));
                _play_position = std::make_pair(
                    _play_position.first + y_mod,
                    _play_position.second + x_mod);
                break;

        case 'O':
                switch (_gamestate.at(_play_position.first + (2 * y_mod),
                _play_position.second + (2 * x_mod))) {
                case '*':
                    crate_set = true;
                case '.':
                    if (_crates[(_play_position.first + y_mod) *
                        _gamestate.cSize() +
                    _play_position.second + x_mod].second) {
                        break; }
                _trail = '.';
                _play_direction = dMove;
                _sprites[dMove][0]->setPosition(
                    SPRITE_SIZE * (_play_position.second + x_mod),
                    SPRITE_SIZE * (_play_position.first + y_mod));
                _play_position = std::make_pair(
                    _play_position.first + y_mod,
                    _play_position.second + x_mod);
                moveCrate(dMove, crate_set, x_mod, y_mod);
                break;
                default:
                    break;
            }
        default:
            break;
    }

    if (start_position != _play_position) {
        _gamestate(_play_position.first, _play_position.second) = '@';
        _gamestate(start_position.first, start_position.second) = start_trail;
    }

    if (_crate_count == 0) {
        _play_direction =
            dMove == NORTH ? SOUTH :
            dMove == SOUTH ? NORTH :
            dMove == WEST ? EAST :
            WEST;
        _sprites[_play_direction][0]
        ->setPosition(
            SPRITE_SIZE *
            _play_position.second,
            SPRITE_SIZE * _play_position.first);
       _win = true;
    }
}

ostream& operator<<(ostream& out, const Sokoban& skb) {
    out << std::to_string(skb.gridSize().second) << " " << skb.gridSize().first;
    for (size_t i = 0; i <= skb._gamestate.rSize(); i++) {
        out << "\n";
        for (size_t j = 0; j < skb._gamestate.cSize(); j++) {
            out << skb._gamestate(i, j);
        }
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
                skb._crates[i * columns + j] =
                std::make_pair(skb._sprites[CRATE].size() - 1, false);
                skb._crate_count++;
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

std::pair<size_t, size_t>Sokoban::gridSize() const {
    return std::make_pair(_gamestate.cSize(), _gamestate.rSize());
}


