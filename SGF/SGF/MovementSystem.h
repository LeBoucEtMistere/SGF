//
//  MovementSystem.h
//  SGF
//
//  Created by DEPASSE Arthur on 03/03/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#ifndef SGF_MovementSystem_h
#define SGF_MovementSystem_h

#include "ECS.h"
#include "MyComponents.h"
#include <SFML/Graphics.hpp>
#include "Logger.h"
//inheritance approach

/*
class MovementSystem : public sgf::System<PositionComponent>
{
public:
    
    MovementSystem(sgf::ECSWorld& world) : System(world)
    {}
    
    virtual void run()
    {
        LOG("coucou");
        for ( auto &i : _watchedEntity)
        {
            LOG(std::to_string(i.second.getId()).c_str());
        }
    }
};

class MySystem : public sgf::System<PositionComponent,HealthComponent>
{
public:
    
    MySystem(sgf::ECSWorld& world) : System(world)
    {}
    
    virtual void run()
    {
        LOG("coucou 2");
        for ( auto &i : _watchedEntity)
        {
            LOG(std::to_string(i.second.getId()).c_str());
        }
    }
};
*/


struct MovementPolicy
{
    static void computeEntity(sgf::System<MovementPolicy, PositionComponent>::EntityWrapper& wrapper)
    {
        auto comp = wrapper->getComponent<PositionComponent>("pos");
        comp.setData(3.0,4.6);
        if (wrapper.isActivated()) LOG("blob");
    }
};




struct OtherPolicy
{
    static void computeEntity(sgf::System<OtherPolicy, PositionComponent, HealthComponent>::EntityWrapper& wrapper) {}
};

typedef sgf::System<MovementPolicy, PositionComponent> MovementSystem;

typedef sgf::System<OtherPolicy, PositionComponent, HealthComponent> MySystem;




#endif
