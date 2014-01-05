//
//  State.h
//  SGF
//
//  Created by DEPASSE Arthur on 28/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__State__
#define __SGF__State__

#include <iostream>

#include "Dispatcher.h"
#include "System.h"
#include "Entity.h"

#include "Singleton.h"

namespace sgf
{
    
    class Game;
    class StateManager;

    class State
    {
    public:
        
        virtual ~State(){}
        
        typedef std::shared_ptr<sgf::State> StatePtr;
        
        friend class sgf::Singleton<State>;
    
        virtual void Init() = 0;
        virtual void Cleanup() = 0;
    
        virtual void Pause() = 0;
        virtual void Resume() = 0;
    
        virtual void HandleEvents(sgf::Game *) = 0;
        virtual void Update(sgf::Game *) = 0;
        virtual void Draw(sgf::Game *) = 0;
    
    protected:
        
        State(StateManager& stateMng): mStateMng(stateMng){}
        State(const State& rhs): mStateMng(rhs.mStateMng){}
        void operator=(const State& rhs){}

        
        void ChangeState(StatePtr state);  // DEFINED IN STATEMANAGER.CPP //
        StateManager& mStateMng;

    
    };
}

#endif /* defined(__SGF__State__) */
