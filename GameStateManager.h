#pragma once
#include <SFML/System/Time.hpp>
#include "EventManager.h"
#include "Window.h"
#include "BaseState.h"

using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
using TypeContainer = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<BaseState* (void)>>;

struct SharedContext {
	SharedContext() : window(nullptr), eventManager(nullptr) {}
	Window* window;
	EventManager* eventManager;

	std::function<void(const StateType&)> SwitchState;
};

enum class StateType {
	Intro = 1,
	MainMenu,
	Play,
	Paused,
	GameEnd,
	Credits
};

class GameStateManager
{
public:
	GameStateManager(SharedContext* sharedContext);
	~GameStateManager();

	void Init();

	void Update(const sf::Time& time);

	void Draw();

	void ProcessRequest();

	SharedContext* GetContext();
	bool HasState(const StateType& type);

	void SwitchTo(const StateType& type);
	void Remove(const StateType& type);

private:
	void createState(const StateType& type);
	void removeState(const StateType& type);

	//registering and creating instances of different states.
	template<class T>
	void registerState(const StateType& type)
	{
		stateFactory[type] = [this]()->BaseState*
		{
			return new T(this);
		};
	}

	SharedContext* sharedContext;
	StateContainer states;
	TypeContainer toRemove; // for smooth and error-free transitions.
	StateFactory stateFactory;
};