//
//  IntroState.h
//  SGF
//
//  Created by DEPASSE Arthur on 04/01/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__IntroState__
#define __SGF__IntroState__

#include "State.h"

class IntroState: public sgf::State
{
public:
    
    friend class sgf::Singleton<IntroState>;
    
    virtual ~IntroState(){}
    
    virtual void Init();
    virtual void Cleanup();
    
    virtual void Pause();
    virtual void Resume();
    
    virtual void HandleEvents(sgf::Game *);
    virtual void Update(sgf::Game *);
    virtual void Draw(sgf::Game *);
    
protected:
    
    IntroState(sgf::StateManager& stateMng): sgf::State(stateMng){}
    IntroState(const IntroState& rhs): sgf::State(rhs){}
    void operator=(const IntroState& rhs){}
    
};

#endif /* defined(__SGF__IntroState__) */
