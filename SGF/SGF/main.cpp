//
//  main.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 09/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//
const int width = 1920;
const int height = 1080;

#include <iostream>

#include "MyGame.h"



int main(int argc, const char * argv[])
{

    MyGame newGame("My New Game", width, height, sf::Style::Fullscreen);
    newGame.exec();
    
    
    return EXIT_SUCCESS;
}

