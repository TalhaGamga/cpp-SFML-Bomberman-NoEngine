#pragma once
#include <SFML/System/Time.hpp>
#include "EventManager.h"
#include "Window.h"

// Forward declaration of GameStateManager class to avoid circular dependencies
class GameStateManager;

// BaseState class serves as the virtual base class for different game states
class BaseState
{
	// A friend class can access private and protected members of other classes
	friend class GameStateManager;

public:
	// Constructor: Initializes the BaseState with a pointer to the GameStateManager
	BaseState(GameStateManager* stateManager) :
		stateManager(stateManager),
		isTransparent(false),
		isTranscendent(false)
	{}

	// Virtual destructor to ensure proper cleanup in derived classes
	virtual ~BaseState() {}

	// Pure virtual functions to be implemented by derived classes
	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;

	// Input-related functions to be implemented by derived classes
	virtual void AddInputCallbacks() = 0;
	virtual void RemoveInputCallbacks() = 0;

	// Activation and deactivation functions to manage state transitions
	virtual void Activate() = 0;
	virtual void Deactivate() = 0;

	// Update and tick functions for state-specific logic and time-based actions
	virtual void Update() = 0;
	virtual void Tick(const sf::Time& time) = 0;

	// Draw function for rendering the state
	virtual void Draw() = 0;

	// Setters and getters for transparency and transcendence flags
	void SetTransparent(const bool& transparent)
	{
		this->isTransparent = transparent;
	}

	bool IsTransparent() const
	{
		return isTransparent;
	}

	void SetTranscendent(const bool& transcendence)
	{
		this->isTranscendent = transcendence;
	}

	bool IsTranscendent() const
	{
		return isTranscendent;
	}

	// Getter for the GameStateManager pointer
	GameStateManager* GetStateManager()
	{
		return stateManager;
	}

protected:
	// Pointer to the GameStateManager for state management
	GameStateManager* stateManager;

	/*
	isTransparent and isTranscendent flags indicate if this state
	also needs to render or update a state that came before it.
	*/
	bool isTransparent;
	bool isTranscendent;
};
