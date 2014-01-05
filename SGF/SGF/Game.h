//
//  Game.h
//  SGF
//
//  Created by DEPASSE Arthur on 09/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__Game__
#define __SGF__Game__

#include <SFML/Graphics.hpp>
#include "Logger.h"
#include "Exception.h"
#include "Utils.h"
#include "StandardContentManager.h"
#include "StateManager.h"

namespace sgf {

    class Game
    {
        public :
    
        // CTOR AND DTOR //
        
        Game(const std::string& title, int width, int height, unsigned int style = sf::Style::Default);
    
        virtual ~Game();
    
        // MAIN METHOD //
    
        void exec();
    
        // GETTERS //
    
        sf::RenderWindow const& getWindow() const {return mWindow ;}

    
        protected :
    
        virtual void init() = 0;   //Will be called at the beginning of exec()
    
        virtual void load() = 0;   //Will be called at the beginning of exec() after init()
    
        virtual void unload() = 0; //Will be called while exiting the main loop in exec()

    
        sf::RenderWindow mWindow;
    
        sgf::StateManager mStateManager;
    
    };
    
}

#endif /* defined(__SGF__Game__) */
