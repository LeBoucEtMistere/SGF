//
//  PauseState.h
//  SGF
//
//  Created by DEPASSE Arthur on 22/01/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__PauseState__
#define __SGF__PauseState__

#include "State.h"
#include <SFML/Graphics.hpp>
#include "Logger.h"


class MyGame;

class PauseState: public sgf::IState
{
public:
    
    PauseState(sgf::StateManager& stateMng);
    virtual ~PauseState(){}
    
    virtual void Init();
    virtual void Cleanup();
    
    virtual void Pause();
    virtual void Resume();
    
    virtual void HandleEvents(sgf::Game *,sf::RenderWindow& window, sf::Event const& evt);
    virtual void Update(sgf::Game* game, sf::Time const& elapsed);
    virtual void Draw(sgf::Game *,sf::RenderWindow& window);
    
protected:
    
    PauseState(const PauseState& rhs)=delete;
    void operator=(const PauseState& rhs)=delete;
    
private:
    sf::Text text;
    sf::Font font;
    
};
#endif /* defined(__SGF__PauseState__) */
