//
//  MyGame.h
//  SGF
//
//  Created by DEPASSE Arthur on 03/01/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__MyGame__
#define __SGF__MyGame__

#include <thread>

#include "Game.h"
#include "IntroState.h"

class MyGame : public sgf::Game
{
    
public:
    
    MyGame(const std::string& title, int width, int height, unsigned int style = sf::Style::Default) : sgf::Game(title, width, height, style), textureMng("text_mng"), musicMng("music_mng"), soundMng("sound_mng"), musicLoading(nullptr)
    {
        mStateManager.PushState(sgf::Singleton<IntroState>::Instance<sgf::StateManager>(mStateManager));
    }
    
    virtual ~MyGame()
    {
    }
    
protected:
    
    virtual void init()
    {
        mStateManager.Init();
        
        
        sgf::TextureLoader::ptrTexture tex1;
        try
        {
            textureMng.LoadRessource("loading_screen", "loading.jpg");
            musicMng.LoadRessource("music", "Music.wav");
            
        }
        catch (std::exception const& e)
        {
            LOG(e.what());
        }
        
        try
        {
            tex1 = textureMng.getRessource("loading_screen");
            musicLoading = musicMng.getRessource("music");
            
        }
        catch (std::exception const& e)
        {
            LOG(e.what());
        }
        
        sf::Sprite sprite;
        sprite.setTexture(*tex1);
        mWindow.draw(sprite);
        musicLoading->play();
         
    }
    virtual void load()
    {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        musicLoading->stop();
    }
    virtual void unload()
    {
        textureMng.UnloadAllRessources();
        musicMng.UnloadAllRessources();
        
        mStateManager.Cleanup();
    }
    
    sgf::TextureLoader textureMng;
    sgf::MusicLoader musicMng;
    sgf::SoundLoader soundMng;
    
    sgf::MusicLoader::ptrMusic musicLoading;
    
    

};


#endif /* defined(__SGF__MyGame__) */
