// Copyright [2022] <Andrew Allman>




#ifndef SPRITES_HPP_
#define SPRITES_HPP_

#include<math.h>
#include<SFML/Graphics.hpp>
#include <SFML/Window.hpp>


class FX_KNOB : public sf::Drawable, public sf::Transformable {
 public:
    FX_KNOB(double min, double max, sf::Vector2f pos, double init);
    void adjust(sf::Vector2f);
    void update();

    double getValue() { return _min + _value * (_max - _min); }
    bool hasMouseHover(sf::Vector2f mPos) {
      return _skin.getGlobalBounds().contains(mPos);
    }

 private:
      virtual void draw(sf::RenderTarget& target,
      sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(_skin, states);
    }
    double _min;
    double _max;
    double _value;
    sf::Texture _texture;
    sf::Sprite _skin;
};


FX_KNOB::FX_KNOB(double min, double max,
sf::Vector2f pos, double init) :_min(min), _max(max), _value(init) {
  _texture.loadFromFile("knob.png");
  _skin.setTexture(_texture);
  _skin.setOrigin(_skin.getGlobalBounds().width/2,
    _skin.getGlobalBounds().height/2);
  _skin.setPosition(pos);
  _skin.setRotation(0);
}

void FX_KNOB::update() {
  if (_value == 0) {
      _skin.rotate(240);
  } else if (_value <= 0.5) {
      _skin.rotate(360 - _value * 120);
  } else {
    _skin.rotate(_value * 120);
  }
}

void FX_KNOB::adjust(sf::Vector2f mPos) {
  double perf_rot;
  double current_rotation = _skin.getRotation();
  double rot_angle = (atan2(mPos.y - _skin.getPosition().y, mPos.x -
  _skin.getPosition().x) * 180 / M_PI) + 90;

  rot_angle = rot_angle < 0 ? rot_angle + 360 : rot_angle;

  if (rot_angle < 240 && rot_angle > 120) {
    if (rot_angle < 180) {
      perf_rot = 120 - current_rotation;
    } else {
      perf_rot = 240 - current_rotation;
    }
  } else {
    perf_rot = (rot_angle - current_rotation);
  }

  _skin.rotate(perf_rot);

  if (_skin.getRotation() >= 240 && _skin.getRotation() < 360) {
    _value = (120 - abs(_skin.getRotation() - 360)) / 240.0;
  } else {
    _value = 0.5 + _skin.getRotation() / 240.0;
  }
}

class SWITCH : public sf::Drawable, public sf::Transformable{
 public:
    explicit SWITCH(sf::Vector2f pos);
    void flip();
    bool hasMouseHover(sf::Vector2f mPos) {
      return _skin.getGlobalBounds().contains(mPos);
    }

    bool getValue() { return _val; }

 private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(_skin, states);
    }
    sf::Texture _texture;
    sf::Sprite _skin;
    bool _val;
};

SWITCH::SWITCH(sf::Vector2f pos) : _val(false) {
  _texture.loadFromFile("switch_off.png");
  _skin.setTexture(_texture);
  _skin.setOrigin(_skin.getGlobalBounds().width/2,
  _skin.getGlobalBounds().height/2);
  _skin.setPosition(pos);
  _skin.setRotation(0);
}

void SWITCH::flip() {
  switch (_val) {
  case true:
    _texture.loadFromFile("switch_off.png");
    _skin.setTexture(_texture);
    _val = false;
    break;
  case false:
    _texture.loadFromFile("switch_on.png");
    _skin.setTexture(_texture);
    _val = true;
  }
}

#endif  // SPRITES_HPP_
