//
//  Game.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 09/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#include "Game.h"


sgf::Game::Game(const std::string& title, int width, int height, unsigned int style) : mWindow(sf::VideoMode(width,height),title, style), mTextureLoader("texture_loader_1")
{
}

sgf::Game::~Game()
{}

// MAIN METHOD //

void sgf::Game::exec()
{
    

    try
    {
        mTextureLoader.LoadRessource("mouton", "/Users/depassearthur/SGF/SGF/DerivedData/SGF/Build/Products/Debug/mouton_punk.jpg");
        
    }
    catch (std::exception const& e)
    {
        ERR(e.what())

    }
    
    sgf::TextureLoader::ptrTexture tex;
    
    try
    {
        tex = mTextureLoader.getRessource("mouton");
        
    }
    catch (std::exception const& e)
    {
        ERR(e.what())

    }
    
    tex->setSmooth(true);
    sf::Sprite sprite;
    sprite.setTexture(*tex);

    while (mWindow.isOpen())
    {
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mWindow.close();
        }
        
        mWindow.clear(sf::Color::Black);
        
        mWindow.draw(sprite);
        
        mWindow.display();
    }
}