//
//  ECSWorld.h
//  SGF
//
//  Created by DEPASSE Arthur on 14/07/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__ECSWorld__
#define __SGF__ECSWorld__

#include "Entity.h"
#include "System.h"
#include <unordered_map>
#include <typeindex>

namespace sgf
{
    class ISystem;
    class ECSIWorld;
    
    class ECSWorld
    {
    public:
        
        friend class ISystem;
        friend class ECSIWorld;
        
        typedef unsigned int indexType ;
        
        ECSWorld();
        
        ECSWorld(const ECSWorld& rhs) = delete;
        ECSWorld(ECSWorld&& rhs) = delete;
        ECSWorld& operator=(const ECSWorld&) = delete;
        ECSWorld& operator=(ECSWorld&&) = delete;
        
        ~ECSWorld()
        {
            removeAllSystems();
            removeAllEntities();
        }
        
        ////////////////////////////////////////////////////
        ////////////////////   SYSTEMS   ///////////////////
        ////////////////////////////////////////////////////
        
        template <typename SystemType>
        void addSystem();
        
        template <typename SystemType>
        void removeSystem();
        
        template <typename SystemType>
        bool isSystemExisting() const;
        
        void runSystems();
        
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
        
        std::unordered_map<size_t, std::unique_ptr<sgf::ISystem> > _systems; //size_t represent the hash of the type_index
        std::size_t _systemCount;
        
        std::unordered_map<indexType, std::unique_ptr<sgf::Entity> > _activeEntities;
        std::unordered_map<indexType, std::unique_ptr<sgf::Entity> > _inactiveEntities;
        std::size_t _entityCount;
        
        
    };
    
    template <typename SystemType>
    void sgf::ECSWorld::addSystem()
    {
        //créer un system du type spécifié (après avoir vérifié que le type dérive bien de sgf::System et qu'il n'y a pas déjà un system de ce type)
        static_assert(std::is_base_of<sgf::ISystem, SystemType>::value, "Trying to register a system that do not derive from sgf::ISystem");
        if(isSystemExisting<SystemType>()) throw sgf::Exception("excp");

        // l'ajouter à la liste de systems
        _systems.emplace(std::make_pair(std::type_index(typeid(SystemType)).hash_code(), std::unique_ptr<sgf::ISystem>(new SystemType(*this)) ));
        ++_systemCount;
    }
    
    template <typename SystemType>
    void sgf::ECSWorld::removeSystem()
    {
        // retirer le system de ce type
        if (!isSystemExisting<SystemType>()) throw sgf::Exception("excp");
        size_t index (std::type_index(typeid(SystemType)).hash_code());
        _systems.erase(_systems.find(index));
        --_systemCount;
    }
    
    template <typename SystemType>
    bool sgf::ECSWorld::isSystemExisting() const
    {
        size_t index (std::type_index(typeid(SystemType)).hash_code());
        auto it = std::find_if(_systems.begin(),
                               _systems.end(),
                               [&index](const std::unordered_map<size_t, std::unique_ptr<sgf::ISystem> >::value_type &elem) -> bool
                               { return elem.first == index;}
                               );
        if ( it != _systems.end())
        {
            return true;
        }
        else return false;

    }
    

    

}



#endif /* defined(__SGF__ECSWorld__) */
