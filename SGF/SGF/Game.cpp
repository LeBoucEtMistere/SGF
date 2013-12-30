//
//  Game.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 09/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#include "Game.h"


sgf::Game::Game(const std::string& title, int width, int height, unsigned int style) : mWindow(sf::VideoMode(width,height),title, style), mTextureLoader("texture_loader_1"), mSoundLoader("sound_loader_1"), mMusicLoader("music_loader_1"), mFontLoader("font_loader_1")
{
}

sgf::Game::~Game()
{}

// MAIN METHOD //

void sgf::Game::exec()
{
    

    try
    {
        mTextureLoader.LoadRessource("mouton", "/Users/depassearthur/SGF/SGF/DerivedData/SGF/Build/Products/Debug/mouton_punk.jpg");
        mSoundLoader.LoadRessource("explosion", "/Users/depassearthur/SGF/SGF/DerivedData/SGF/Build/Products/Debug/Sound.aif");
        mMusicLoader.LoadRessource("music", "/Users/depassearthur/SGF/SGF/DerivedData/SGF/Build/Products/Debug/Music.wav");
        mFontLoader.LoadRessource("bombing", "/Users/depassearthur/SGF/SGF/DerivedData/SGF/Build/Products/Debug/Font.ttf");
        
    }
    catch (std::exception const& e)
    {
        ERR(e.what())

    }
    
    sgf::TextureLoader::ptrTexture tex;
    sgf::SoundLoader::ptrSound sound;
    sgf::MusicLoader::ptrMusic music;
    sgf::FontLoader::ptrFont font;
    
    try
    {
        tex = mTextureLoader.getRessource("mouton");
        sound = mSoundLoader.getRessource("explosion");
        music = mMusicLoader.getRessource("music");
        font = mFontLoader.getRessource("bombing");
        
    }
    catch (std::exception const& e)
    {
        ERR(e.what())

    }
    
    tex->setSmooth(true);
    sf::Sprite sprite;
    sprite.setTexture(*tex);
    
    music->play();
    
    sf::Text text;

    text.setFont(*font);
    text.setString("New Game");
    text.setCharacterSize(48);
    text.setColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);
    text.setPosition(450/2, 480/2);

    while (mWindow.isOpen())
    {
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    mWindow.close();
                    break;
                    
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Key::Escape)
                        mWindow.close();
                    break;
                    
                default:
                    break;
            }
        }
        
        mWindow.clear(sf::Color::Black);
        
        mWindow.draw(sprite);
        mWindow.draw(text);
        
        mWindow.display();

        
        
    }
    
    music->stop();

    sound->play();
    std::chrono::nanoseconds timer(sound->getBuffer()->getDuration().asMicroseconds()*1000);
    std::this_thread::sleep_for(timer);




}



