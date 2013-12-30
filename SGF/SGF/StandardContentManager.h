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

#include "ContentManager.h"

namespace sgf{

//////////////////////////////////////////////
///BASE LOADERS DEFINITIONS FOR SFML TYPES////
//////////////////////////////////////////////

class TextureLoader : public ILoader<sf::Texture>
{
public:
    
    typedef std::shared_ptr<sf::Texture> ptrTexture;
    
private:
    typedef std::shared_ptr<sf::Texture> returnType;
    
public:
    
    TextureLoader(std::string const& loaderName): ILoader<sf::Texture>(loaderName)
    {}
    ~TextureLoader()
    {
        UnloadAllRessources();
    }
    
    virtual void LoadRessource(KeyType const& key, std::string const& filename)
    {
        ptrTexture ressource (new sf::Texture);
        
        if(!ressource->loadFromFile(filename))
        {
            throw sgf::FileException(filename,"Unable to Load the Texture from the given filepath");
            return;
        }
        
        this->add(key, ressource);
    }
    
    virtual void UnloadRessource(KeyType const& UID)
    {
        return this->remove(UID);
    }
    
    virtual void UnloadAllRessources()
    {
        return this->removeAll();
    }
    
    virtual returnType getRessource(KeyType const& UID)
    {
        return this->get(UID);
    }
    
};

    class SoundLoader : public ILoader<std::pair<std::shared_ptr<sf::Sound>,std::shared_ptr<sf::SoundBuffer>>>
{
public:
    
    typedef std::shared_ptr<sf::Sound> ptrSound;
    
private:
    typedef std::shared_ptr<sf::SoundBuffer> ptrSoundBuffer;
    typedef std::pair<std::shared_ptr<sf::Sound>,std::shared_ptr<sf::SoundBuffer>> pairSound;
    typedef std::shared_ptr<sf::Sound> returnType;
    
public:

    
    SoundLoader(std::string const& loaderName): ILoader<std::pair<std::shared_ptr<sf::Sound>,std::shared_ptr<sf::SoundBuffer>>>(loaderName)
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
        
        this->add(key, std::make_shared<pairSound>(std::make_pair(sound, buffer)));
    }
    
    virtual void UnloadRessource(KeyType const& UID)
    {
        return this->remove(UID);
    }
    
    virtual void UnloadAllRessources()
    {
        return this->removeAll();
    }
    
    virtual returnType getRessource(KeyType const& UID)
    {
        return this->get(UID)->first;
    }
    
};
    
    class MusicLoader : public ILoader<sf::Music>
    {
    public:
        
        typedef std::shared_ptr<sf::Music> ptrMusic;
        
    private:
        typedef std::shared_ptr<sf::Music> returnType;
        
    public:
        
        MusicLoader(std::string const& loaderName): ILoader<sf::Music>(loaderName)
        {}
        ~MusicLoader()
        {
            UnloadAllRessources();
        }
        
        virtual void LoadRessource(KeyType const& key, std::string const& filename)
        {
            ptrMusic ressource (new sf::Music);
            
            if(!ressource->openFromFile(filename))
            {
                throw sgf::FileException(filename,"Unable to Load the Music from the given filepath");
                return;
            }
            
            this->add(key, ressource);
        }
        
        virtual void UnloadRessource(KeyType const& UID)
        {
            return this->remove(UID);
        }
        
        virtual void UnloadAllRessources()
        {
            return this->removeAll();
        }
        
        virtual returnType getRessource(KeyType const& UID)
        {
            return this->get(UID);
        }
        
    };
    
    class FontLoader : public ILoader<sf::Font>
    {
    public:
        
        typedef std::shared_ptr<sf::Font> ptrFont;
        
    private:
        typedef std::shared_ptr<sf::Font> returnType;
        
    public:
        
        FontLoader(std::string const& loaderName): ILoader<sf::Font>(loaderName)
        {}
        ~FontLoader()
        {
            UnloadAllRessources();
        }
        
        virtual void LoadRessource(KeyType const& key, std::string const& filename)
        {
            ptrFont ressource (new sf::Font);
            
            if(!ressource->loadFromFile(filename))
            {
                throw sgf::FileException(filename,"Unable to Load the Font from the given filepath");
                return;
            }
            
            this->add(key, ressource);
        }
        
        virtual void UnloadRessource(KeyType const& UID)
        {
            return this->remove(UID);
        }
        
        virtual void UnloadAllRessources()
        {
            return this->removeAll();
        }
        
        virtual returnType getRessource(KeyType const& UID)
        {
            return this->get(UID);
        }
        
    };
}

#endif
