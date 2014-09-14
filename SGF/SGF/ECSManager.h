//
//  ECSManager.h
//  SGF
//
//  Created by DEPASSE Arthur on 25/03/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__ECSManager__
#define __SGF__ECSManager__

#include "Entity.h"
#include "System.h"
#include <unordered_map>

namespace sgf
{
    class ECSManager
    {
    public:
        
        typedef unsigned int indexType ;
        
        ECSManager();
        
        ECSManager(const ECSManager& rhs) = delete;
        ECSManager(ECSManager&& rhs) = delete;
        ECSManager& operator=(const ECSManager&) = delete;
        ECSManager& operator=(ECSManager&&) = delete;
        
        template <typename ...ComponentTypes>
        void addSystem();
        
        template <typename ...ComponentTypes>
        void removeSystem();
        bool isSystemTypeExisting() const;
        bool isSystemExisting() const;
        void removeAllSystems();
         
        
        sgf::Entity&& addEntity();
        void removeEntity(sgf::Entity& entity);
        sgf::Entity&& getEntity(indexType index);
        void removeAllEntities();
        void reactiveEntity(sgf::Entity& entity);
        void unactiveEntity(sgf::Entity& entity);
        bool isActivated(sgf::Entity& entity) const;
        
        void clear();
        std::size_t getEntityCount() const;
        
        
    private:
        
        std::unordered_map<indexType, std::unique_ptr<sgf::ISystem> > _systems;
        std::size_t _systemCount;
        
        std::unordered_map<indexType, std::unique_ptr<sgf::Entity> > _activeEntities;
        std::unordered_map<indexType, std::unique_ptr<sgf::Entity> > _inactiveEntities;
        std::size_t _entityCount;
        
        
    };
}

#endif /* defined(__SGF__ECSManager__) */
