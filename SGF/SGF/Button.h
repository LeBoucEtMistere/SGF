//
//  Button.h
//  SGF
//
//  Created by DEPASSE Arthur on 28/01/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__Button__
#define __SGF__Button__

#include <SFML/Graphics.hpp>

#include "BoxFrame.h"
#include "Logger.h"

namespace sgf
{
namespace gui
{
    
    enum ButtonState
    {
        Idle,
        Clicked,
        Disabled
    };
   
    class Button : public sgf::gui::BoxFrame
    {
    public:
        
        Button();
        Button(float originX, float originY, float width, float height, std::string const& ID);
        Button(sf::Vector2f const& origin, float width, float height, std::string const& ID);
        
        bool collideWith (float x, float y);
        bool collideWith (sf::Vector2f const& vec);
        
        void setIdleSprite (sf::Sprite& sprite);
        void setClickedSprite (sf::Sprite& sprite);
        void setDisabledSprite (sf::Sprite& sprite);
        
        sf::Sprite const& getCurrentSprite();
        
        void setCurrentState(ButtonState const& state);
        ButtonState const& getCurrentState();
        

    protected:
        
        ButtonState _state;
 
        sf::Sprite* _idleSprite;
        sf::Sprite* _clickedSprite;
        sf::Sprite* _disabledSprite;
        sf::Sprite* _currentSprite;
        
    };
    
}
}


#endif /* defined(__SGF__Button__) */
