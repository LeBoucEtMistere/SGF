//
//  State.h
//  SGF
//
//  Created by DEPASSE Arthur on 28/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__State__
#define __SGF__State__

#include <iostream>

#include <SFML/Graphics.hpp>



namespace sgf
{
    
    class Game;
    class StateManager;

    class IState
    {
    public:
        
        IState(StateManager& stateMng): _stateMng(stateMng){}
        IState(const IState& rhs) = delete;
        void operator=(const IState& rhs) = delete;
        
        virtual ~IState(){}
    
        virtual void Init() = 0;
        virtual void Cleanup() = 0;
    
        virtual void Pause() = 0;
        virtual void Resume() = 0;
    
        virtual void HandleEvents(sgf::Game *,sf::RenderWindow& window, sf::Event const& evt) = 0;
        virtual void Update(sgf::Game* game, sf::Time const& elapsed) = 0;
        virtual void Draw(sgf::Game *,sf::RenderWindow& window) = 0;
    
    protected:
        
        void PushState(std::unique_ptr<sgf::IState>&& state);    
        void ReplaceState(std::unique_ptr<sgf::IState>&& state);
        void PopState();
        StateManager& _stateMng;

    
    };
}

#endif /* defined(__SGF__State__) */
