//
//  IntroState.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 04/01/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#include "IntroState.h"
#include "Utils.h"

IntroState::IntroState(sgf::StateManager& stateMng, int width, int height, sf::RenderWindow &window): sgf::IState(stateMng), _texLoader("TextureLoader_IntroState"), _spriteLoader("SpriteLoader_IntroState"), _musicLoader("MusicLoader_IntroState"), music(nullptr), jouer(), quitter(), reglages(), world(), _width(width), _height(height), _window(window), _systems()
{


}

void IntroState::Init()
{
    _musicLoader.LoadRessource("music_intro" , "media/music/theme_intro.ogg");
    music = &_musicLoader.getRessource("music_intro" );
    
    _texLoader.LoadRessource("gui_button_jouer_idle" , "media/gui/jouer_idle.png");
    _texLoader.LoadRessource("gui_button_jouer_clicked" , "media/gui/jouer_clicked.png");
    _texLoader.LoadRessource("gui_button_jouer_disabled" , "media/gui/jouer_disabled.png");

    _texLoader.LoadRessource("gui_button_reglages_idle" , "media/gui/reglages_idle.png");
    _texLoader.LoadRessource("gui_button_reglages_clicked" , "media/gui/reglages_clicked.png");
    _texLoader.LoadRessource("gui_button_reglages_disabled" , "media/gui/reglages_disabled.png");

    _texLoader.LoadRessource("gui_button_quitter_idle" , "media/gui/quitter_idle.png");
    _texLoader.LoadRessource("gui_button_quitter_clicked" , "media/gui/quitter_clicked.png");
    _texLoader.LoadRessource("gui_button_quitter_disabled" , "media/gui/quitter_disabled.png");

    _texLoader.LoadRessource("gui_title" , "media/gui/IntroState.png");
    
    _texLoader.LoadRessource("bckg_image" , "media/img/intro_bckgd.jpg");
    
    _spriteLoader.LoadRessource("gui_button_jouer_idle" , _texLoader.getRessource("gui_button_jouer_idle" ));
    _spriteLoader.LoadRessource("gui_button_jouer_clicked" , _texLoader.getRessource("gui_button_jouer_clicked" ));
    _spriteLoader.LoadRessource("gui_button_jouer_disabled" , _texLoader.getRessource("gui_button_jouer_disabled" ));
    
    _spriteLoader.LoadRessource("gui_button_quitter_idle" , _texLoader.getRessource("gui_button_quitter_idle" ));
    _spriteLoader.LoadRessource("gui_button_quitter_clicked" , _texLoader.getRessource("gui_button_quitter_clicked" ));
    _spriteLoader.LoadRessource("gui_button_quitter_disabled" , _texLoader.getRessource("gui_button_quitter_disabled" ));
    
    _spriteLoader.LoadRessource("gui_button_reglages_idle" , _texLoader.getRessource("gui_button_reglages_idle" ));
    _spriteLoader.LoadRessource("gui_button_reglages_clicked" , _texLoader.getRessource("gui_button_reglages_clicked" ));
    _spriteLoader.LoadRessource("gui_button_reglages_disabled" , _texLoader.getRessource("gui_button_reglages_disabled" ));
    
    _spriteLoader.LoadRessource("gui_title" , _texLoader.getRessource("gui_title" ));
    
    _spriteLoader.LoadRessource("bckg_image" , _texLoader.getRessource("bckg_image" ));

    auto size_button_jouer = (_texLoader.getRessource("gui_button_jouer_idle" )).getSize();
    auto size_button_reglages = (_texLoader.getRessource("gui_button_reglages_idle" )).getSize();
    auto size_button_quitter = (_texLoader.getRessource("gui_button_quitter_idle" )).getSize();
    auto size_title = (_texLoader.getRessource("gui_title" )).getSize();
    
    _spriteLoader.getRessource("gui_title" ).setPosition((_width/2)-(size_title.x/2), (_height/7));
    
    jouer.setDimension(0, 0, size_button_jouer.x, size_button_jouer.y);
    jouer.setId("jouer");
    jouer.setIdleSprite(_spriteLoader.getRessource("gui_button_jouer_idle" ));
    jouer.setDisabledSprite(_spriteLoader.getRessource("gui_button_jouer_disabled" ));
    jouer.setClickedSprite(_spriteLoader.getRessource("gui_button_jouer_clicked" ));
    jouer.centerAt(_width/2, (_height/7)*3);
    
    reglages.setDimension(0, 0, size_button_reglages.x, size_button_reglages.y);
    reglages.setId("reglages");
    reglages.setIdleSprite(_spriteLoader.getRessource("gui_button_reglages_idle" ));
    reglages.setDisabledSprite(_spriteLoader.getRessource("gui_button_reglages_disabled" ));
    reglages.setClickedSprite(_spriteLoader.getRessource("gui_button_reglages_clicked" ));
    reglages.centerAt(_width/2, (_height/7)*4);
    
    reglages.setCurrentState(sgf::gui::ButtonState::Disabled);
    
    quitter.setDimension(0, 0, size_button_quitter.x, size_button_quitter.y);
    quitter.setId("quitter");
    quitter.setIdleSprite(_spriteLoader.getRessource("gui_button_quitter_idle" ));
    quitter.setDisabledSprite(_spriteLoader.getRessource("gui_button_quitter_disabled" ));
    quitter.setClickedSprite(_spriteLoader.getRessource("gui_button_quitter_clicked" ));
    quitter.centerAt(_width/2, (_height/7)*5);
    
    
    /*
    for (unsigned int i = 0; i < 10; ++i)
    {
        std::unique_ptr<sgf::Entity> entity(new sgf::Entity(i));
        entity->addComponent<PositionComponent>("pos", i, 3.0*i);

        auto data = entity->getComponent<PositionComponent>("pos").getData();
        std::string str ("entity n" + std::to_string(i) + " : x=" + std::to_string(data.x) + " y=" + std::to_string(data.y));
        LOG(str.c_str());

        
        entity->addComponent<PositionComponent>("position", i,i);
        entity->inactiveComponent("position");
        entity->reactiveComponent("position");
        entity->deleteComponent("position");
        
        world.registerEntity(entity);
    }*/
    
    std::unique_ptr<sgf::Entity> entity(sgf::make_unique<sgf::Entity>(12));
    entity->addComponent<PositionComponent>("pos", 200,200);
    auto circle=sf::CircleShape(150);
    circle.setPosition(200, 200);
    circle.setFillColor(sf::Color::Red);
    entity->addComponent<CircleShapeComponent>("graph", circle);
    
    world.registerEntity(entity);
    
    auto render=sgf::make_unique<RenderSystem>(world,_window);
    world.addSystem(*render);
    auto mov=sgf::make_unique<MovementSystem>(world);
    world.addSystem(*mov);
    
    _systems.push_back(std::move(render));
    _systems.push_back(std::move(mov));

    
    music->play();
    
}
void IntroState::Cleanup()
{
    _texLoader.UnloadAllRessources();
    world.removeAllSystems();
    music->stop();
}

