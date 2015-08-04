//
//  MyGame.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 03/01/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#include "MyGame.h"

MyGame::MyGame(const std::string& title, int width, int height, unsigned int style) :
                sgf::Game(title, width, height, style), _width(width), _height(height)

{
    _stateManager.PushState(std::unique_ptr<IntroState>(new IntroState (_stateManager, _width, _height, getWindow())));
}

MyGame::~MyGame()
{
    
}

void MyGame::init()
{
    
}
void MyGame::load()
{

}
void MyGame::unload()
{
    _stateManager.Cleanup();
}


