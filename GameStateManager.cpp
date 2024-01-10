#include "GameStateManager.h"
#include "IntroState.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "PausedState.h"
#include "GameEndState.h"
#include "CreditsState.h"

GameStateManager::GameStateManager(SharedContext* sharedContext) : sharedContext(sharedContext)
{
    // Set the function pointer for switching states in the shared context
    sharedContext->SwitchState = std::bind(&GameStateManager::SwitchTo, this, std::placeholders::_1);
}

GameStateManager::~GameStateManager() {
    // Clean up all states during destruction
    for (auto& itr : states)
    {
        itr.second->OnDestroy();
        delete itr.second;
    }
}

void GameStateManager::Init()
{
    // Load key bindings and initialize states
    EventManager* eventManager = sharedContext->eventManager;
    eventManager->LoadBindings("Assets/Files/InputKeys.cfg");

    registerState<IntroState>(StateType::Intro);
    registerState<MainMenuState>(StateType::MainMenu);
    registerState<PlayState>(StateType::Play);
    registerState<PausedState>(StateType::Paused);
    registerState<GameEndState>(StateType::GameEnd);
    registerState<CreditsState>(StateType::Credits);

    // Switch to the initial state (Intro)
    SwitchTo(StateType::Intro);
}

/*
Assumption:
If there are 5 states and the third one is not transparent,
then only 4th and 5th states are drawn.
*/
void GameStateManager::Draw() {
    if (states.empty())
    {
        return;
    }

    // Draw states based on transparency
    if (states.back().second->IsTransparent() && states.size() > 1)
    {
        auto itr = states.end();
        while (itr != states.begin())
        {
            if (itr != states.end())
            {
                if (!itr->second->IsTransparent())
                {
                    break;
                }
            }
            --itr;
        }

        for (; itr != states.end(); ++itr)
        {
            itr->second->Draw();
        }
    }

    else
    {
        states.back().second->Draw();
    }
}

void GameStateManager::Update(const sf::Time& time)
{
    if (states.empty())
    {
        return;
    }

    // Update states based on transparency
    if (states.back().second->IsTranscendent() && states.size() > 1)
    {
        auto itr = states.end();
        while (itr != states.begin())
        {
            if (itr != states.end())
            {
                if (!itr->second->IsTranscendent())
                {
                    break;
                }
            }
            --itr;
        }

        for (; itr != states.end(); ++itr)
        {
            itr->second->Update();
            itr->second->Tick(time);
        }
    }

    else
    {
        states.back().second->Update();
        states.back().second->Tick(time);
    }
}

SharedContext* GameStateManager::GetContext()
{
    return sharedContext;
}

bool GameStateManager::HasState(const StateType& type)
{
    for (auto itr = states.begin();itr != states.end();++itr)
    {
        if (itr->first == type)
        {
            auto removed = std::find(toRemove.begin(), toRemove.end(), type);

            // If the searched state is not gonna be removed, then it exists. True +
            if (removed == toRemove.end())
            {
                return true;
            }
        }
    }

    return false;
}

void GameStateManager::Remove(const StateType& type)
{
    toRemove.push_back(type);
}

void GameStateManager::ProcessRequest() {
    // Process removal requests
    while (toRemove.begin() != toRemove.end())
    {
        removeState(*toRemove.begin());
        toRemove.erase(toRemove.begin());
    }
}

void GameStateManager::SwitchTo(const StateType& type)
{
    // Set the current state in the event manager
    sharedContext->eventManager->SetCurrentState(type);

    for (auto itr = states.begin(); itr != states.end();++itr)
    {
        if (itr->first == type)
        {
            states.back().second->Deactivate();
            StateType tmpType = itr->first;
            BaseState* tmpState = itr->second;
            states.erase(itr);
            states.emplace_back(tmpType, tmpState);
            tmpState->Activate();
            return;
        }
    }

    if (!states.empty())
    {
        states.back().second->Deactivate();
    }

    createState(type);
    states.back().second->Activate();
}

void GameStateManager::createState(const StateType& type)
{
    auto newState = stateFactory.find(type);

    if (newState == stateFactory.end())
    {
        return;
    }

    BaseState* state = newState->second();
    states.emplace_back(type, state);
    state->OnCreate();
}

void GameStateManager::removeState(const StateType& type)
{
    for (auto itr = states.begin();itr != states.end();++itr)
    {
        if (itr->first == type)
        {
            // Clean up and remove the specified state
            itr->second->OnDestroy();
            delete itr->second;
            states.erase(itr);
            return;
        }
    }
}
