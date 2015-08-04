//
//  World.h
//  SGF
//
//  Created by DEPASSE Arthur on 14/07/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__World__
#define __SGF__World__

#include "Entity.h"
#include "System.h"
#include <unordered_map>
#include <typeindex>

namespace sgf
{
    class ISystem;
    class IWorld;
    
    class World
    {
    public:
        
        friend class ISystem;
        friend class IWorld;
        
        typedef unsigned int indexType ;
        
        World();
        
        World(const World& rhs) = delete;
        World(World&& rhs) = delete;
        World& operator=(const World&) = delete;
        World& operator=(World&&) = delete;
        
        ~World()
        {
            removeAllSystems();
            removeAllEntities();
        }
        
        ////////////////////////////////////////////////////
        ////////////////////   SYSTEMS   ///////////////////
        ////////////////////////////////////////////////////
        
        template <typename SystemType>
        void addSystem(SystemType& system);
        
        template <typename SystemType>
        void removeSystem();
        
        template <typename SystemType>
        bool isSystemExisting() const;
        
        void addEntityToSystem(sgf::ISystem& sys, std::unique_ptr<sgf::Entity>& entity);
        
        void runSystems(sf::Time const& elapsed);
        
        void removeAllSystems();
        
        ////////////////////////////////////////////////////
        ///////////////////// ENTITIES  ////////////////////
        ////////////////////////////////////////////////////
        
    public:
        
        void registerEntity(std::unique_ptr<sgf::Entity>& entity); //will take the ownership of the entity
        std::size_t getEntityCount() const;
        
        
    private:
        
        void removeEntity(indexType const& ID);
        void removeAllEntities();
        void reactiveEntity(indexType const& ID);
        void unactiveEntity(indexType const& ID);
        bool isActivated(indexType const& ID) const;
        
        
    private:
        
        std::unordered_map<size_t, ISystem&> _systems; //size_t represent the hash of the type_index
        std::size_t _systemCount;
        
        std::unordered_map<indexType, std::unique_ptr<sgf::Entity> > _activeEntities;
        std::unordered_map<indexType, std::unique_ptr<sgf::Entity> > _inactiveEntities;
        std::size_t _entityCount;
        
        
    };
    
    template <typename SystemType>
    void sgf::World::addSystem(SystemType &system)
    {
        //créer un system du type spécifié (après avoir vérifié que le type dérive bien de sgf::System et qu'il n'y a pas déjà un system de ce type)
        static_assert(std::is_base_of<sgf::ISystem, SystemType>::value, "Trying to register a system that do not derive from sgf::ISystem");
        if(isSystemExisting<SystemType>()) throw sgf::Exception("System Type already registered");
        
        // l'ajouter à la liste de systems
        auto ret = _systems.insert({std::type_index(typeid(SystemType)).hash_code(), system});
        if (!ret.second) throw sgf::Exception("Cannot register system");
        
        ++_systemCount;
        
        
        
        //lui enregistrer les entités qui existent déjà dans le world et sur lequelles il a autorité
        for (auto it = _activeEntities.begin(); it != _activeEntities.end(); ++it)
        {
            addEntityToSystem(ret.first->second,it->second);
        }
        
        //plus clair ? (probleme de constness)
        //std::for_each(_activeEntities.begin(),_activeEntities.end(),std::bind(addEntityToSystem(ret.first->second,std::placeholders::_1)));
        
    }
    
    template <typename SystemType>
    void sgf::World::removeSystem()
    {
        // retirer le system de ce type
        if (!isSystemExisting<SystemType>()) throw sgf::Exception("System Type doesn't exist and cannot be erased");
        size_t index (std::type_index(typeid(SystemType)).hash_code());
        _systems.erase(_systems.find(index));
        --_systemCount;
    }
    
    template <typename SystemType>
    bool sgf::World::isSystemExisting() const
    {
        size_t index (std::type_index(typeid(SystemType)).hash_code());
        auto it = std::find_if(_systems.begin(),
                               _systems.end(),
                               [&index](const std::unordered_map<size_t, sgf::ISystem& >::value_type &elem) -> bool
                               { return elem.first == index;}
                               );
        if ( it != _systems.end())
        return true;
        
        else return false;
        
    }
    
    
    
    
}



#endif /* defined(__SGF__World__) */
