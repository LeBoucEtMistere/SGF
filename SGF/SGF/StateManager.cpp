//
//  StateManager.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 28/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#include "StateManager.h"

sgf::StateManager::StateManager(): _states()
{
    
}
sgf::StateManager::~StateManager()
{
    
}

void sgf::StateManager::Init()
{

}

void sgf::StateManager::Cleanup()
{

}

void sgf::StateManager::PushState(StatePtr&& state)
{
    if (!_states.empty())
    {
        currentState()->Pause();
    }
    _states.push(StatePtr(std::move(state)));
    currentState()->Init();
}

void sgf::StateManager::PopState()
{
    if (!_states.empty())
    {
        currentState()->Cleanup();
        _states.pop();
        if (!_states.empty())
        {
            currentState()->Resume();
        }
    }

}

void sgf::StateManager::PopAndPush(StatePtr&& state)
{
    PopState();
    PushState(std::forward<StatePtr&&>(state));
}

void sgf::StateManager::HandleEvents(sgf::Game* game, sf::RenderWindow& window, sf::Event const& evt)
{
    currentState()->HandleEvents(std::forward<sgf::Game*>(game), std::forward<sf::RenderWindow&>(window), std::forward<sf::Event const&>(evt));
}

void sgf::StateManager::Update(sgf::Game* game, sf::Time const& elapsed)
{
    currentState()->Update(std::forward<sgf::Game*>(game), std::forward<sf::Time const&>(elapsed));
}

void sgf::StateManager::Draw(sgf::Game* game, sf::RenderWindow& window)
{
    currentState()->Draw(std::forward<sgf::Game*>(game), std::forward<sf::RenderWindow&>(window));
}

std::unique_ptr<sgf::IState>& sgf::StateManager::currentState()
{
    if (!_states.empty()) return _states.top();
    
    else throw sgf::Exception("No State in the StateStack");
}










