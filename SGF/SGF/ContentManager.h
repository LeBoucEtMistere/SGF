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


#include <map>
#include <utility>
#include <string>






namespace sgf {
    
    // LOADER INTERFACE //
    
    template <class T>
    class ILoader
    {
        
    public :

        typedef std::shared_ptr<T> ptrT;
        using KeyType = std::string;
        using MapType = std::map<KeyType , ptrT>;
        
        ILoader(std::string const& loaderName) : mLoaderName(loaderName)
        {}
        
        virtual ~ILoader() = 0;
        
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
        
        ptrT get(KeyType const& UID)
        {
            if(mRessources.find(UID) != mRessources.end())
            {
                return mRessources[UID];
            }
            throw sgf::LoaderException(mLoaderName,UID,"Trying to get a non-initialized ressource",sgf::ExceptionLevel::WARNING);
            return nullptr;
        }
        
        void add(KeyType const& key, ptrT ptr)
        {
            
            if(true)//la ressource est déjà dans la map  /// TODO ///
            {
                if (!mRessources.emplace(std::make_pair(key, ptr)).second)
                    throw sgf::LoaderException(mLoaderName,key,"Cannot emplace the given Ressource",sgf::ExceptionLevel::WARNING);
            }
            else throw sgf::LoaderException(mLoaderName,key,"The given ressource is already present in the loader",sgf::ExceptionLevel::WARNING);

        }
        
        void remove(KeyType const& UID)
        {
            if(mRessources.find(UID) != mRessources.end())
            {
                mRessources.erase(UID);
            }
            else
            {
                throw sgf::LoaderException(mLoaderName,UID,"Trying to delete a non-initialized ressource",sgf::ExceptionLevel::WARNING);
            }
        }
        
        void removeAll()
        {
            mRessources.clear();

        }
        
        static MapType mRessources;
        std::string mLoaderName;
        
    };
    template <class T>
    inline ILoader<T>::~ILoader<T>() { }
    
    template <class T>
    typename ILoader<T>::MapType ILoader<T>::mRessources ;
    
}

#endif /* defined(__SGF__ContentManager__) */



