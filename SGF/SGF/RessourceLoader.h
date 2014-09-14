//
//  ContentManager.h
//  SGF
//
//  Created by DEPASSE Arthur on 09/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__ContentManager__
#define __SGF__ContentManager__

#include "Logger.h"
#include "Exception.h"
#include "Hash.h"


#include <unordered_map>
#include <utility>
#include <string>






namespace sgf {
    
    // LOADER INTERFACE //
    
    template <class T>
    class IRessourceLoader
    {
        
    public :

        typedef std::unique_ptr<T> ptrT;
        typedef T& refT;
        using KeyType = std::string;
        using HashType = uint64_t;
        using MapType = std::unordered_map<HashType , ptrT>;
        
        IRessourceLoader(std::string const& loaderName) : _loaderName(loaderName)
        {}
        
        virtual ~IRessourceLoader() = 0;
        
        virtual void LoadRessource(KeyType const& key, std::string const& filename)
        {
            throw sgf::FileException(filename, "Unspecified Loader");
        }
        
        virtual void UnloadRessource(KeyType const& UID)
        {
            throw sgf::FileException(UID, "Unspecified Unloader");
        }
        
        virtual void UnloadAllRessources()
        {
            throw sgf::FileException("the whole map", "Unspecified global unloader");
        }
        
        virtual ptrT GetRessource(KeyType const& UID)
        {
            throw sgf::FileException(UID ,"Unspecified getter");

        }
        
        
    protected:
        
        refT get(KeyType const& UID)
        {
            HashType hash = Hash(UID.c_str(), UID.size());
            
            if(_ressources.find(hash) != _ressources.end())
            {
                return *(_ressources[hash]);
            }
            throw sgf::LoaderException(_loaderName,UID,"Trying to get a non-initialized ressource",sgf::ExceptionLevel::WARNING);
            
        }
        
        void add(KeyType const& key, ptrT&& ptr)
        {
            HashType hash = Hash(key.c_str(), key.size());

            if(_ressources.find(hash) == _ressources.end())
            {
                if (!_ressources.emplace(std::make_pair(hash, ptrT(std::move(ptr)))).second)
                    throw sgf::LoaderException(_loaderName,key,"Cannot emplace the given Ressource",sgf::ExceptionLevel::WARNING);
            }
            else throw sgf::LoaderException(_loaderName,key,"The given ressource is already present in the loader",sgf::ExceptionLevel::WARNING);

        }
        
        void remove(KeyType const& UID)
        {
            HashType hash = Hash(UID.c_str(), UID.size());

            if(_ressources.find(hash) != _ressources.end())
            {
                _ressources.erase(hash);
            }
            else
            {
                throw sgf::LoaderException(_loaderName,UID,"Trying to delete a non-initialized ressource",sgf::ExceptionLevel::WARNING);
            }
        }
        
        void removeAll()
        {
            _ressources.clear();

        }
        
        static MapType _ressources;
        std::string _loaderName;
        
    };
    template <class T>
    inline IRessourceLoader<T>::~IRessourceLoader<T>() { }
    
    template <class T>
    typename IRessourceLoader<T>::MapType IRessourceLoader<T>::_ressources ;
    
}

#endif /* defined(__SGF__ContentManager__) */



