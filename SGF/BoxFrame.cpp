//
//  BoxFrame.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 28/01/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#include "BoxFrame.h"

sgf::gui::BoxFrame::BoxFrame(float originX, float originY, float width, float height, std::string const& ID) : _position(originX, originY, width, height), _id(ID)
{

}
sgf::gui::BoxFrame::BoxFrame(sf::Vector2f const& origin, float width, float height, std::string const& ID) : _position(origin, width, height), _id(ID)
{

}

void sgf::gui::BoxFrame::centerAt(float x, float y)
{
    _position.x = x-(_position.width/2);
    _position.y = y-(_position.height/2);
}
void sgf::gui::BoxFrame::centerAt(sf::Vector2f const& center)
{
    _position.x = center.x-(_position.width/2);
    _position.y = center.y-(_position.height/2);
}

void sgf::gui::BoxFrame::setOrigin(float x, float y)
{
    _position.x = x;
    _position.y = y;
}
void sgf::gui::BoxFrame::setOrigin(sf::Vector2f const& origin)
{
    _position.x = origin.x;
    _position.y = origin.y;
}

void sgf::gui::BoxFrame::setSize(float width, float height)
{
    _position.width = width;
    _position.height = height;
}

void sgf::gui::BoxFrame::setDimension (float originX, float originY, float width, float height)
{
    _position.x = originX;
    _position.y = originY;
    _position.width = width;
    _position.height = height;
}
void sgf::gui::BoxFrame::setDimension (sf::Vector2f const& origin, float width, float height)
{
    _position.x = origin.x;
    _position.y = origin.y;
    _position.width = width;
    _position.height = height;
}

sgf::gui::Box const& sgf::gui::BoxFrame::getDimension() const
{
    return _position;
}

void sgf::gui::BoxFrame::setId(std::string const& str)
{
    _id = str;
}

std::string const& sgf::gui::BoxFrame::getId() const
{
    return _id;
}


