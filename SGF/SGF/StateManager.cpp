//
//  StateManager.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 28/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#include "StateManager.h"

sgf::StateManager::StateManager(): m_running(true), m_currentState(), m_states()
{
    
}
sgf::StateManager::~StateManager()
{
    
}



void sgf::StateManager::Init()
{
    for(State::StatePtr e : m_states)
    {
        e->Init();
    }
}
void sgf::StateManager::Cleanup()
{
    auto it = m_states.begin();
    for(State::StatePtr e : m_states)
    {
        e->Cleanup();
        m_states.erase(it);
        it++;
    }
}


void sgf::StateManager::PushState(sgf::State::StatePtr state)
{
    m_currentState->Pause();
    m_states.push_front(state);
    m_currentState = m_states.front();
    m_currentState->Init();
}
void sgf::StateManager::PopState()
{
    m_currentState->Cleanup();
    m_states.pop_front();
    m_currentState = m_states.front();
    m_currentState->Resume();
}



void sgf::StateManager::HandleEvents(sgf::Game* game)
{
    m_currentState->HandleEvents(std::forward<sgf::Game*>(game));
}
void sgf::StateManager::Update(sgf::Game* game)
{
    m_currentState->Update(std::forward<sgf::Game*>(game));

}
void sgf::StateManager::Draw(sgf::Game* game)
{
    m_currentState->Draw(std::forward<sgf::Game*>(game));

}




////// DEFINITION OF A FUNCTION OF THE STATE CLASS //////////

void sgf::State::ChangeState(sgf::State::StatePtr state)
{
    mStateMng.PushState(state);
}