//
//  MyGame.h
//  SGF
//
//  Created by DEPASSE Arthur on 03/01/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__MyGame__
#define __SGF__MyGame__

#include <thread>

#include "Game.h"
#include "IntroState.h"


class MyGame : public sgf::Game
{
    
public:
    
    MyGame(const std::string& title, int width, int height, unsigned int style = sf::Style::Default);
    
    virtual ~MyGame();
    
protected:
    
    virtual void init();
    virtual void load();
    virtual void unload();
    
    int _width;
    int _height;

};


#endif /* defined(__SGF__MyGame__) */
