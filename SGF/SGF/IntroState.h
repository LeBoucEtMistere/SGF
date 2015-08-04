//
//  IntroState.h
//  SGF
//
//  Created by DEPASSE Arthur on 04/01/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__IntroState__
#define __SGF__IntroState__

#include "State.h"
#include "GameState.h"
#include "StandardRessourceLoader.h"


#include "Logger.h"

#include "Gui.h"


#include "ECS.h"

#include "MyComponents.h"
#include "MovementSystem.h"


#include <SFML/Graphics.hpp>

class MyGame;

class IntroState: public sgf::IState
{
public:
    
    IntroState(sgf::StateManager& stateMng, int width, int height, sf::RenderWindow &window);
    virtual ~IntroState(){}
    
    virtual void Init();
    virtual void Cleanup();
    
    virtual void Pause();
    virtual void Resume();
    
    virtual void HandleEvents(sgf::Game *,sf::RenderWindow& window, sf::Event const& evt);
    virtual void Update(sgf::Game* game, sf::Time const& elapsed);
    virtual void Draw(sgf::Game *,sf::RenderWindow& window);
    
protected:
    
    IntroState(const IntroState& rhs)=delete;
    void operator=(const IntroState& rhs)=delete;
    
private:
    
    sgf::TextureLoader _texLoader;
    sgf::SpriteLoader _spriteLoader;

    
    sgf::MusicLoader _musicLoader;
    sf::Music* music;
    
    sgf::gui::Button jouer;
    sgf::gui::Button quitter;
    sgf::gui::Button reglages;
    
    sgf::World world;
    
    sf::RenderWindow &_window;
    std::vector< std::unique_ptr<sgf::ISystem> > _systems;
    
    int _width;
    int _height;
    
};

#endif /* defined(__SGF__IntroState__) */
