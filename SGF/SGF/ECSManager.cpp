//
//  ECSManager.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 25/03/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#include "ECSManager.h"

sgf::ECSManager::ECSManager(): _activeEntities(), _inactiveEntities(), _entityCount(0), _systems(), _systemCount(0)
{
    
}

sgf::Entity&& sgf::ECSManager::addEntity()
{
    auto pair = _activeEntities.emplace((unsigned int)(_entityCount),std::unique_ptr<sgf::Entity>(new sgf::Entity( (unsigned int)(_entityCount) ) ) );
    ++_entityCount;
    return std::move(*(pair.first->second.get()));
}

void sgf::ECSManager::removeEntity(sgf::Entity& entity)
{
    auto pos =_activeEntities.find(entity.getId());
    if(pos != _activeEntities.end())
    {
        _activeEntities.erase(pos);
        return;
    }
    
    pos =_inactiveEntities.find(entity.getId());
    if(pos != _inactiveEntities.end())
    {
        _inactiveEntities.erase(pos);
        return;
    }
    
    throw sgf::Exception("Trying to delete a non existing entity");
}

sgf::Entity&& sgf::ECSManager::getEntity(indexType index)
{
    auto pos =_activeEntities.find(index);
    if(pos != _activeEntities.end())
    {
        return std::move(*(pos->second.get()));
    }
    else throw sgf::Exception("Tryong to get a non existing Entity");
}

void sgf::ECSManager::removeAllEntities()
{
    _activeEntities.clear();
    _inactiveEntities.clear();
}

void sgf::ECSManager::reactiveEntity(sgf::Entity& entity)
{
    auto pos = _inactiveEntities.find(entity.getId());
    if (pos == _inactiveEntities.end())
        throw sgf::Exception("");
    
    
    _activeEntities.emplace(pos->first, std::move(pos->second));
    _inactiveEntities.erase(pos);
}

void sgf::ECSManager::unactiveEntity(sgf::Entity& entity)
{
    auto pos = _activeEntities.find(entity.getId());
    if (pos == _activeEntities.end())
        throw sgf::Exception("");
    
    
    _inactiveEntities.emplace(pos->first, std::move(pos->second));
    _activeEntities.erase(pos);
}

bool sgf::ECSManager::isActivated(sgf::Entity& entity) const
{
    auto pos = _activeEntities.find(entity.getId());
    if (pos == _activeEntities.end())
        return true;
    else
        return false;
}

void sgf::ECSManager::clear()
{
    removeAllEntities();
}

std::size_t sgf::ECSManager::getEntityCount() const
{
    return _activeEntities.size()+_inactiveEntities.size();
}

template <typename ...ComponentTypes>
void sgf::ECSManager::addSystem()
{
    _systems.emplace((unsigned int)(_systemCount),std::unique_ptr<sgf::ISystem>(new sgf::System<ComponentTypes...>( (unsigned int)(_systemCount) ) ) );
    ++_systemCount;
}

template <typename ...ComponentTypes>
void sgf::ECSManager::removeSystem()
{

}

bool sgf::ECSManager::isSystemTypeExisting() const
{
    return true;
}

bool sgf::ECSManager::isSystemExisting() const
{
    return true;
}

void sgf::ECSManager::removeAllSystems()
{
    
}



