//
//  State.cpp
//  SGF
//
//  Created by DEPASSE Arthur on 25/07/2014.
//  Copyright (c) 2014 DEPASSE Arthur. All rights reserved.
//

#include "State.h"
#include "StateManager.h"

void sgf::IState::PushState(std::unique_ptr<sgf::IState>&& state)
{
    _stateMng.PushState(std::forward<std::unique_ptr<sgf::IState>&&>(state));
}
void sgf::IState::ReplaceState(std::unique_ptr<sgf::IState>&& state)
{
    _stateMng.PopAndPush(std::forward<std::unique_ptr<sgf::IState>&&>(state));
}
void sgf::IState::PopState()
{
    _stateMng.PopState();
}
