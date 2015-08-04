//
//  Component.h
//  SGF
//
//  Created by DEPASSE Arthur on 28/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__Component__
#define __SGF__Component__

#include <string>

namespace sgf
{
    
    class IComponent
    {
    public:
        
        IComponent(std::string const& ID) : _id(ID)
        {}
        
        IComponent(IComponent&& rhs) : _id(rhs._id)
        {}
        
        virtual ~IComponent() = default;

        IComponent (IComponent const& rhs) = default;
        IComponent& operator=(IComponent const& rhs) = default;
        

        std::string const& getId() const { return _id; }
   
    protected:
        
        std::string _id;
        
    };
    
    template <class DataType>
    struct Component : public sgf::IComponent
    {
    
        template<class ... Args>
        Component(std::string const& ID, Args&&... args) : sgf::IComponent(ID), _data(std::forward<Args>(args)...)
        {}
        
        virtual ~Component() = default;
        Component (Component const& rhs) = default;
        Component& operator=(Component const& rhs) = default;
        /*
        DataType const& getData()const
        {
            return _data;
        }
        template <class ... Args>
        void setData(Args&& ...args)
        {
            _data = DataType(std::forward<Args>(args)...);
        }*/
        
    
        
        DataType _data;
    };
}

#endif /* defined(__SGF__Component__) */
