//
//  StateManager.h
//  SGF
//
//  Created by DEPASSE Arthur on 28/12/2013.
//  Copyright (c) 2013 DEPASSE Arthur. All rights reserved.
//

#ifndef __SGF__StateManager__
#define __SGF__StateManager__

#include <list>
#include <algorithm>
#include "Exception.h"
#include "State.h"

namespace sgf
{
    
    class StateManager
    {
    public:
        StateManager();
        virtual ~StateManager();
    
        virtual void Init();
        virtual void Cleanup();
    
        void PushState(sgf::State::StatePtr state);
        void PopState();
    
        void HandleEvents(sgf::Game* game);
        void Update(sgf::Game* game);
        void Draw(sgf::Game* game);
    
    private:
        StateManager(StateManager const&);
        void operator=(StateManager const&);
    
        std::list<sgf::State::StatePtr> m_states;
    
        bool m_running;
        sgf::State::StatePtr m_currentState;
    
    };
    
    

}



#endif /* defined(__SGF__StateManager__) */
