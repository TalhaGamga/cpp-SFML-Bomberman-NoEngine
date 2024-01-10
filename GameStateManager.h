#pragma once
#include <SFML/System/Time.hpp>
#include "EventManager.h"
#include "Window.h"
#include "BaseState.h"

// Type alias for a container holding pairs of StateType and BaseState pointers.
using StateContainer = std::vector<std::pair<StateType, BaseState*>>;

// Type alias for a container holding StateType values.
using TypeContainer = std::vector<StateType>;

// Type alias for a factory function mapping StateType to BaseState pointers.
using StateFactory = std::unordered_map<StateType, std::function<BaseState* (void)>>;

// Structure representing shared context among game states.
struct SharedContext {
	SharedContext() : window(nullptr), eventManager(nullptr) {}
	Window* window;
	EventManager* eventManager;

	// Function to switch between game states.
	std::function<void(const StateType&)> SwitchState;
};

// Enumeration representing different game states.
enum class StateType {
	Intro = 1,
	MainMenu,
	Play,
	Paused,
	GameEnd,
	Credits
};

// Class managing different game states.
class GameStateManager
{
public:
	// Constructor taking a pointer to the shared context.
	GameStateManager(SharedContext* sharedContext);

	// Destructor.
	~GameStateManager();

	// Initialize the game state manager.
	void Init();

	// Update method called during the game loop.
	void Update(const sf::Time& time);

	// Draw method for rendering the current game state.
	void Draw();

	// Process requests to remove game states.
	void ProcessRequest();

	// Get the shared context.
	SharedContext* GetContext();

	// Check if a specific game state exists.
	bool HasState(const StateType& type);

	// Switch to a new game state.
	void SwitchTo(const StateType& type);

	// Remove a game state.
	void Remove(const StateType& type);

private:
	// Create a new game state based on its type.
	void createState(const StateType& type);

	// Remove a game state based on its type.
	void removeState(const StateType& type);

	// Register a new game state type with its factory function.
	template<class T>
	void registerState(const StateType& type)
	{
		stateFactory[type] = [this]()->BaseState*
		{
			return new T(this);
		};
	}

	SharedContext* sharedContext; // Shared context among game states.
	StateContainer states; // Container holding active game states.
	TypeContainer toRemove; // Container holding game states to be removed.
	StateFactory stateFactory; // Factory mapping StateType to BaseState pointers.
};
