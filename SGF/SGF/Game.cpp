//
//  Game.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 09/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#include "Game.h"


sgf::Game::Game(const std::string& title, int width, int height, unsigned int style) : mWindow(sf::VideoMode(width,height),title, style), mStateManager()
{
}

sgf::Game::~Game()
{
}

// MAIN METHOD //

void sgf::Game::exec()
{
    init();
    
    load();
    
    while (mWindow.isOpen())
    {
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
            mStateManager.HandleEvents(this);
            
        }
        
        mStateManager.Update(this);
        
        mWindow.clear();
        
        mStateManager.Draw(this);
        
        mWindow.display();
        
    }
    
    unload();
    
}



