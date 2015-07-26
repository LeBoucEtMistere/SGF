//
//  GameState.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 22/01/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#include "GameState.h"


GameState::GameState(sgf::StateManager& stateMng): sgf::IState(stateMng), text(), font()
{
    font.loadFromFile("font.ttf");
    
    text.setFont(font);
    
    text.setString("GameState");
    
    text.setCharacterSize(24);
}

void GameState::Init()
{
    
}
void GameState::Cleanup()
{
    
}

void GameState::Pause()
{
    
}
void GameState::Resume()
{
    
}


void GameState::HandleEvents(sgf::Game *,sf::RenderWindow& window, sf::Event const& evt)
{
    switch (evt.type) {
        case sf::Event::Closed:
            window.close();
            break;
            
        case sf::Event::KeyPressed:
            switch (evt.key.code)
            {
            case sf::Keyboard::P:
                PushState(std::unique_ptr<PauseState>(new PauseState(_stateMng)));
                break;
            case sf::Keyboard::Escape:
                window.close();
                break;
            default:
                break;
            }
        break;
        default:
        break;
    }
}
void GameState::Update(sgf::Game* game, sf::Time const& elapsed)
{
}
void GameState::Draw(sgf::Game *,sf::RenderWindow& window)
{
    window.draw(text);
}