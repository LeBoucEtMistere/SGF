//
//  Game.h
//  SGF
//
//  Created by DEPASSE Arthur on 09/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__Game__
#define __SGF__Game__

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Logger.h"
#include "Exception.h"
#include "ContentManager.h"
#include "StateManager.h"

namespace sgf {

class Game
{
public :
    
    // CTOR AND DTOR //
    
    Game(const std::string& title, int width, int height, unsigned int style = sf::Style::Default);
    
    virtual ~Game();
    
    // MAIN METHOD //
    
    void exec();
    
    // GETTERS //
    
    sf::RenderWindow const& getWindow() const {return mWindow ;}

    
protected :
    
    virtual void init()
    {
        throw sgf::Exception("No Init Function def for your Game", sgf::ExceptionLevel::FATAL);
    }
    
    virtual void load()
    {
        throw sgf::Exception("No Load Function def for your Game", sgf::ExceptionLevel::FATAL);
    }
    
    virtual void unload()
    {
        throw sgf::Exception("No Unload Function def for your Game", sgf::ExceptionLevel::FATAL);
    }
    
    sf::RenderWindow mWindow;
    
    sgf::TextureLoader mTextureLoader;
    
};
    
}

#endif /* defined(__SGF__Game__) */
