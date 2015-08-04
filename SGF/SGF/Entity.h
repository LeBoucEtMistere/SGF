//
//  Entity.h
//  SGF
//
//  Created by DEPASSE Arthur on 28/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__Entity__
#define __SGF__Entity__

#include <unordered_map>
#include "Component.h"
#include "Exception.h"
#include <algorithm>
#include <typeindex>

namespace sgf
{
    class Entity
    {
    public:
        
        Entity(unsigned int ID);
        ~Entity() = default;
        
        Entity(Entity const& rhs)=delete;
        Entity operator=(Entity const& rhs)=delete;
        
        //move assignable
        Entity(Entity&& rhs): _id(rhs._id)
        {}

        
        unsigned int const& getId() const { return _id; }
        
        
        ////////////////////////////////////////////////////
        //////////////////// COMPONENTS  ///////////////////
        ////////////////////////////////////////////////////

        ///// HAS /////

        template <class ComponentType>
        bool hasComponentType();
        
        bool hasComponentType(std::type_index const& type);
        
        template <class ComponentType>
        bool hasComponent(std::string const& ID);
        
        ///// ADD //////
        
        template<class T, class ... Args>
        void addComponent(std::string const& ID, Args&& ... args);
        
        ///// GET /////
        
        template<class T>
        T & getComponent(std::string const& ID) const;
        
        ///// SET /////
        
        template<class T, class ... Args>
        void setComponent(std::string const& ID, Args&& ... args);
        
        
        
        void inactiveComponent(std::string const& ID);
        
        void reactiveComponent(std::string const& ID);
        
        void deleteComponent(std::string const& ID);
        
        
        ////////////////////////////////////////////////////
        ////////////////////   SYSTEMS   ///////////////////
        ////////////////////////////////////////////////////
        
        
    private:
        
        const unsigned int _id;
        using MapType = std::unordered_multimap<std::type_index, std::unique_ptr<sgf::IComponent> >;
        MapType _activeComponents;
        MapType _inactiveComponents;
        

    };
    
    ///// HAS /////
    
    template <class ComponentType>
    bool sgf::Entity::hasComponentType()
    {
        std::type_index index (typeid(ComponentType));
        return hasComponentType(index);
    }
    
    template <class ComponentType>
    bool sgf::Entity::hasComponent(std::string const& ID)
    {
        std::type_index index (typeid(ComponentType));
        auto it = std::find_if(_activeComponents.begin(),
                               _activeComponents.end(),
                               [& ID, &index](const MapType::value_type &elem) -> bool
                               { return elem.second->getId() == ID && elem.first == index;}
                               );
        if ( it != _activeComponents.end())
        {
            return true;
        }
        
        auto it2 = std::find_if(_inactiveComponents.begin(),
                                _inactiveComponents.end(),
                                [& ID, &index](const MapType::value_type &elem) -> bool
                                { return elem.second->getId() == ID && elem.first == index;}
                                );
        if ( it2 != _inactiveComponents.end())
        {
            return true;
        }
        
        else return false;
    }
    
    
    ///// ADD //////
    
    template<class T, class ... Args>
    void sgf::Entity::addComponent(std::string const& ID, Args&& ... args)
    {
        _activeComponents.emplace( std::make_pair( std::type_index(typeid(T)), std::unique_ptr<sgf::IComponent>( new T(ID,args...))  ) );
    }
    
    
    ///// GET /////
    
    template <class T>
    T & sgf::Entity::getComponent(std::string const& ID) const
    {
        std::type_index index (typeid(T));
        auto it = std::find_if(_activeComponents.begin(),
                               _activeComponents.end(),
                               [& index, & ID](const MapType::value_type &elem) -> bool
                               { return elem.first == index && elem.second->getId() == ID;}
                               );
        if ( it != _activeComponents.end())
        return *static_cast<T*>(it->second.get());
        else throw sgf::Exception("excp");
    }
    
    ///// SET //////
    
    template<class T, class ... Args>
    void sgf::Entity::setComponent(std::string const& ID, Args&& ... args)
    {
        if (!hasComponent<T>(ID))
            throw sgf::Exception("excp");
        
        std::type_index index (typeid(T));
        auto it = std::find_if(_activeComponents.begin(),
                               _activeComponents.end(),
                               [& index, & ID](const MapType::value_type &elem) -> bool
                               { return elem.first == index && elem.second->getId() == ID;}
                               );
        it->second.reset(new T(ID,args...));
    }
    

}

#endif /* defined(__SGF__Entity__) */
