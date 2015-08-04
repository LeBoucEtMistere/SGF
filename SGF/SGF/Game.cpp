//
//  Game.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 09/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#include "Game.h"


sgf::Game::Game(const std::string& title, int width, int height, unsigned int style) : _window(sf::VideoMode(width,height),title, style), _stateManager()
{
}

sgf::Game::~Game()
{
}

sf::RenderWindow& sgf::Game::getWindow()
{
    return _window;
}

void sgf::Game::exec()
{
    init();
    
    _stateManager.Init();
    
    load();
    
    sf::Clock clock;
    
    while (_window.isOpen())
    {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            _stateManager.HandleEvents(this,_window, event);
        }
        
        _window.clear();
        
        _stateManager.Update(this, clock.restart());
        
        _stateManager.Draw(this, _window);
        
        _window.display();
        
    }
    
    unload();
    
}



