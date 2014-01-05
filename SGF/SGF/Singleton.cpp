//
//  Singleton.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 05/01/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#include "Singleton.h"

template<class T>
std::shared_ptr<T> sgf::Singleton<T>::mInstance = std::shared_ptr<T>(nullptr);
