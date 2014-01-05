//
//  main.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 09/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#include <iostream>



#include "MyGame.h"

int main(int argc, const char * argv[])
{

    MyGame newGame("My New Game", 450, 480);
    newGame.exec();
    
    return EXIT_SUCCESS;
}

