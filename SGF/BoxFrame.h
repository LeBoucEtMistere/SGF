//
//  BoxFrame.h
//  SGF
//
//  Created by DEPASSE Arthur on 28/01/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__BoxFrame__
#define __SGF__BoxFrame__

#include <SFML/Graphics.hpp>

namespace sgf
{
    namespace gui
    {
        
        struct Box
        {
            
            Box(float originX, float originY, float givenwidth, float givenheight): x(originX), y(originY), width(givenwidth), height(givenheight) {}
            Box(sf::Vector2f const& origin, float givenwidth, float givenheight): x(origin.x), y(origin.y), width(givenwidth), height(givenheight) {}
            float x;
            float y;
            float width;
            float height;
        };
        
        class BoxFrame
        {
        public:
            
            BoxFrame(float originX, float originY, float width, float height, std::string const& ID);
            BoxFrame(sf::Vector2f const& origin, float width, float height, std::string const& ID);
            
            void centerAt(float x, float y);
            void centerAt(sf::Vector2f const& center);
            
            void setOrigin(float x, float y);
            void setOrigin(sf::Vector2f const& origin);
            
            void setSize(float width, float height);
            
            void setDimension (float originX, float originY, float width, float height);
            void setDimension (sf::Vector2f const& origin, float width, float height);
            
            sgf::gui::Box const& getDimension() const;
            
            void setId(std::string const& str);
            std::string const& getId() const;

            
        protected:
            
            sgf::gui::Box _position;
            std::string _id;
        };
        
   
    }
}

#endif /* defined(__SGF__BoxFrame__) */
