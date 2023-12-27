#pragma once
#include <SFML/System/Time.hpp>
#include "EventManager.h"
#include "Window.h"

class GameStateManager;

class BaseState
{
	// A friend class can access private and protected members of other classes
	friend class GameStateManager;

public:
	BaseState(GameStateManager* stateManager) :
		stateManager(stateManager),
		isTransparent(false),
		isTranscendent(false)
	{}

	virtual ~BaseState() {}

	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;

	virtual void AddInputCallbacks() = 0;
	virtual void RemoveInputCallbacks() = 0;

	virtual void Activate() = 0;
	virtual void Deactivate() = 0;

	virtual void Update() = 0;
	virtual void Tick(const sf::Time& time) = 0;

	virtual void Draw() = 0;

	void SetTransparent(const bool& transparent)
	{
		this->isTransparent = transparent;
	}

	bool IsTransparent()const
	{
		return isTransparent;
	}

	void SetTranscendent(const bool& transcendence)
	{
		this->isTranscendent = transcendence;
	}

	bool IsTranscendent()const
	{
		return isTranscendent;
	}

	GameStateManager* GetStateManager()
	{
		return stateManager;
	}

protected:
	GameStateManager* stateManager;
	bool isTransparent;
	bool isTranscendent;

	/*
	isTransparent and is Transcendent falgs indicate if this state
	also needs to render or update a state that came before it.
	*/
};

