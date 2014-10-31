//
//  Button.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 28/01/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#include "Button.h"


sgf::gui::Button::Button() : BoxFrame(0,0,0,0,""), _state(sgf::gui::ButtonState::Idle), _idleSprite(nullptr), _clickedSprite(nullptr), _disabledSprite(nullptr), _currentSprite(nullptr)
{
}
sgf::gui::Button::Button(float originX, float originY, float width, float height, std::string const& ID) : BoxFrame(originX,originY,width,height,ID), _state(sgf::gui::ButtonState::Idle), _idleSprite(nullptr), _clickedSprite(nullptr), _disabledSprite(nullptr), _currentSprite(nullptr)
{
}
sgf::gui::Button::Button(sf::Vector2f const& origin, float width, float height, std::string const& ID) : BoxFrame(origin.x,origin.y,width,height,ID), _state(sgf::gui::ButtonState::Idle), _idleSprite(nullptr), _clickedSprite(nullptr), _disabledSprite(nullptr), _currentSprite(nullptr)
{
}

bool sgf::gui::Button::collideWith (float x, float y)
{
    if (x >= _position.x
            && y < _position.y + _position.height
            && y >= _position.y
            && x < _position.x + _position.width)
    return true;
       else
    return false;
}
bool sgf::gui::Button::collideWith (sf::Vector2f const& vec)
{
    if (vec.x >= _position.x
        && vec.y < _position.y + _position.height
        && vec.y >= _position.y
        && vec.x < _position.x + _position.width)
        return true;
    else
        return false;
}

void sgf::gui::Button::setIdleSprite (sf::Sprite& sprite)
{
    _idleSprite = &sprite;
}
void sgf::gui::Button::setClickedSprite (sf::Sprite& sprite)
{
    _clickedSprite = &sprite;
}
void sgf::gui::Button::setDisabledSprite (sf::Sprite& sprite)
{
    _disabledSprite = &sprite;
}

sf::Sprite const& sgf::gui::Button::getCurrentSprite()
{
    switch (_state) {
        case sgf::gui::Idle:
            _idleSprite->setPosition(_position.x, _position.y);
            return *_idleSprite;
            break;
        case sgf::gui::Clicked:
            _clickedSprite->setPosition(_position.x, _position.y);
            return *_clickedSprite;
            break;
        case sgf::gui::Disabled:
            _disabledSprite->setPosition(_position.x, _position.y);
            return *_disabledSprite;
            break;
        default:
            _idleSprite->setPosition(_position.x, _position.y);
            return *_idleSprite;
            break;
    }
}
void sgf::gui::Button::setCurrentState(sgf::gui::ButtonState const& state)
{
    _state = state;
}
sgf::gui::ButtonState const& sgf::gui::Button::getCurrentState()
{
    return _state;
}


