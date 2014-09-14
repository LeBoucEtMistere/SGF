//
//  Entity.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 28/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#include "Entity.h"

sgf::Entity::Entity(unsigned int ID) : _id(ID)
{
    
}



////////////////////////////////////////////////////
//////////////////// COMPONENTS  ///////////////////
////////////////////////////////////////////////////

bool sgf::Entity::hasComponentType(std::type_index const& type)
{
    auto it = std::find_if(_activeComponents.begin(),
                           _activeComponents.end(),
                           [& type](const MapType::value_type &elem) -> bool
                           { return elem.first == type; }
                           );
    if ( it != _activeComponents.end()) return true;
    
    auto it2 = std::find_if(_inactiveComponents.begin(),
                            _inactiveComponents.end(),
                            [& type](const MapType::value_type &elem) -> bool
                            { return elem.first == type; }
                            );
    if ( it2 != _inactiveComponents.end()) return true;
    
    return false;

}


void sgf::Entity::inactiveComponent(std::string const& ID)
{
    auto it = std::find_if(_activeComponents.begin(),
                           _activeComponents.end(),
                           [& ID](const MapType::value_type &elem) -> bool
                           { return elem.second->getId() == ID;}
                           );
    if ( it != _activeComponents.end())
    {
        _inactiveComponents.emplace(it->first, std::move(it->second));
        _activeComponents.erase(it);
    }
    else throw sgf::Exception("excp");
}

void sgf::Entity::reactiveComponent(std::string const& ID)
{
    auto it = std::find_if(_inactiveComponents.begin(),
                           _inactiveComponents.end(),
                           [& ID](const MapType::value_type &elem) -> bool
                           { return elem.second->getId() == ID;}
                           );
    if ( it != _inactiveComponents.end())
    {
        _activeComponents.emplace(it->first, std::move(it->second));
        _inactiveComponents.erase(it);
    }
    else throw sgf::Exception("excp");
}

void sgf::Entity::deleteComponent(std::string const& ID)
{
    auto it = std::find_if(_activeComponents.begin(),
                           _activeComponents.end(),
                           [& ID](const MapType::value_type &elem) -> bool
                           { return elem.second->getId() == ID;}
                           );
    if ( it != _activeComponents.end())
    {
        _activeComponents.erase(it);
        return;
    }
    auto it2 = std::find_if(_inactiveComponents.begin(),
                           _inactiveComponents.end(),
                            [& ID](const MapType::value_type &elem) -> bool
                           { return elem.second->getId() == ID;}
                           );
    if ( it2 != _inactiveComponents.end())
    {
        _inactiveComponents.erase(it2);
        return;
    }
    else throw sgf::Exception("excp");
}




