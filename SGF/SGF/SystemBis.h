//
//  SystemBis.h
//  SGF
//
//  Created by DEPASSE Arthur on 26/07/2015.
//  Copyright (c) 2015 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__SystemBis__
#define __SGF__SystemBis__

#include <unordered_map>
#include <utility>
#include <typeindex>
#include <vector>
#include "Logger.h"
#include "Hash.h"
#include "World.h"
#include "Entity.h"
#include "Exception.h"

namespace sgf
{
    class World;
    
    class IWorld
    {
        
    public:
        
        IWorld(World& world) : _world(world)
        {}
        
        IWorld(const IWorld& rhs) = delete;
        IWorld(IWorld&& rhs) = delete;
        IWorld& operator=(const IWorld&) = delete;
        IWorld& operator=(IWorld&&) = delete;
        
        typedef unsigned int indexType ;
        
        void registerEntity(std::unique_ptr<sgf::Entity>& entity);
        std::size_t getEntityCount() const;
        
        void removeEntity(indexType const& ID);
        void removeAllEntities();
        void reactiveEntity(indexType const& ID);
        void unactiveEntity(indexType const& ID);
        bool isActivated(indexType const& ID) const;
    private:
        sgf::World& _world;
        
        
    };
    
    
    class ISystem
    {
        
    public:
        ISystem(sgf::World& world) : _world(world)
        {}
        virtual ~ISystem() = default;
        virtual void run(sf::Time const& elapsed) = 0;
        virtual void registerEntity(sgf::Entity &entity) = 0;
        virtual bool isWatchable(sgf::Entity &entity) =0;
    protected:
        sgf::IWorld _world;
    };
    
    
    template <class... Components>
    class System : public ISystem
    {
    public:
        
        System(sgf::World& world): ISystem(world), _watchedEntity()
        {}
        
        virtual ~System() = default;
        
        virtual void run(sf::Time const& elapsed) = 0;
        
        virtual bool isWatchable(sgf::Entity &entity)
        {
            for (auto &i : _typeWatched)
            {
                if (!entity.hasComponentType(i))
                {
                    return false;
                }
                
            }
            return true;
        }
        
        void registerEntity(Entity & entity) override
        {
            if (!isWatchable(entity)) throw sgf::Exception("excp");
            
            auto hash = Hash(std::to_string(entity.getId()).c_str(), sizeof(entity.getId()));
            
            if (_watchedEntity.find(hash) != _watchedEntity.end())
                throw sgf::SystemException("",sgf::ExceptionType::SYSTEM_ACCESS_INVALID_ENTITY, "entity already registered by system");
            
            _watchedEntity.insert({hash, entity});
        }
        
        
    protected:
        
        
        void unregisterEntity(Entity const& entity)
        {
            unregisterEntity(entity.getId());
        }
        void unregisterEntity(std::string const& entityId)
        {
            auto hash = Hash(entityId.c_str(),entityId.size());
            if (_watchedEntity.find(hash) == _watchedEntity.end())
                throw sgf::SystemException("",sgf::ExceptionType::SYSTEM_ACCESS_INVALID_ENTITY, "entity not registered by system");
            else
                _watchedEntity.erase(hash);
        }
        void unregisterAllEntites()
        {
            _watchedEntity.clear();
        }
        
        void deleteEntity(sgf::Entity &entity);
        void deleteAllEntities();
        void reactiveEntity(sgf::Entity &entity);
        void unactiveEntity(sgf::Entity &entity);
        bool isActivated(sgf::Entity &entity) const;
        
        
        
        static std::vector<std::type_index> _typeWatched;
        std::unordered_map<uint64_t, sgf::Entity&> _watchedEntity;
        
    };
    
    template<class... Components>
    std::vector<std::type_index> System<Components...>::_typeWatched = {(typeid(Components))...};
    
    template <class... Components>
    void sgf::System<Components...>::deleteEntity(sgf::Entity &entity)
    {
        unregisterEntity(entity);
        _world.removeEntity(entity.getId());
    }
    template <class... Components>
    void sgf::System<Components...>::deleteAllEntities()
    {
        unregisterAllEntites();
        _world.removeAllEntities();
    }
    template <class... Components>
    void sgf::System<Components...>::reactiveEntity(sgf::Entity &entity)
    {
        _world.reactiveEntity(entity.getId());
    }
    template <class... Components>
    void sgf::System<Components...>::unactiveEntity(sgf::Entity &entity)
    {
        _world.unactiveEntity(entity.getId());
    }
    template <class... Components>
    bool sgf::System<Components...>::isActivated(sgf::Entity &entity) const
    {
        return _world.isActivated(entity.getId());
    }
    
    
    
    
}

#endif /* defined(__SGF__SystemBis__) */
