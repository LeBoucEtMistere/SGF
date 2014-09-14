//
//  System.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 28/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#include "System.h"
#include "ECSWorld.h"

// Systems methods defs

template <class Policy, class... Components>
void sgf::System<Policy,Components...>::deleteEntity(sgf::Entity &entity)
{
    unregisterEntity(entity);
    _world.removeEntity(entity.getId());
}
template <class Policy, class... Components>
void sgf::System<Policy,Components...>::deleteAllEntities()
{
    unregisterAllEntites();
    _world.removeAllEntities();
}
template <class Policy, class... Components>
void sgf::System<Policy,Components...>::reactiveEntity(sgf::Entity &entity)
{
    _world.reactiveEntity(entity.getId());
}
template <class Policy, class... Components>
void sgf::System<Policy,Components...>::unactiveEntity(sgf::Entity &entity)
{
    _world.unactiveEntity(entity.getId());
}
template <class Policy, class... Components>
bool sgf::System<Policy,Components...>::isActivated(sgf::Entity &entity) const
{
    _world.isActivated(entity.getId());
}