void IntroState::Pause()
{
    
}
void IntroState::Resume()
{
    
}


void IntroState::HandleEvents(sgf::Game *,sf::RenderWindow& window, sf::Event const& evt)
{
    switch (evt.type) {
        case sf::Event::Closed:
            window.close();
        break;
            
        case sf::Event::KeyPressed:
            switch (evt.key.code)
            {
                case sf::Keyboard::Return:
                    ReplaceState(std::unique_ptr<GameState>(new GameState(_stateMng)));
                break;
                case sf::Keyboard::Escape:
                    window.close();
                break;
                default:
                break;
            }
        break;
        case sf::Event::MouseButtonPressed:

            if (jouer.collideWith(evt.mouseButton.x, evt.mouseButton.y) && jouer.getCurrentState() == sgf::gui::ButtonState::Idle)
            {
                jouer.setCurrentState(sgf::gui::ButtonState::Clicked);
            }
            else if (quitter.collideWith(evt.mouseButton.x, evt.mouseButton.y) && quitter.getCurrentState() == sgf::gui::ButtonState::Idle)
            {
                quitter.setCurrentState(sgf::gui::ButtonState::Clicked);
            }
            break;
        case sf::Event::MouseButtonReleased:
            if (jouer.collideWith(evt.mouseButton.x, evt.mouseButton.y) && jouer.getCurrentState() == sgf::gui::ButtonState::Clicked)
            {
                jouer.setCurrentState(sgf::gui::ButtonState::Idle);
                ReplaceState(std::unique_ptr<GameState>(new GameState(_stateMng)));
            }
            else if (quitter.collideWith(evt.mouseButton.x, evt.mouseButton.y) && quitter.getCurrentState() == sgf::gui::ButtonState::Clicked)
            {
                quitter.setCurrentState(sgf::gui::ButtonState::Idle);
                window.close();
            }
            break;

        default:
        break;
    }

}
void IntroState::Update(sgf::Game* game, sf::Time const& elapsed)
{
    world.runSystems(std::forward<sf::Time const&>(elapsed));
}
void IntroState::Draw(sgf::Game *,sf::RenderWindow& window)
{
    //window.draw(_spriteLoader.getRessource("bckg_image" ));
    window.draw(jouer.getCurrentSprite());
    window.draw(reglages.getCurrentSprite());
    window.draw(quitter.getCurrentSprite());
    window.draw(_spriteLoader.getRessource("gui_title" ));
  
}


