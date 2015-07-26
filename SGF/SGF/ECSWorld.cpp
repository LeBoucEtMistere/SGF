//
//  ECSWorld.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 14/07/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#include "ECSWorld.h"

sgf::ECSWorld::ECSWorld(): _systems(), _systemCount(0),_activeEntities(), _inactiveEntities(), _entityCount(0)
{
    
}

////////////////////////////////////////////////////
////////////////////   SYSTEMS   ///////////////////
////////////////////////////////////////////////////



void sgf::ECSWorld::removeAllSystems()
{
    _systems.clear();
    _systemCount = 0;
}

void sgf::ECSWorld::runSystems(sf::Time const& elapsed)
{
    for (auto &i : _systems)
    {
        i.second->run(std::forward<sf::Time const&>(elapsed));
    }
}

void sgf::ECSWorld::addEntityToSystem(std::unique_ptr<sgf::ISystem>& sys, std::unique_ptr<sgf::Entity>& entity)
{
    if( sys->isWatchable(*entity))
        sys->registerEntity(*entity);
}

////////////////////////////////////////////////////
///////////////////// ENTITIES  ////////////////////
////////////////////////////////////////////////////


void sgf::ECSWorld::registerEntity(std::unique_ptr<sgf::Entity>& entity)
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
        if (it->second->isWatchable(*(ret.first->second)))
            it->second->registerEntity(*(ret.first->second));
    }
    
    ++_entityCount;
}
std::size_t sgf::ECSWorld::getEntityCount() const
{
    return _entityCount;
}

void sgf::ECSWorld::removeEntity(indexType const& ID)
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
void sgf::ECSWorld::removeAllEntities()
{
    _activeEntities.clear();
    _inactiveEntities.clear();
    _entityCount = 0;
}
void sgf::ECSWorld::reactiveEntity(indexType const& ID)
{
    auto pos = _inactiveEntities.find(ID);
    if (pos == _inactiveEntities.end())
        throw sgf::Exception("Trying to access a non existing Entity");
    
    
    _activeEntities.emplace(pos->first, std::move(pos->second));
    _inactiveEntities.erase(pos);

}
void sgf::ECSWorld::unactiveEntity(indexType const& ID)
{
    auto pos = _activeEntities.find(ID);
    if (pos == _activeEntities.end())
        throw sgf::Exception("Trying to access a non existing Entity");
    
    
    _inactiveEntities.emplace(pos->first, std::move(pos->second));
    _activeEntities.erase(pos);
 
}
bool sgf::ECSWorld::isActivated(indexType const& ID) const
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






