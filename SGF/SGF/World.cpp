//
//  World.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 14/07/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#include "World.h"

sgf::World::World(): _systems(), _systemCount(0),_activeEntities(), _inactiveEntities(), _entityCount(0)
{
    
}

////////////////////////////////////////////////////
////////////////////   SYSTEMS   ///////////////////
////////////////////////////////////////////////////



void sgf::World::removeAllSystems()
{
    _systems.clear();
    _systemCount = 0;
}

void sgf::World::runSystems(sf::Time const& elapsed)
{
    for (auto it=_systems.begin(); it!=_systems.end(); it++)
    {
        it->second.run(elapsed);
    }
}

void sgf::World::addEntityToSystem(sgf::ISystem& sys, std::unique_ptr<sgf::Entity>& entity)
{
    if( sys.isWatchable(*entity))
        sys.registerEntity(*entity);
}

////////////////////////////////////////////////////
///////////////////// ENTITIES  ////////////////////
////////////////////////////////////////////////////


void sgf::World::registerEntity(std::unique_ptr<sgf::Entity>& entity)
{
    //vérifier la validité de l'entité
    if (_activeEntities.find(entity->getId())!= _activeEntities.end() or _inactiveEntities.find(entity->getId())!= _inactiveEntities.end())
    {
        throw sgf::Exception("Trying to register an entity with an id already registered in the world");
    }
    
    //en prendre l'ownership
    //l'ajouter au vecteur d'entité actives
    auto ret = _activeEntities.emplace(std::make_pair(entity->getId(),std::move(entity)));
    
    //l'ajouter au(x) système(s) compétents
    
    for (auto it = _systems.begin(); it != _systems.end(); ++it)
    {
        if (it->second.isWatchable(*(ret.first->second)))
            it->second.registerEntity(*(ret.first->second));
    }
    
    ++_entityCount;
}
std::size_t sgf::World::getEntityCount() const
{
    return _entityCount;
}

void sgf::World::removeEntity(indexType const& ID)
{
    auto pos =_activeEntities.find(ID);
    if(pos != _activeEntities.end())
    {
        _activeEntities.erase(pos);
        --_entityCount;
        return;
    }
    
    pos =_inactiveEntities.find(ID);
    if(pos != _inactiveEntities.end())
    {
        _inactiveEntities.erase(pos);
        --_entityCount;
        return;
    }
    
    throw sgf::Exception("Trying to delete a non existing entity");
    
}
void sgf::World::removeAllEntities()
{
    _activeEntities.clear();
    _inactiveEntities.clear();
    _entityCount = 0;
}
void sgf::World::reactiveEntity(indexType const& ID)
{
    auto pos = _inactiveEntities.find(ID);
    if (pos == _inactiveEntities.end())
        throw sgf::Exception("Trying to access a non existing Entity");
    
    
    _activeEntities.emplace(pos->first, std::move(pos->second));
    _inactiveEntities.erase(pos);
    
}
void sgf::World::unactiveEntity(indexType const& ID)
{
    auto pos = _activeEntities.find(ID);
    if (pos == _activeEntities.end())
        throw sgf::Exception("Trying to access a non existing Entity");
    
    
    _inactiveEntities.emplace(pos->first, std::move(pos->second));
    _activeEntities.erase(pos);
    
}
bool sgf::World::isActivated(indexType const& ID) const
{
    auto pos =_activeEntities.find(ID);
    if(pos != _activeEntities.end())
    {
        return true;
    }
    auto pos2 = _inactiveEntities.find(ID);
    if (pos2 != _inactiveEntities.end())
    {
        return false;
    }
    throw sgf::Exception("Trying to access a non existing Entity");
    
}






