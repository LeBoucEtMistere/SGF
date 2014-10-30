//
//  System.h
//  SGF
//
//  Created by DEPASSE Arthur on 28/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__System__
#define __SGF__System__

#include <unordered_map>
#include <utility>
#include <typeindex>
#include <vector>
#include "Logger.h"
#include "Hash.h"
#include "ECSWorld.h"
#include "Entity.h"
#include "Exception.h"


namespace sgf
{
    class ECSWorld;
    
    class ECSIWorld
    {
        
    public:
        
        ECSIWorld(ECSWorld& world) : _world(world)
        {}
        
        ECSIWorld(const ECSIWorld& rhs) = delete;
        ECSIWorld(ECSIWorld&& rhs) = delete;
        ECSIWorld& operator=(const ECSIWorld&) = delete;
        ECSIWorld& operator=(ECSIWorld&&) = delete;
        
        typedef unsigned int indexType ;
        
        void registerEntity(std::unique_ptr<sgf::Entity>& entity);
        std::size_t getEntityCount() const;
        
        void removeEntity(indexType const& ID);
        void removeAllEntities();
        void reactiveEntity(indexType const& ID);
        void unactiveEntity(indexType const& ID);
        bool isActivated(indexType const& ID) const;
    private:
        ECSWorld& _world;
        
        
    };
    

    
    
    
    
    
    
    class EntityWrapper;
    
    class ISystem
    {

    public:
        ISystem(sgf::ECSWorld& world) : _world(world)
        {}
        virtual ~ISystem() = default;
        virtual void run() = 0;
    protected:
        sgf::ECSIWorld _world;
    };
    
    
    template <class Policy, class... Components>
    class System : public ISystem
    {
    public:
        
        System(sgf::ECSWorld& world): ISystem(world), _watchedEntity()
        {}
        
        virtual ~System() = default;
        
        // nested class //
        
        class EntityWrapper {
            sgf::System<Policy,Components...> * _system;
            sgf::Entity* _entity;
        public:
            
            EntityWrapper(sgf::System<Policy,Components...>* system, sgf::Entity& entity) : _system(system), _entity(&entity) {}
            
            void unregisterEntity()
            {
                _system->unregisterEntity(*_entity);
            }
            void deleteEntity()
            {
                _system->deleteEntity(*_entity);
            }
            void deleteAllEntities()
            {
                _system->deleteAllEntities();
            }
            void reactiveEntity()
            {
                _system->reactiveEntity(*_entity);
            }
            void unactiveEntity()
            {
                _system->unactiveEntity(*_entity);
            }
            bool isActivated() const
            {
                return _system->isActivated(*_entity);
            }
            sgf::Entity* operator->()
            {
                return _entity;
            }
        };
        
        // end of nested class //
        
        virtual void run()
        {
            for (auto &i : _watchedEntity)
            {
                LOG("da");
                EntityWrapper wrapper(this, i.second);
                Policy::computeEntity(wrapper);
            }
        }
        
        static bool isWatchable(sgf::Entity &entity)
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
        
        void registerEntity(Entity & entity)
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
    
    template<class Policy, class... Components>
    std::vector<std::type_index> System<Policy,Components...>::_typeWatched = {(typeid(Components))...};
    
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
        return _world.isActivated(entity.getId());
    }
    
    


}


#endif /* defined(__SGF__System__) */
