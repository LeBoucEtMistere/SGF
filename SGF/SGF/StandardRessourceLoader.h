//
//  StandardContentManager.h
//  SGF
//
//  Created by DEPASSE Arthur on 30/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#ifndef SGF_StandardContentManager_h
#define SGF_StandardContentManager_h

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "RessourceLoader.h"

namespace sgf{

//////////////////////////////////////////////
///BASE LOADERS DEFINITIONS FOR SFML TYPES////
//////////////////////////////////////////////

    class TextureLoader : public IRessourceLoader<sf::Texture>
    {
    
    public:
    
        TextureLoader(std::string const& loaderName): IRessourceLoader<sf::Texture>(loaderName)
        {}
        ~TextureLoader()
        {
            UnloadAllRessources();
        }
    
        virtual void LoadRessource(KeyType const& key, std::string const& filename)
        {
            ptrT ressource(new sf::Texture);
        
            if(!ressource->loadFromFile(filename))
            {
                throw sgf::FileException(filename,"Unable to Load the Texture from the given filepath");
                return;
            }
        
            add(key, std::move(ressource));
        }
    
        virtual void UnloadRessource(KeyType const& UID)
        {
            return remove(UID);
        }
    
        virtual void UnloadAllRessources()
        {
            return removeAll();
        }
    
        virtual refT getRessource(KeyType const& UID)
        {
            return get(UID);
        }
    
    };
    
    class SpriteLoader : public IRessourceLoader<sf::Sprite>
    {

    public:
    
        SpriteLoader(std::string const& loaderName): IRessourceLoader<sf::Sprite>(loaderName)
        {}
        ~SpriteLoader()
        {
            UnloadAllRessources();
        }
    
        virtual void LoadRessource(KeyType const& key, sf::Texture& tex)
        {
            ptrT ressource (new sf::Sprite);
            
            ressource->setTexture(tex);
        
            add(key, std::move(ressource));
        }
    
        virtual void UnloadRessource(KeyType const& UID)
        {
            return remove(UID);
        }
    
        virtual void UnloadAllRessources()
        {
            return removeAll();
        }
    
        virtual refT getRessource(KeyType const& UID)
        {
            return get(UID);
        }
        
    };

    class SoundLoader : public IRessourceLoader<std::pair<std::unique_ptr<sf::Sound>,std::unique_ptr<sf::SoundBuffer>>>
    {
    
    private:
        typedef std::unique_ptr<sf::SoundBuffer> ptrSoundBuffer;
        typedef std::unique_ptr<std::pair<std::unique_ptr<sf::Sound>,std::unique_ptr<sf::SoundBuffer>>> ptrPair;
        typedef std::unique_ptr<sf::Sound> ptrSound;
    
    public:
    
        SoundLoader(std::string const& loaderName): IRessourceLoader<std::pair<std::unique_ptr<sf::Sound>,std::unique_ptr<sf::SoundBuffer>>>(loaderName)
        {}
        ~SoundLoader()
        {
            UnloadAllRessources();
        }
    
        virtual void LoadRessource(KeyType const& key, std::string const& filename)
        {
            ptrSound sound (new sf::Sound);
            ptrSoundBuffer buffer(new sf::SoundBuffer);
        
            if(!buffer->loadFromFile(filename))
            {
                throw sgf::FileException(filename,"Unable to Load the SoundBuffer from the given filepath");
                return;
            }
            sound->setBuffer(*buffer);
        
            ptrPair pair(new std::pair<std::unique_ptr<sf::Sound>,std::unique_ptr<sf::SoundBuffer>>(std::move(sound), std::move(buffer)));
        
            add(key, std::move(pair));
        
        }
    
        virtual void UnloadRessource(KeyType const& UID)
        {
            return this->remove(UID);
        }
    
        virtual void UnloadAllRessources()
        {
            return this->removeAll();
        }
    
        virtual sf::Sound& getRessource(KeyType const& UID)
        {
            return *(get(UID).first);
        }
    
    };
    
    class MusicLoader : public IRessourceLoader<sf::Music>
    {
        
    public:
        
        MusicLoader(std::string const& loaderName): IRessourceLoader<sf::Music>(loaderName)
        {}
        ~MusicLoader()
        {
            UnloadAllRessources();
        }
        
        virtual void LoadRessource(KeyType const& key, std::string const& filename)
        {
            ptrT ressource (new sf::Music);
            
            if(!ressource->openFromFile(filename))
            {
                throw sgf::FileException(filename,"Unable to Load the Music from the given filepath");
                return;
            }
            
            add(key, std::move(ressource));
        }
        
        virtual void UnloadRessource(KeyType const& UID)
        {
            return remove(UID);
        }
        
        virtual void UnloadAllRessources()
        {
            return removeAll();
        }
        
        virtual refT getRessource(KeyType const& UID)
        {
            return get(UID);
        }
        
    };
    
    class FontLoader : public IRessourceLoader<sf::Font>
    {
        
    public:
        
        FontLoader(std::string const& loaderName): IRessourceLoader<sf::Font>(loaderName)
        {}
        ~FontLoader()
        {
            UnloadAllRessources();
        }
        
        virtual void LoadRessource(KeyType const& key, std::string const& filename)
        {
            ptrT ressource (new sf::Font);
            
            if(!ressource->loadFromFile(filename))
            {
                throw sgf::FileException(filename,"Unable to Load the Font from the given filepath");
                return;
            }
            
            add(key, std::move(ressource));
        }
        
        virtual void UnloadRessource(KeyType const& UID)
        {
            return this->remove(UID);
        }
        
        virtual void UnloadAllRessources()
        {
            return this->removeAll();
        }
        
        virtual refT getRessource(KeyType const& UID)
        {
            return get(UID);
        }
        
    };
}

#endif
